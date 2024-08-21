
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "pin_config.h"
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>
#include <driver/i2c.h>

class LGFX : public lgfx::LGFX_Device
{
public:
    lgfx::Bus_RGB _bus_instance;
    lgfx::Panel_RGB _panel_instance;
    lgfx::Light_PWM _light_instance;
    lgfx::Touch_GT911 _touch_instance;

    LGFX(void)
    {
        {
            auto cfg = _panel_instance.config();
            cfg.memory_width = LCD_WIDTH;
            cfg.memory_height = LCD_HEIGHT;
            cfg.panel_width = LCD_WIDTH;
            cfg.panel_height = LCD_HEIGHT;
            cfg.offset_x = 0;
            cfg.offset_y = 0;
            _panel_instance.config(cfg);
        }

        {
            auto cfg = _panel_instance.config_detail();
            cfg.use_psram = 1;
            _panel_instance.config_detail(cfg);
        }

        {
            auto cfg = _bus_instance.config();
            cfg.panel = &_panel_instance;
            cfg.pin_d0 = PIN_LCD_D0;   // B0
            cfg.pin_d1 = PIN_LCD_D1;   // B1
            cfg.pin_d2 = PIN_LCD_D2;   // B2
            cfg.pin_d3 = PIN_LCD_D3;   // B3
            cfg.pin_d4 = PIN_LCD_D4;   // B4
            cfg.pin_d5 = PIN_LCD_D5;   // G0
            cfg.pin_d6 = PIN_LCD_D6;   // G1
            cfg.pin_d7 = PIN_LCD_D7;   // G2
            cfg.pin_d8 = PIN_LCD_D8;   // G3
            cfg.pin_d9 = PIN_LCD_D9;   // G4
            cfg.pin_d10 = PIN_LCD_D10; // G5
            cfg.pin_d11 = PIN_LCD_D11; // R0
            cfg.pin_d12 = PIN_LCD_D12; // R1
            cfg.pin_d13 = PIN_LCD_D13; // R2
            cfg.pin_d14 = PIN_LCD_D14; // R3
            cfg.pin_d15 = PIN_LCD_D15; // R4

            cfg.pin_henable = PIN_LCD_DE;
            cfg.pin_vsync = PIN_LCD_VS;
            cfg.pin_hsync = PIN_LCD_HS;
            cfg.pin_pclk = PIN_LCD_CLK;
            cfg.freq_write = LCD_FREQ;

            cfg.hsync_polarity = 0;
            cfg.hsync_front_porch = 40;
            cfg.hsync_pulse_width = 48;
            cfg.hsync_back_porch = 40;

            cfg.vsync_polarity = 0;
            cfg.vsync_front_porch = 1;
            cfg.vsync_pulse_width = 31;
            cfg.vsync_back_porch = 13;

            cfg.pclk_idle_high = 1;
            _bus_instance.config(cfg);
        }
        _panel_instance.setBus(&_bus_instance);

        {
            auto cfg = _light_instance.config();
            cfg.pin_bl = PIN_LCD_BL;
            cfg.invert = true;
            _light_instance.config(cfg);
        }
        _panel_instance.light(&_light_instance);

        {
            auto cfg = _touch_instance.config();
            cfg.x_min = 0;
            cfg.y_min = 0;
            cfg.bus_shared = false;
            cfg.offset_rotation = 0;

            cfg.pin_sda = PIN_TOUCH_SDA;
            cfg.pin_scl = PIN_TOUCH_SCL;
            cfg.pin_int = PIN_TOUCH_INT;
            cfg.pin_rst = PIN_TOUCH_RST;
            cfg.i2c_port = TOUCH_PORT;
            cfg.x_max = LCD_WIDTH;
            cfg.y_max = LCD_HEIGHT;

            cfg.freq = TOUCH_FREQ;
            _touch_instance.config(cfg);
            _panel_instance.setTouch(&_touch_instance);
        }

        setPanel(&_panel_instance);
    }
};