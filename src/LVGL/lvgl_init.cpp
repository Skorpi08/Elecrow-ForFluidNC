#ifdef USE_LVGL

#include "main.h"

static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf1[LCD_WIDTH * LCD_HEIGHT / 10];
static lv_color_t disp_draw_buf2[LCD_WIDTH * LCD_HEIGHT / 10];
static lv_disp_drv_t disp_drv;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    tft.pushImageDMA(area->x1, area->y1, w, h, (lgfx::rgb565_t *)&color_p->full);
    lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    uint16_t touchX, touchY;
    bool touched = tft.getTouch(&touchX, &touchY);
    if (!touched)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchX;
        data->point.y = touchY;
    }
}

void lvgl_begin()
{
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf1, disp_draw_buf2, LCD_WIDTH * LCD_HEIGHT / 10);
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.full_refresh = 1;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
    lvgl_UI();
}

// Beispielhafte Anzahl der Achsen
int axis_count = 6; // XYZABC

// Positionswerte der Achsen
int axis_positions[6] = {0, 0, 0, 0, 0, 0};

// Limit Switch Status
bool limit_switches[6] = {false, false, false, false, false, false};

// Geräte Status
bool air_status = false;
bool coolant_status = false;
void update_ui();
void update_axis_data_from_serial()
{
    // Beispiel: Empfangen von Daten über Serial
    if (Serial.available())
    {
        String data = Serial.readString();

        // Parsen der Daten
        sscanf(data.c_str(), "X:%d Y:%d Z:%d A:%d B:%d C:%d",
               &axis_positions[0], &axis_positions[1], &axis_positions[2],
               &axis_positions[3], &axis_positions[4], &axis_positions[5]);

        // Update der UI Elemente basierend auf den neuen Werten
        update_ui();
    }
}

void create_cnc_ui(lv_obj_t *parent)
{
    // Menü erstellen
    lv_obj_t *menu = lv_menu_create(parent);
    lv_obj_set_size(menu, 480, 320);
    lv_obj_center(menu);

    // Hauptseite des Menüs
    lv_obj_t *root_page = lv_menu_page_create(menu, "CNC Controller");

    // Abschnitt für Achsenpositionen
    lv_obj_t *axis_section = lv_menu_section_create(root_page);

    for (int i = 0; i < axis_count; i++)
    {
        lv_obj_t *label = lv_label_create(axis_section);
        char buf[32];
        sprintf(buf, "Axis %c: %d", 'X' + i, axis_positions[i]);
        lv_label_set_text(label, buf);
    }

    // Abschnitt für Limit Switches
    lv_obj_t *limit_section = lv_menu_section_create(root_page);
    for (int i = 0; i < axis_count; i++)
    {
        lv_obj_t *label = lv_label_create(limit_section);
        char buf[32];
        sprintf(buf, "Limit %c: %s", 'X' + i, limit_switches[i] ? "ON" : "OFF");
        lv_label_set_text(label, buf);
    }

    // Abschnitt für Geräte
    lv_obj_t *device_section = lv_menu_section_create(root_page);

    lv_obj_t *air_btn = lv_btn_create(device_section);
    lv_obj_set_width(air_btn, 150);
    lv_obj_t *label = lv_label_create(air_btn);
    lv_label_set_text(label, "Air");

    lv_obj_t *coolant_btn = lv_btn_create(device_section);
    lv_obj_set_width(coolant_btn, 150);
    label = lv_label_create(coolant_btn);
    lv_label_set_text(label, "Coolant");

    // Abschnitt für Einstellungen
    lv_obj_t *settings_section = lv_menu_section_create(root_page);

    // lv_obj_t *vel_slider = create_slider(settings_section, LV_SYMBOL_SETTINGS, "Velocity", 0, 150, 120, velocity_slider_event_cb);
    // lv_obj_t *acc_slider = create_slider(settings_section, LV_SYMBOL_SETTINGS, "Acceleration", 0, 150, 50, acceleration_slider_event_cb);
    // lv_obj_t *other_slider = create_slider(settings_section, LV_SYMBOL_SETTINGS, "Other", 0, 150, 80, weight_limit_slider_event_cb);

    // Hauptseite zum Menü hinzufügen
    lv_menu_set_page(menu, root_page);
}

// Beispielhafte Funktion zum Erstellen eines Sliders
// static lv_obj_t *create_slider(lv_obj_t *parent, const char *icon, const char *txt, int32_t min, int32_t max, int32_t val)
// {
//     lv_obj_t *obj = lv_menu_item_create(parent, NULL, txt, NULL, NULL);

//     lv_obj_t *slider = lv_slider_create(obj);
//     lv_obj_set_flex_grow(slider, 1);
//     lv_slider_set_range(slider, min, max);
//     lv_slider_set_value(slider, val, LV_ANIM_OFF);

//     return obj;
// }

void update_ui()
{
    // // Aktualisiere die Achsenpositionen
    // lv_obj_t *axis_section = ...; // Verweis auf die Achsen Sektion
    // for (int i = 0; i < axis_count; i++)
    // {
    //     lv_obj_t *label = ...; // Verweis auf das entsprechende Label
    //     char buf[32];
    //     sprintf(buf, "Axis %c: %d", 'X' + i, axis_positions[i]);
    //     lv_label_set_text(label, buf);
    // }

    // // Aktualisiere die Limit Switches
    // lv_obj_t *limit_section = ...; // Verweis auf die Limit Sektion
    // for (int i = 0; i < axis_count; i++)
    // {
    //     lv_obj_t *label = ...; // Verweis auf das entsprechende Label
    //     char buf[32];
    //     sprintf(buf, "Limit %c: %s", 'X' + i, limit_switches[i] ? "ON" : "OFF");
    //     lv_label_set_text(label, buf);
    // }

    // // Aktualisiere den Status der Geräte (Air, Coolant)
    // lv_obj_t *air_btn = ...; // Verweis auf den Air Button
    // lv_obj_t *coolant_btn = ...; // Verweis auf den Coolant Button

    // lv_obj_t *label = lv_label_get_text(lv_obj_get_child(air_btn, NULL));
    // lv_label_set_text(label, air_status ? "Air: ON" : "Air: OFF");

    // label = lv_label_get_text(lv_obj_get_child(coolant_btn, NULL));
    // lv_label_set_text(label, coolant_status ? "Coolant: ON" : "Coolant: OFF");
}

#endif