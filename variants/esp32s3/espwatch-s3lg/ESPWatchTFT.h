#pragma once
#include "lcd.h"
#include "configuration.h"

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
        for (int32_t i = 0; i < w * h; i++) {
            uint16_t pixel = data[i];
            pixel = (pixel >> 8) | (pixel << 8);
            Lcd_WriteData_16Bit(pixel);
            if ((i & 0x3FF) == 0)
                vTaskDelay(1);
        }
    }

    void setBrightness(uint8_t brightness) {
      ledcWrite(LCD_LED, brightness);
    }
    void setRotation(uint8_t rotation) {
        LCD_set_direction(rotation);
    }

    void wakeup() {
        LOG_DEBUG("ESPWatchTFT::wakeup() - LCD re-init");
        LCD_Init();
        LOG_DEBUG("ESPWatchTFT::wakeup() done, brightness=%d", BRIGHTNESS_DEFAULT);
    }
    void sleep() {
        LOG_DEBUG("ESPWatchTFT::sleep()");
        ledcWrite(LCD_LED, 0);
        LCD_Sleep();
    }
    void powerSaveOn() {
        LOG_DEBUG("ESPWatchTFT::powerSaveOn()");
        ledcWrite(LCD_LED, 0);
    }
    void powerSaveOff() {
        LOG_DEBUG("ESPWatchTFT::powerSaveOff()");
        ledcWrite(LCD_LED, BRIGHTNESS_DEFAULT);
    }
    void displayOn() {
        LOG_DEBUG("ESPWatchTFT::displayOn()");
        LCD_Wakeup();
        ledcWrite(LCD_LED, BRIGHTNESS_DEFAULT);
    }
    void displayOff() {
        LOG_DEBUG("ESPWatchTFT::displayOff()");
        ledcWrite(LCD_LED, 0);
        LCD_Sleep();
    }
    void clear() { LCD_Clear(BLACK); }
    void setSwapBytes(bool) {}

    void *touch() { return nullptr; }
    bool getTouch(int16_t *x, int16_t *y) { return false; }
};