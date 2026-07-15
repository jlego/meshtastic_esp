#pragma once

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <SPI.h>
#include <esp_task_wdt.h>
#include "lcd.h"

// Declare external vspi from lcd.cpp
extern SPIClass* vspi;

#ifndef SPI_FREQUENCY
#define SPI_FREQUENCY 40000000
#endif

class Bus_SPI_9bit : public lgfx::IBus
{
public:
    lgfx::bus_type_t busType(void) const override { return lgfx::bus_type_t::bus_spi; }

    void configCS(int cs_pin)
    {
        _cs_pin = cs_pin;
        _cs_mask = (1UL << cs_pin);
        pinMode(_cs_pin, OUTPUT);
        GPIO.out_w1ts = _cs_mask;
        _yield_counter = 0;
    }

    bool init(void) override
    {
        pinMode(_cs_pin, OUTPUT);
        GPIO.out_w1ts = _cs_mask;
        _initialized = true;
        _yield_counter = 0;
        return true;
    }

    void release(void) override {}
    void beginTransaction(void) override {}
    void endTransaction(void) override {}
    void wait(void) override {}
    bool busy(void) const override { return false; }
    void initDMA(void) override {}
    void addDMAQueue(const uint8_t *data, uint32_t length) override { writeBytes(data, length, true, false); }
    void execDMAQueue(void) override {}
    uint8_t *getDMABuffer(uint32_t length) override { return _buf; }
    void flush(void) override {}

    bool writeCommand(uint32_t data, uint_fast8_t bit_length) override
    {
        if (!_initialized || bit_length != 8) return true;
        GPIO.out_w1tc = _cs_mask;
        _spi9Write(data & 0xFF, 0);
        GPIO.out_w1ts = _cs_mask;
        return true;
    }

    void writeData(uint32_t data, uint_fast8_t bit_length) override
    {
        if (!_initialized) return;
        if (bit_length == 8) {
            GPIO.out_w1tc = _cs_mask;
            _spi9Write(data & 0xFF, 1);
            GPIO.out_w1ts = _cs_mask;
        } else if (bit_length == 16) {
            GPIO.out_w1tc = _cs_mask;
            _spi9Write((data >> 8) & 0xFF, 1);
            GPIO.out_w1ts = _cs_mask;
            GPIO.out_w1tc = _cs_mask;
            _spi9Write(data & 0xFF, 1);
            GPIO.out_w1ts = _cs_mask;
        } else if (bit_length == 32) {
            for (int i = 3; i >= 0; i--) {
                GPIO.out_w1tc = _cs_mask;
                _spi9Write((data >> (i * 8)) & 0xFF, 1);
                GPIO.out_w1ts = _cs_mask;
            }
        }
    }

    void writeDataRepeat(uint32_t data, uint_fast8_t bit_length, uint32_t count) override
    {
        if (!_initialized) return;
        if (bit_length == 16) {
            uint8_t hi = (data >> 8) & 0xFF;
            uint8_t lo = data & 0xFF;
            for (uint32_t i = 0; i < count; i++) {
                GPIO.out_w1tc = _cs_mask;
                _spi9Write(hi, 1);
                GPIO.out_w1ts = _cs_mask;
                GPIO.out_w1tc = _cs_mask;
                _spi9Write(lo, 1);
                GPIO.out_w1ts = _cs_mask;
            }
        } else if (bit_length == 8) {
            uint8_t b = data & 0xFF;
            for (uint32_t i = 0; i < count; i++) {
                GPIO.out_w1tc = _cs_mask;
                _spi9Write(b, 1);
                GPIO.out_w1ts = _cs_mask;
            }
        }
    }

    // writePixels - 从pixelcopy_t获取像素数据发送
    // ⚠️ 字节顺序说明：
    //    LGFXDriver::display_flush 已调用 lv_draw_sw_rgb565_swap() 将像素数据
    //    从 little-endian 交换为 big-endian，然后调用 lgfx->pushImage()
    //    → fp_copy 输出的 buf 已经是 big-endian RGB565
    //    → 直接按 buf 顺序发送即可，与 ST7789 期望的 big-endian 一致
    void writePixels(lgfx::pixelcopy_t *pc, uint32_t length) override
    {
        Serial.printf("[LGFX] writePixels: length=%d\n", length);
        if (!_initialized) return;
        const uint32_t PIXELS_PER_BATCH = 256;
        uint8_t buf[PIXELS_PER_BATCH * 2];
        while (length) {
            uint32_t n = (length > PIXELS_PER_BATCH) ? PIXELS_PER_BATCH : length;
            n = pc->fp_copy(buf, 0, n, pc);
            if (n == 0) break;
            uint32_t byte_count = n * 2;
            for (uint32_t i = 0; i < byte_count; i++) {
                GPIO.out_w1tc = _cs_mask;
                _spi9Write(buf[i], 1);
                GPIO.out_w1ts = _cs_mask;
            }
            length -= n;
        }
        Serial.printf("[LGFX] writePixels done\n");
    }

