#pragma once

// LCD EK9716BD3 + EK73002ACGB
#define LCD_WIDTH 800
#define LCD_HEIGHT 480
#define LCD_FREQ 16000000
#define PIN_LCD_BL 2
#define PIN_LCD_CLK 0
#define PIN_LCD_DE 41
#define PIN_LCD_VS 40
#define PIN_LCD_HS 39

#define PIN_LCD_D0 15
#define PIN_LCD_D1 7
#define PIN_LCD_D2 6
#define PIN_LCD_D3 5
#define PIN_LCD_D4 4
#define PIN_LCD_D5 9
#define PIN_LCD_D6 46
#define PIN_LCD_D7 3
#define PIN_LCD_D8 8
#define PIN_LCD_D9 16
#define PIN_LCD_D10 1
#define PIN_LCD_D11 14
#define PIN_LCD_D12 21
#define PIN_LCD_D13 47
#define PIN_LCD_D14 48
#define PIN_LCD_D15 45

// I2C
#define PIN_I2C_SDA 19
#define PIN_I2C_SCL 20

// I2S
#define PIN_I2S_SDIN 17
#define PIN_I2S_LRCLK 18
#define PIN_I2S_BCLK 42

// Serial
#define PIN_SERIAL_TX 43
#define PIN_SERIAL_RX 44

// Touchscreen GT911
#define TOUCH_ADDR 0x14
#define TOUCH_FREQ 400000
#define TOUCH_PORT I2C_NUM_1
#define PIN_TOUCH_SCL PIN_I2C_SCL
#define PIN_TOUCH_SDA PIN_I2C_SDA
#define PIN_TOUCH_RST -1
#define PIN_TOUCH_INT -1

// SDcard
#define SPI_FREQ 80000000
#define PIN_SD_MISO 13
#define PIN_SD_MOSI 11
#define PIN_SD_SCK 12
#define PIN_SD_CS 10

// GPIO_D
#define PIN_GPIO_D 38
