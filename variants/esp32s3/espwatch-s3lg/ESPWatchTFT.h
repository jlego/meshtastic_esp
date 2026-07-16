#pragma once
#include "lcd.h"

#ifndef TFT_BLACK
#define TFT_BLACK 0x0000
#endif
#ifndef TFT_WHITE
#define TFT_WHITE 0xFFFF
#endif
#ifndef TFT_RED
#define TFT_RED   0xF800
#endif
#ifndef TFT_GREEN
#define TFT_GREEN 0x07E0
#endif
#ifndef TFT_BLUE
#define TFT_BLUE  0x001F
#endif

class ESPWatchTFT {
  public:
    void init() {
        LCD_Init();
    }

    void fillScreen(uint16_t color) {
        LCD_Clear(color);
    }

    void pushImage(int32_t x, int32_t y, int32_t w, int32_t h, const uint16_t *data) {
        LCD_SetWindows(x, y, x + w - 1, y + h - 1);

        digitalWrite(LCD_CS, LOW);
        uint8_t txbuf[2];
        txbuf[0] = (uint8_t)((0 << 7) | (0x2C >> 1)) & 0xFF;
        txbuf[1] = (uint8_t)(0x2C << 7) & 0xFF;
        lcdSPI.transferBytes(txbuf, NULL, 2);
        digitalWrite(LCD_CS, HIGH);

        int32_t total = w * h;
        for (int32_t i = 0; i < total; i++) {
            uint16_t px = data[i];
            uint8_t hi = (uint8_t)(px >> 8);
            uint8_t lo = (uint8_t)(px & 0xFF);
            // Swap byte order: send LO byte first, then HI byte
            digitalWrite(LCD_CS, LOW);
            txbuf[0] = (uint8_t)((1 << 7) | (lo >> 1)) & 0xFF;
            txbuf[1] = (uint8_t)(lo << 7) & 0xFF;
            lcdSPI.transferBytes(txbuf, NULL, 2);
            digitalWrite(LCD_CS, HIGH);

            digitalWrite(LCD_CS, LOW);
            txbuf[0] = (uint8_t)((1 << 7) | (hi >> 1)) & 0xFF;
            txbuf[1] = (uint8_t)(hi << 7) & 0xFF;
            lcdSPI.transferBytes(txbuf, NULL, 2);
            digitalWrite(LCD_CS, HIGH);
        }
    }

    void setBrightness(uint8_t brightness) {
        ledcWrite(LCD_LED, brightness);
    }
    void setRotation(uint8_t rotation) {
        LCD_set_direction(rotation);
    }

    void wakeup() {}
    void sleep() {}
    void powerSaveOn() {}
    void powerSaveOff() {}
    void displayOn() {}
    void displayOff() {}
    void clear() { LCD_Clear(0); }
    void setSwapBytes(bool) {}

    void *touch() { return nullptr; }
    bool getTouch(int16_t *x, int16_t *y) { return false; }
};