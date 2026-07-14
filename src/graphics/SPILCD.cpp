#ifdef ESPWATCH_S3LG
#include "configuration.h"
#if HAS_TFT && defined(USE_LCD_DRIVER)

#include "SPILCD.h"
#include "lcd.h"  // 使用ESPWATCH S3LG变体目录中的专用LCD驱动
#include "SPILock.h"

SPILCD::SPILCD(int8_t cs, int8_t rst, int8_t mosi, int8_t sck, int16_t width, int16_t height)
    : cs_pin(cs), reset_pin(rst), mosi_pin(mosi), sck_pin(sck), displayWidth(width), displayHeight(height)
{
}

bool SPILCD::begin()
{
    // 初始化SPI和LCD
    LCD_Init();
    return true;
}

void SPILCD::fillScreen(uint16_t color)
{
    LCD_Clear(color);
}

void SPILCD::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if (x < 0 || x >= displayWidth || y < 0 || y >= displayHeight)
        return;
        
    POINT_COLOR = color;
    LCD_DrawPoint(x, y);
}

void SPILCD::setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    LCD_SetWindows(x, y, x + w - 1, y + h - 1);
}

void SPILCD::writePixel(uint16_t color)
{
    Lcd_WriteData_16Bit(color);
}

void SPILCD::writePixels(uint16_t *colors, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++) {
        Lcd_WriteData_16Bit(colors[i]);
    }
}

void SPILCD::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
    LCD_Fill(x, y, x, y + h - 1, color);
}

void SPILCD::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
    LCD_Fill(x, y, x + w - 1, y, color);
}

void SPILCD::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    LCD_Fill(x, y, x + w - 1, y + h - 1, color);
}

#endif
#endif