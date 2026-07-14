#pragma once

#ifdef ESPWATCH_S3LG
#include "configuration.h"
#if HAS_TFT && defined(USE_LCD_DRIVER)

#include <Arduino.h>

// SPILCD - 使用ESPWATCH S3LG变体目录中的专用LCD驱动的类
class SPILCD
{
  private:
    int8_t cs_pin, reset_pin, mosi_pin, sck_pin;
    int16_t displayWidth, displayHeight;

  public:
    SPILCD(int8_t cs, int8_t rst, int8_t mosi, int8_t sck, int16_t width, int16_t height);

    bool begin();
    void fillScreen(uint16_t color);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void writePixel(uint16_t color);
    void writePixels(uint16_t *colors, uint32_t len);
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
};

#endif
#endif