    // writeBytes - 命令/数据直接发送路径
    // ⚠️ 字节顺序说明：
    //    dc=false(命令参数)：按原始顺序发送
    //    dc=true(像素数据)：display_flush已做lv_draw_sw_rgb565_swap，
    //                      fp_copy输出的data已是big-endian，按原始顺序直接发送
    void writeBytes(const uint8_t *data, uint32_t length, bool dc, bool use_dma) override
    {
        if (!_initialized) return;
        Serial.printf("[LGFX] writeBytes: length=%d, dc=%d\n", length, dc);
        uint8_t dc_bit = dc ? 1 : 0;
        for (uint32_t i = 0; i < length; i++) {
            GPIO.out_w1tc = _cs_mask;
            _spi9Write(data[i], dc_bit);
            GPIO.out_w1ts = _cs_mask;
        }
    }

    void beginRead(uint_fast8_t dummy_bits) override {}
    void beginRead(void) override {}
    void endRead(void) override {}
    uint32_t readData(uint_fast8_t bit_length) override { return 0; }
    bool readBytes(uint8_t *dst, uint32_t length, bool use_dma = false) override { return false; }
    void readPixels(void *dst, lgfx::pixelcopy_t *pc, uint32_t length) override {}
    void setClock(uint32_t freq) override {}
    uint32_t getClock(void) const override { return SPI_FREQUENCY; }

private:
    int _cs_pin = -1;
    uint32_t _cs_mask = 0;
    uint32_t _yield_counter = 0;
    bool _initialized = false;
    uint8_t _buf[1024];

    // ═════════════════════════════════════════════════════════════
    // 所有SPI数据发送的唯一入口点
    // 9-bit SPI编码: DC位(1bit) + 数据(8bit) → SPI发送2字节(16bit)
    // 内部嵌入yield计数器 - 每128字节数据让出一次CPU避免WDT超时
    // 使用lcd.cpp的vspi实例，避免SPI总线冲突
    // ═════════════════════════════════════════════════════════════
    inline void _spi9Write(uint8_t data, uint8_t dc)
    {
        uint8_t txbuf[2];
        txbuf[0] = (uint8_t)((dc << 7) | (data >> 1)) & 0xFF;
        txbuf[1] = (uint8_t)(data << 7) & 0xFF;
        vspi->transferBytes(txbuf, NULL, 2);
        _yield_counter++;
        // 每128次调用让出一次CPU
        // 40MHz SPI: 128×16bits/40MHz = 51µs + overhead ≈ 1-3ms
        if (_yield_counter >= 128) {
            _yield_counter = 0;
            vTaskDelay(1);
        }
    }
};

class LGFX_ESWATCH_S3LG : public lgfx::LGFX_Device
{
    struct Panel_ESWATCH_S3LG : public lgfx::Panel_ST7789
    {
        const uint8_t *getInitCommands(uint8_t listno) const override
        {
            return nullptr;
        }
    };

    Panel_ESWATCH_S3LG _panel_instance;
    Bus_SPI_9bit _bus_instance;
    lgfx::Light_PWM _light_instance;

public:
    const uint32_t screenWidth = 240;
    const uint32_t screenHeight = 285;

    bool hasButton(void) { return true; }

    LGFX_ESWATCH_S3LG(void)
    {
        _panel_instance.setBus(&_bus_instance);
        _bus_instance.configCS(7);
        // Initialize the bus early so _initialized is true before LGFX uses it
        _bus_instance.init();

        {
            auto cfg = _panel_instance.config();
            cfg.pin_cs = -1;           // CS由Bus_SPI_9bit直接控制
            cfg.pin_rst = -1;
            cfg.pin_busy = -1;
            cfg.memory_width = 240;    // ST7789驱动器IC支持的最大宽度
            cfg.memory_height = 320;   // ST7789驱动器IC支持的最大高度
            cfg.panel_width = 240;     // 实际可显示宽度
            cfg.panel_height = 285;    // 实际可显示高度
            cfg.offset_x = 0;
            cfg.offset_y = 0;
            cfg.offset_rotation = 0;
            cfg.dummy_read_pixel = 9;  // 标准ST7789的dummy读取位
            cfg.dummy_read_bits = 1;
            cfg.readable = false;
            cfg.invert = true;         // ⚠️ 关键修复：ST7789需要display inversion ON（0x21）
                                       //            若为false，Panel会发送0x20覆盖init中的0x21，导致颜色花屏
            cfg.rgb_order = false;     // ⚠️ 与lcd.cpp一致，不做R↔B通道swap
                                       //    lcd.cpp发送RGB565 big-endian可正常显示
                                       //    display_flush已做lv_draw_sw_rgb565_swap字节交换
                                       //    fp_copy(rgb_order=false)保持RGB顺序，直接发送即可
            cfg.dlen_16bit = false;
            cfg.bus_shared = false;
            _panel_instance.config(cfg);
        }

        {
            auto cfg = _light_instance.config();
            cfg.pin_bl = 15;
            cfg.invert = false;
            cfg.freq = 5000;
            cfg.pwm_channel = 7;
            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance);
        }

        setPanel(&_panel_instance);
    }
};