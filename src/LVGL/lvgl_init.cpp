#ifdef USE_LVGL

#include "main.h"

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
    static lv_disp_drv_t disp_drv;
    static lv_disp_draw_buf_t draw_buf;
    // static lv_color_t disp_draw_buf1[LCD_WIDTH * LCD_HEIGHT / 10];
    // static lv_color_t disp_draw_buf2[LCD_WIDTH * LCD_HEIGHT / 10];
    static lv_color_t *disp_draw_buf1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * LCD_WIDTH * LCD_HEIGHT / 8,
                                                                       MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    static lv_color_t *disp_draw_buf2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * LCD_WIDTH * LCD_HEIGHT / 8,
                                                                       MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

    lv_init();
    // lv_png_init();
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf1, disp_draw_buf2, LCD_WIDTH * LCD_HEIGHT / 8);
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.full_refresh = 0;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
    lvgl_UI();
}

static char *DRO_format(int axis_index, float position)
{
    static char buf[20];
    snprintf(buf, sizeof(buf), "%c: %.2f", ui.axesNames[axis_index], position);
    return buf;
}

void update_axis_labels()
{
    if (my_n_axis > 0)
    {
        if (!ui.start)
        {

            for (int i = 0; i < my_n_axis; i++)
            {
                ui.my_axis_labels[i] = lv_label_create(ui.screen_1_cont_1);
                lv_obj_set_pos(ui.my_axis_labels[i], 60, 155 + 30 * i);
                lv_obj_set_size(ui.my_axis_labels[i], 200, 27);
                lv_obj_set_style_text_color(ui.my_axis_labels[i], lv_color_hex(0x5abd68), LV_PART_MAIN);
                lv_obj_set_style_text_font(ui.my_axis_labels[i], &lv_font_montserrat_30, LV_PART_MAIN);
                lv_obj_set_style_text_align(ui.my_axis_labels[i], LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

                ui.my_limits_labels[i] = lv_led_create(ui.screen_1_cont_1);
                lv_led_set_color(ui.my_limits_labels[i], lv_color_hex(0x00ff40));
                lv_obj_set_pos(ui.my_limits_labels[i], 15, 164 + 30 * i);
                lv_obj_set_size(ui.my_limits_labels[i], 15, 15);
            }
            ui.start = 1;
            update_label();
            update_texts();
        }

        for (int i = 0; i < my_n_axis; i++)
        {
            lv_label_set_text(ui.my_axis_labels[i], DRO_format(i, my_axis_positions[i]));
            // lv_led_set_brightness(ui.my_limits_labels[i], myLimits[i] == 1 ? 255 : 0);
            lv_obj_set_style_opa(ui.my_limits_labels[i], myLimits[i] == 1 ? 255 : 0, LV_PART_MAIN);
        }

        lv_label_set_text(ui.MyState, myState.c_str());
        lv_obj_set_style_text_color(ui.MyState, myState == "Alarm" ? lv_color_hex(RED) : myState.startsWith("Hold") ? lv_color_hex(YELLOW)
                                                                                                                    : lv_color_hex(0x5abd68),
                                    0);
    }
}

#endif