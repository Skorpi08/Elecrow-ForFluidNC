#include "PCA9557.h"
#include "main.h"

LGFX tft;
PCA9557 Out;
extern void updateDisplay();
extern "C" void fnc_putchar(uint8_t c);
extern void fnc_poll();

void display_set_brightness(int brightness)
{
    analogWrite(PIN_LCD_BL, brightness);
}

void setup(void)
{
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    Out.reset();
    Out.setMode(IO_OUTPUT);
    Out.setState(IO0, IO_LOW);
    Out.setState(IO1, IO_LOW);
    delay(20);
    Out.setState(IO0, IO_HIGH);
    delay(100);
    Out.setMode(IO1, IO_INPUT);

    FNCSerial.begin(115200);
    tft.begin();
    fnc_putchar('?');
#ifdef USE_LVGL
    lvgl_begin();
#endif
    updateDisplay();
}

void loop(void)
{
    fnc_poll();
#ifdef USE_LVGL
    lv_timer_handler();
#endif
}
