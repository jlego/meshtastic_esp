#include "lcd.h"

#define u8 char
#define u16 int
#define u32 long
#define SPI1 0

SPIClass* vspi = NULL;
static const int spiClk = 20 * 1000 * 1000;  // 40 MHz
_lcd_dev lcddev;

#define delay_ms(x) delay(x)
u16 POINT_COLOR = 0x0000, BACK_COLOR = 0xFFFF;

u8 SPI_WriteByte(int SPIx, u8 Byte, u8 cmd) {
    uint8_t txbuf[2];
    txbuf[0] = (uint8_t)((cmd << 7) | (Byte >> 1)) & 0xFF;
    txbuf[1] = (uint8_t)((Byte << 7)) & 0xFF;
		vspi->transferBytes(txbuf, NULL, 2);
    return 0;
}
/*****************************************************************************
 * @name       :void LCD_WR_REG(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_REG(u8 data) {
	LCD_CS_CLR();
	// LCD_DC_CLR;
	SPI_WriteByte(SPI1, data, 0);
	LCD_CS_SET();
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_DATA(u8 data) {
	LCD_CS_CLR();
	// LCD_DC_SET;
	SPI_WriteByte(SPI1, data, 1);
	LCD_CS_SET();
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :LCD_WR_DATA()into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue) {
	LCD_WR_REG(LCD_Reg);
	LCD_WR_DATA(LCD_RegValue);
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void LCD_WriteRAM_Prepare(void) {
	LCD_WR_REG(lcddev.wramcmd);
}

/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(u16 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/
void Lcd_WriteData_16Bit(u16 Data) {
	LCD_WR_DATA(Data >> 8);
	LCD_WR_DATA(Data);
}
// void Lcd_WriteData_16Bit(u16 Data) {
// 	uint8_t txbuf[4];
// 	LCD_CS_CLR();
// 	txbuf[0] = (uint8_t)((1 << 7) | ((Data >> 8) >> 1)) & 0xFF;
// 	txbuf[1] = (uint8_t)(((Data >> 8) << 7)) & 0xFF;
// 	// vspi->transferBytes(txbuf, NULL, 2);
// 	// LCD_CS_SET();
// 	// LCD_CS_CLR();
// 	txbuf[2] = (uint8_t)((1 << 7) | (Data >> 1)) & 0xFF;
// 	txbuf[3] = (uint8_t)((Data << 7)) & 0xFF;
// 	vspi->transferBytes(txbuf, NULL, 4);
// 	LCD_CS_SET();
// }

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel 
 * @retvalue   :None
******************************************************************************/
void LCD_DrawPoint(u16 x, u16 y) {
	LCD_SetCursor(x, y);
	Lcd_WriteData_16Bit(POINT_COLOR);
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09 
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/
void LCD_Clear(u16 Color)
{
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
    uint32_t total_pixels = lcddev.width * lcddev.height;
    LCD_WriteRAM_Prepare();
    for (uint32_t i = 0; i < total_pixels; i++) {
        Lcd_WriteData_16Bit(Color);  // 使用16位写入函数
        // 可选：每N次让出CPU，防止看门狗
        if (i % 2048 == 0) {
            delay_ms(1);
        }
    }
} 

/*****************************************************************************
 * @name       :void LCD_GPIOInit(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen GPIO
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void LCD_GPIOInit(void) {
	// Serial.println("LCD_GPIOInit start");
	vspi = new SPIClass(HSPI);
	pinMode(LCD_CS, OUTPUT);
	// Serial.printf("LCD_LED=%d LCD_CS=%d\n", LCD_LED, LCD_CS);
	// Serial.printf("VSPI_SCLK=%d VSPI_MISO=%d VSPI_MOSI=%d VSPI_SS=%d\n", VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);
	vspi->begin(VSPI_SCLK, -1, VSPI_MOSI, VSPI_SS);
	vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
	// Serial.println("LCD_GPIOInit done");
}

/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09 
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void LCD_RESET(void) {
	if (LCD_RST >= 0) {
		LCD_RST_CLR;
		delay_ms(100);
		LCD_RST_SET;
		delay_ms(50);
	} else {
		LCD_WR_REG(0x01);
		delay_ms(150);
	}
}

/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void LCD_Init(void) {
	//	SPI1_Init();
	LCD_GPIOInit();
	LCD_RESET();

	//************* ST7789 IPS**********//
	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x33);
	LCD_WR_DATA(0x33);

	LCD_WR_REG(0xB7);
	LCD_WR_DATA(0x35);

	LCD_WR_REG(0xBB);
	LCD_WR_DATA(0x17);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA(0x12);

	LCD_WR_REG(0xC4);
	LCD_WR_DATA(0x20);

	LCD_WR_REG(0xC6);
	LCD_WR_DATA(0x0F);

	LCD_WR_REG(0xD0);
	LCD_WR_DATA(0xA4);
	LCD_WR_DATA(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0xD0);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x2B);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0x54);
	LCD_WR_DATA(0x4C);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x0B);
	LCD_WR_DATA(0x1F);
	LCD_WR_DATA(0x23);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA(0xD0);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0x44);
	LCD_WR_DATA(0x51);
	LCD_WR_DATA(0x2F);
	LCD_WR_DATA(0x1F);
	LCD_WR_DATA(0x1F);
	LCD_WR_DATA(0x20);
	LCD_WR_DATA(0x23);

	LCD_WR_REG(0x21);

	LCD_WR_REG(0x11);
	delay_ms(120);

	LCD_WR_REG(0x29);

	LCD_set_direction(USE_HORIZONTAL);
	ledcAttach(LCD_LED, 5000, 8);
	ledcWrite(LCD_LED, BRIGHTNESS_DEFAULT);
	// LCD_Clear(WHITE);
}

