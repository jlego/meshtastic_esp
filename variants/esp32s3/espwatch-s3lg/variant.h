#define PIN_BUTTON1 0 // 功能键
#define BUTTON_PIN PIN_BUTTON1
#define BUTTON_NEED_PULLUP 1   // ← 加在这里
#define PIN_BUTTON2 45  // 电源键

#define LED_PIN 4
#define LED_STATE_ON 1
// ST7789 TFT LCD
#define ST7789_CS 7
#define ST7789_SDA 6 // MOSI
#define ST7789_SCK 5
#define ST7789_MISO 46
#define ST7789_BL 15
#define ST7789_SPI_HOST SPI3_HOST
#define USE_TFTDISPLAY 1

#define USE_POWERSAVE
#define DISPLAY_CLOCK_FRAME 1

#undef BATTERY_PIN

// PCF8563 RTC Module
#define PCF8563_RTC 0x51

// CW2015 Fuel Gauge
#define HAS_CW2015 1

#define I2C_SDA 1
#define I2C_SCL 2

#define HAS_LIS3DH 1
#define LIS3DH_INT 21

// #define USE_SX1262
#define USE_SX1268

#define LORA_SCK 18
#define LORA_MISO 11
#define LORA_MOSI 12
#define LORA_CS 14

#define LORA_DIO0 9 // TXEN (RF switch TX control)
#define LORA_RESET RADIOLIB_NC
#define LORA_DIO1 41 // LoRa IRQ
#define LORA_DIO2 10 // SX126X BUSY
#define LORA_DIO3   // Not connected on PCB, but internally on the TTGO SX1262, if DIO3 is high the TXCO is enabled

#define SX126X_CS LORA_CS
#define SX126X_DIO1 LORA_DIO1 // IRQ on IO41
#define SX126X_BUSY LORA_DIO2
#define SX126X_RESET LORA_RESET
#define SX126X_RXEN 8
#define SX126X_TXEN 9
#define SX126X_DIO3_TCXO_VOLTAGE 1.8
/*
 * GPS pins
 */
#define HAS_GPS 1
#define GPS_BAUDRATE 9600
// #define PIN_GPS_RESET (42)
// #define GPS_RESET_MODE LOW
#define PIN_GPS_EN 40
#define GPS_EN_ACTIVE LOW
#define PERIPHERAL_WARMUP_MS 1000
// #define PIN_GPS_PPS (41)
#define GPS_TX_PIN 43
#define GPS_RX_PIN 44
#define GPS_THREAD_INTERVAL 50

#undef HAS_PMU