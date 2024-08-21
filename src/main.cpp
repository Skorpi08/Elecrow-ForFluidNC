#include "main.h"

LGFX tft;

extern void updateDisplay();
extern "C" void fnc_putchar(uint8_t c);
extern void fnc_poll();

void display_set_brightness(int brightness)
{
    analogWrite(PIN_LCD_BL, brightness);
}

void setup(void)
{
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