/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/
void LCD_SetWindows(u16 xStar, u16 yStar, u16 xEnd, u16 yEnd) {
	LCD_WR_REG(lcddev.setxcmd);
	LCD_WR_DATA((xStar + lcddev.xoffset) >> 8);
	LCD_WR_DATA(xStar + lcddev.xoffset);
	LCD_WR_DATA((xEnd + lcddev.xoffset) >> 8);
	LCD_WR_DATA(xEnd + lcddev.xoffset);

	LCD_WR_REG(lcddev.setycmd);
	LCD_WR_DATA((yStar + lcddev.yoffset) >> 8);
	LCD_WR_DATA(yStar + lcddev.yoffset);
	LCD_WR_DATA((yEnd + lcddev.yoffset) >> 8);
	LCD_WR_DATA(yEnd + lcddev.yoffset);

	LCD_WriteRAM_Prepare();
}

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09 
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/
void LCD_SetCursor(u16 Xpos, u16 Ypos) {
	LCD_SetWindows(Xpos, Ypos, Xpos, Ypos);
}

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/
void LCD_set_direction(u8 lcd_direction) {
	lcddev.setxcmd = 0x2A;
	lcddev.setycmd = 0x2B;
	lcddev.wramcmd = 0x2C;
	lcddev.dir = lcd_direction % 4;
	switch (lcddev.dir) {
		case 0:
			lcddev.width = LCD_W;
			lcddev.height = LCD_H;
			lcddev.xoffset = 0;
			lcddev.yoffset = 0;
			LCD_WriteReg(0x36, 0);  //BGR==1,MY==0,MX==0,MV==0
			break;
		case 1:
			lcddev.width = LCD_H;
			lcddev.height = LCD_W;
			lcddev.xoffset = 0;
			lcddev.yoffset = 0;
			LCD_WriteReg(0x36, (1 << 6) | (1 << 5));  //BGR==1,MY==1,MX==0,MV==1
			break;
		case 2:
			lcddev.width = LCD_W;
			lcddev.height = LCD_H;
			lcddev.xoffset = 0;
			lcddev.yoffset = 0;
			LCD_WriteReg(0x36, (1 << 6) | (1 << 7));  //BGR==1,MY==0,MX==0,MV==0
			break;
		case 3:
			lcddev.width = LCD_H;
			lcddev.height = LCD_W;
			lcddev.xoffset = 0;
			lcddev.yoffset = 0;
			LCD_WriteReg(0x36, (1 << 7) | (1 << 5));  //BGR==1,MY==1,MX==0,MV==1
			break;
		default: break;
	}
}
// void LCD_set_direction(u8 lcd_direction) {
// 	lcddev.setxcmd = 0x2A;
// 	lcddev.setycmd = 0x2B;
// 	lcddev.wramcmd = 0x2C;
// 	lcddev.dir = lcd_direction % 4;

// 	switch (lcddev.dir) {
// 		case 0:  // 0度方向（默认）
// 			lcddev.width = LCD_W;
// 			lcddev.height = LCD_H;
// 			lcddev.xoffset = 0;
// 			lcddev.yoffset = 20;       // 增加20像素的Y轴偏移
// 			LCD_WriteReg(0x36, 0x00);  // BGR=1, MY=0, MX=0, MV=0
// 			break;

// 		case 1:  // 90度方向
// 			lcddev.width = LCD_H;
// 			lcddev.height = LCD_W;
// 			lcddev.xoffset = 0;
// 			lcddev.yoffset = 20;                      // 增加20像素的Y轴偏移
// 			LCD_WriteReg(0x36, (1 << 6) | (1 << 5));  // BGR=1, MY=1, MX=0, MV=1
// 			break;

// 		case 2:  // 180度方向
// 			lcddev.width = LCD_W;
// 			lcddev.height = LCD_H;
// 			lcddev.xoffset = 0;
// 			lcddev.yoffset = 20;                      // 增加20像素的Y轴偏移
// 			LCD_WriteReg(0x36, (1 << 6) | (1 << 7));  // BGR=1, MY=0, MX=1, MV=0
// 			break;

// 		case 3:  // 270度方向
// 			lcddev.width = LCD_H;
// 			lcddev.height = LCD_W;
// 			lcddev.xoffset = 0;
// 			lcddev.yoffset = 20;                      // 增加20像素的Y轴偏移
// 			LCD_WriteReg(0x36, (1 << 7) | (1 << 5));  // BGR=1, MY=1, MX=1, MV=1
// 			break;

// 		default:
// 			break;
// 	}
// }

void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color) {
	u16 i, j;
	u16 width = ex - sx + 1;
	u16 height = ey - sy + 1;
	LCD_SetWindows(sx, sy, ex, ey);
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++)
			Lcd_WriteData_16Bit(color);
	}
	LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}


#define PI_BUF_SIZE 256
void showImage(int32_t x, int32_t y, int32_t w, int32_t h, const unsigned char* data) {
	int32_t dx = 0;
	int32_t dy = 0;
	int32_t dw = w;
	int32_t dh = h * 2;
	if (x < 0) {
		dw += x;
		dx = -x;
		x = 0;
	}
	if (y < 0) {
		dh += y;
		dy = -y;
		y = 0;
	}
	if (dw < 1 || dh < 1) return;
	data += dx + dy * w;
	uint16_t buffer[PI_BUF_SIZE];
	uint16_t* pix_buffer = buffer;
	uint16_t high, low;
	//tft.setWindow(x, y, x + dw - 1, y + dh - 1);
	// Work out the number whole buffers to send
	uint16_t nb = (dw * dh) / (2 * PI_BUF_SIZE);
	// Fill and send "nb" buffers to TFT
	for (int32_t i = 0; i < nb; i++) {
		for (int32_t j = 0; j < PI_BUF_SIZE; j++) {
			high = pgm_read_word(&data[(i * 2 * PI_BUF_SIZE) + 2 * j + 1]);
			low = pgm_read_word(&data[(i * 2 * PI_BUF_SIZE) + 2 * j]);
			pix_buffer[j] = (high << 8) + low;
		}
		//tft.pushPixels(pix_buffer, PI_BUF_SIZE);
	}
	// Work out number of pixels not yet sent
	uint16_t np = (dw * dh) % (2 * PI_BUF_SIZE);
	// Send any partial buffer left over
	if (np) {
		for (int32_t i = 0; i < np; i++) {
			high = pgm_read_word(&data[(nb * 2 * PI_BUF_SIZE) + 2 * i + 1]);
			low = pgm_read_word(&data[(nb * 2 * PI_BUF_SIZE) + 2 * i]);
			pix_buffer[i] = (high << 8) + low;
		}
		//tft.pushPixels(pix_buffer, np);
	}
}

void LCD_Fill_hv(u16 sx, u16 sy, u16 ex, u16 ey, u16 color) {
	u16 i, j;
	u16 width = ex - sx + 1;
	u16 height = ey - sy + 1;
	LCD_SetWindows(sx, sy, ex, ey);
	char txbuf[3];
	txbuf[0] = 0;  //color>>9;
	txbuf[1] = color >> 1;
	txbuf[2] = color << 15;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			LCD_CS_CLR();
			vspi->transfer(txbuf[0]);
			vspi->transfer(txbuf[1]);
			vspi->transfer(txbuf[2]);
			LCD_CS_SET();
		}
	}
	LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}

void LCD_PushImage(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *data, uint32_t byte_len) {
	Serial.printf("LCD_PushImage: x1=%d y1=%d x2=%d y2=%d len=%d\n", x1, y1, x2, y2, byte_len);
	LCD_SetWindows(x1, y1, x2, y2);
	uint32_t yield_counter = 0;
	uint8_t txbuf[2];
	for (uint32_t i = 0; i < byte_len; i++) {
		LCD_CS_CLR();
		txbuf[0] = (uint8_t)((1 << 7) | (data[i] >> 1)) & 0xFF;
		txbuf[1] = (uint8_t)(data[i] << 7) & 0xFF;
		vspi->transferBytes(txbuf, NULL, 2);
		LCD_CS_SET();
		yield_counter++;
		if (yield_counter >= 256) {
			yield_counter = 0;
			vTaskDelay(1);
		}
	}
}

void LCD_Sleep(void) {
	LCD_WR_REG(0x10);
	delay_ms(120);
}

void LCD_Wakeup(void) {
	LCD_WR_REG(0x11);
	delay_ms(120);
	LCD_WR_REG(0x29);
}