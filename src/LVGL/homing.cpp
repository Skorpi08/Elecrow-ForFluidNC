#ifdef USE_LVGL
#include "main.h"

void img_button_event_cb(lv_event_t *e)
{
    int index = (int)lv_obj_get_user_data(lv_event_get_target(e)); // Index des Tabs basierend auf den Benutzerdaten
    lv_tabview_set_act(ui.screen_1_tabview_1, index, LV_ANIM_OFF);
}

void tab_changed_event_cb(lv_event_t *e)
{
    uint32_t act_tab = lv_tabview_get_tab_act(lv_event_get_target(e)); // Aktiven Tab ermitteln
    for (int i = 0; i < 8; i++)
    {
        lv_color_t bg_color = (i == act_tab) ? lv_color_hex(0x303030) : lv_color_hex(0x000000);
        lv_obj_set_style_bg_color(ui.tab_containers[i], bg_color, LV_PART_MAIN);
    }
}

void screen_1_btn_axis_down_event_handler(lv_event_t *e)
{
    lv_obj_t *img = (lv_obj_t *)lv_event_get_user_data(e);
    if (lv_event_get_code(e) == LV_EVENT_PRESSED)
    {
        lv_obj_set_style_img_recolor(img, lv_color_hex(0x00a8ff), LV_PART_MAIN);
        lv_obj_set_style_img_recolor_opa(img, 255, 0);
        lv_obj_set_style_text_color(img, lv_color_hex(0x00a8ff), LV_PART_MAIN);

        // lv_obj_set_style_bg_color(img, lv_color_hex(0x00a8ff), LV_PART_MAIN);
        // lv_obj_set_style_bg_opa(img, 255, 0);
    }
    else if (lv_event_get_code(e) == LV_EVENT_RELEASED)
    {
        lv_obj_set_style_text_color(img, lv_color_hex(0x6b6b6b), LV_PART_MAIN);
        lv_obj_set_style_img_recolor_opa(img, 0, 0);
        // lv_obj_set_style_bg_opa(img, 0, 0);
    }
}

static void screen_1_sw_1_event_handler(lv_event_t *e)
{
    bool state_checked = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    state_checked ? lv_obj_add_flag(ui.screen_1_label_inc, LV_OBJ_FLAG_HIDDEN) : lv_obj_clear_flag(ui.screen_1_label_inc, LV_OBJ_FLAG_HIDDEN);
    state_checked ? lv_obj_add_flag(ui.screen_1_label_rate, LV_OBJ_FLAG_HIDDEN) : lv_obj_clear_flag(ui.screen_1_label_rate, LV_OBJ_FLAG_HIDDEN);
}

// Funktion zum Aktualisieren der Texte auf Basis von axis_index
void update_texts()
{
    lv_label_set_text(ui.screen_1_label_axis, &ui.axesNames[(ui.axis_index + 1) % my_n_axis]);
    lv_label_set_text_fmt(lv_obj_get_child(ui.screen_1_btn_axis_down, 0), "%c", ui.axesNames[ui.axis_index % my_n_axis]);
    lv_label_set_text_fmt(lv_obj_get_child(ui.screen_1_btn_axis_up, 0), "%c", ui.axesNames[(ui.axis_index + 2) % my_n_axis]);
}

// Callback-Funktion für den oberen Button
void btn_up_cb(lv_event_t *e)
{
    ui.axis_index = (ui.axis_index + 1) % my_n_axis;
    update_texts();
}

// Callback-Funktion für den unteren Button
void btn_down_cb(lv_event_t *e)
{
    ui.axis_index = (ui.axis_index + 5) % my_n_axis; // Rückwärts: -1 (entspricht +5 mod 6)
    update_texts();
}

void update_label()
{
    static char buf[10];
    snprintf(buf, sizeof(buf), "%.2f", ui.inc_value);
    lv_label_set_text(ui.screen_1_label_inc, buf);
}

void btn_increase_cb(lv_event_t *e)
{
    ui.inc_value += 0.1;
    update_label();
}

void btn_decrease_cb(lv_event_t *e)
{
    if (ui.inc_value > 0.1)
    {
        ui.inc_value -= 0.1;
        update_label();
    }
}

void moving(const char *v, float inc_value, int v_val)
{
    char command[50];

    // Gemeinsamen Teil des Befehls vorbereiten
    snprintf(command, sizeof(command), "%sG91 Z%s%d", 
             lv_obj_has_state(ui.screen_1_sw_1, LV_STATE_CHECKED) ? "$J=" : "G92 F%.2f ", 
             v, v_val);

    // Nur im "G92"-Fall wird die Feedrate benötigt
    if (!lv_obj_has_state(ui.screen_1_sw_1, LV_STATE_CHECKED))
    {
        snprintf(command, sizeof(command), command, inc_value);
    }

    fnc_send_line(command, 0);
}

void move_plus(lv_event_t *e)
{
    moving("", ui.inc_value, ui.v_val);
}

void move_minus(lv_event_t *e)
{
    moving("-", ui.inc_value, ui.v_val);
}

void tab2(lv_obj_t *tab)
{
    lv_obj_t *slider = lv_slider_create(tab);
    lv_obj_set_width(slider, 400);
    lv_obj_center(slider);
}
void tab3(lv_obj_t *tab)
{
    // Write codes screen_1_roller_1
    ui.screen_1_roller_1 = lv_roller_create(tab);
    lv_roller_set_options(ui.screen_1_roller_1, "X\nY\nZ\nA\nB\nC", LV_ROLLER_MODE_INFINITE);
    lv_obj_set_pos(ui.screen_1_roller_1, 6, 229);
    lv_obj_set_width(ui.screen_1_roller_1, 110);

    // Write style for screen_1_roller_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui.screen_1_roller_1, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui.screen_1_roller_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui.screen_1_roller_1, lv_color_hex(0xc70000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui.screen_1_roller_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui.screen_1_roller_1, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui.screen_1_roller_1, &lv_font_montserrat_80, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui.screen_1_roller_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui.screen_1_roller_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui.screen_1_roller_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui.screen_1_roller_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui.screen_1_roller_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui.screen_1_roller_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for screen_1_roller_1, Part: LV_PART_MAIN, State: LV_STATE_FOCUSED.
    lv_obj_set_style_radius(ui.screen_1_roller_1, 50, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui.screen_1_roller_1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui.screen_1_roller_1, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_font(ui.screen_1_roller_1, &lv_font_montserrat_80, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_opa(ui.screen_1_roller_1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_align(ui.screen_1_roller_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(ui.screen_1_roller_1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_pad_left(ui.screen_1_roller_1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_pad_right(ui.screen_1_roller_1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui.screen_1_roller_1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    // Write style for screen_1_roller_1, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui.screen_1_roller_1, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui.screen_1_roller_1, lv_color_hex(0x2195f6), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui.screen_1_roller_1, &lv_font_montserrat_80, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui.screen_1_roller_1, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui.screen_1_roller_1, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED | LV_STATE_DEFAULT);

    // Write style for screen_1_roller_1, Part: LV_PART_SELECTED, State: LV_STATE_FOCUSED.
    lv_obj_set_style_bg_opa(ui.screen_1_roller_1, 0, LV_PART_SELECTED | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui.screen_1_roller_1, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_FOCUSED);
    lv_obj_set_style_text_font(ui.screen_1_roller_1, &lv_font_montserrat_80, LV_PART_SELECTED | LV_STATE_FOCUSED);
    lv_obj_set_style_text_opa(ui.screen_1_roller_1, 255, LV_PART_SELECTED | LV_STATE_FOCUSED);
    lv_obj_set_style_text_align(ui.screen_1_roller_1, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED | LV_STATE_FOCUSED);

    lv_roller_set_visible_row_count(ui.screen_1_roller_1, 1);
}
void tab4(lv_obj_t *tab)
{
}
void tab5(lv_obj_t *tab)
{
}
void tab6(lv_obj_t *tab)
{
}
void tab7(lv_obj_t *tab)
{
}
void tab8(lv_obj_t *tab)
{
}
void tab1(lv_obj_t *tab)
{
    ui.screen_1_img_inc_plus = lv_img_create(tab);
    lv_img_set_src(ui.screen_1_img_inc_plus, &_pic1_alpha_75x161);
    lv_img_set_pivot(ui.screen_1_img_inc_plus, 1, 1);
    lv_img_set_angle(ui.screen_1_img_inc_plus, 0);
    lv_obj_set_pos(ui.screen_1_img_inc_plus, 98, 96);
    lv_obj_set_size(ui.screen_1_img_inc_plus, 75, 161);

    ui.screen_1_img_inc_minus = lv_img_create(tab);
    lv_img_set_src(ui.screen_1_img_inc_minus, &_pic1_alpha_75x161);
    lv_img_set_pivot(ui.screen_1_img_inc_minus, 1, 1);
    lv_img_set_angle(ui.screen_1_img_inc_minus, 1800);
    lv_obj_set_pos(ui.screen_1_img_inc_minus, 342, 252);
    lv_obj_set_size(ui.screen_1_img_inc_minus, 75, 161);

    ui.screen_1_img_axis_up = lv_img_create(tab);
    lv_img_set_src(ui.screen_1_img_axis_up, &_pic1_alpha_75x161);
    lv_img_set_pivot(ui.screen_1_img_axis_up, 1, 1);
    lv_img_set_angle(ui.screen_1_img_axis_up, 900);
    lv_obj_set_pos(ui.screen_1_img_axis_up, 298, 52);
    lv_obj_set_size(ui.screen_1_img_axis_up, 75, 161);

    ui.screen_1_img_axis_down = lv_img_create(tab);
    lv_img_set_src(ui.screen_1_img_axis_down, &_pic1_alpha_75x161);
    lv_img_set_pivot(ui.screen_1_img_axis_down, 1, 1);
    lv_img_set_angle(ui.screen_1_img_axis_down, 2700);
    lv_obj_set_pos(ui.screen_1_img_axis_down, 143, 295);
    lv_obj_set_size(ui.screen_1_img_axis_down, 75, 161);

    ui.screen_1_label_jogging = lv_label_create(tab);
    lv_label_set_text(ui.screen_1_label_jogging, "JOGGING");
    lv_label_set_long_mode(ui.screen_1_label_jogging, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_jogging, 30, 0);
    lv_obj_set_size(ui.screen_1_label_jogging, 385, 30);

    lv_obj_set_style_border_width(ui.screen_1_label_jogging, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_jogging, 20, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_jogging, lv_color_hex(0x00a8ff), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_jogging, &lv_font_montserrat_30, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_jogging, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_jogging, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_jogging, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_jogging, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_jogging, 255, LV_PART_MAIN);
    lv_obj_set_style_bg_color(ui.screen_1_label_jogging, lv_color_hex(0xd7d7d7), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(ui.screen_1_label_jogging, LV_GRAD_DIR_NONE, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_jogging, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_jogging, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_jogging, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_jogging, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_jogging, 0, LV_PART_MAIN);

    ui.screen_1_label_axis = lv_label_create(tab);
    lv_label_set_text(ui.screen_1_label_axis, "Z");
    lv_label_set_long_mode(ui.screen_1_label_axis, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_axis, 194, 132);
    lv_obj_set_size(ui.screen_1_label_axis, 55, 74);

    lv_obj_set_style_border_width(ui.screen_1_label_axis, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_axis, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_axis, lv_color_hex(0x00a8ff), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_axis, &lv_font_montserrat_80, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_axis, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_axis, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_axis, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_axis, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_axis, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_axis, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_axis, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_axis, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_axis, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_axis, 0, LV_PART_MAIN);

    ui.screen_1_sw_1 = lv_switch_create(tab);
    lv_obj_set_pos(ui.screen_1_sw_1, 201, 373);
    lv_obj_set_size(ui.screen_1_sw_1, 65, 30);
    lv_obj_set_style_radius(ui.screen_1_sw_1, 15, LV_PART_MAIN);
    lv_obj_add_event_cb(ui.screen_1_sw_1, screen_1_sw_1_event_handler, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_set_style_bg_opa(ui.screen_1_sw_1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui.screen_1_sw_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui.screen_1_sw_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui.screen_1_sw_1, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);

    // Write style for screen_1_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui.screen_1_sw_1, 255, LV_PART_KNOB);
    lv_obj_set_style_bg_color(ui.screen_1_sw_1, lv_color_hex(0xffffff), LV_PART_KNOB);
    lv_obj_set_style_bg_grad_dir(ui.screen_1_sw_1, LV_GRAD_DIR_NONE, LV_PART_KNOB);
    lv_obj_set_style_border_width(ui.screen_1_sw_1, 0, LV_PART_KNOB);
    lv_obj_set_style_radius(ui.screen_1_sw_1, 10, LV_PART_KNOB);

    // Write codes screen_1_label_continuous
    ui.screen_1_label_continuous = lv_label_create(tab);
    lv_label_set_text(ui.screen_1_label_continuous, "continuous");
    lv_label_set_long_mode(ui.screen_1_label_continuous, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_continuous, 178, 410);
    lv_obj_set_size(ui.screen_1_label_continuous, 115, 17);

    // Write style for screen_1_label_continuous, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_label_continuous, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_continuous, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_continuous, lv_color_hex(0x00a8ff), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_continuous, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_continuous, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_continuous, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_continuous, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_continuous, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_continuous, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_continuous, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_continuous, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_continuous, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_continuous, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_continuous, 0, LV_PART_MAIN);

    // Write codes screen_1_label_rate
    ui.screen_1_label_rate = lv_label_create(tab);
    lv_label_set_text(ui.screen_1_label_rate, "Rate: 010.00");
    lv_label_set_long_mode(ui.screen_1_label_rate, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_rate, 121, 327);
    lv_obj_set_size(ui.screen_1_label_rate, 210, 25);

    // Write style for screen_1_label_rate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_label_rate, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_rate, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_rate, lv_color_hex(0x00a8ff), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_rate, &lv_font_montserrat_30, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_rate, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_rate, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_rate, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_rate, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_rate, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_rate, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_rate, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_rate, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_rate, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_rate, 0, LV_PART_MAIN);

    // Write codes screen_1_label_inc
    ui.screen_1_label_inc = lv_label_create(tab);
    lv_label_set_text(ui.screen_1_label_inc, "Inc: 001.00");
    lv_label_set_long_mode(ui.screen_1_label_inc, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_inc, 121, 296);
    lv_obj_set_size(ui.screen_1_label_inc, 210, 25);

    // Write style for screen_1_label_inc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_label_inc, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_inc, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_inc, lv_color_hex(0x00a8ff), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_inc, &lv_font_montserrat_30, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_inc, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_inc, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_inc, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_inc, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_inc, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_inc, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_inc, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_inc, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_inc, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_inc, 0, LV_PART_MAIN);

    // Write codes screen_1_label_next
    ui.screen_1_label_next = lv_label_create(tab);
    lv_label_set_text(ui.screen_1_label_next, "" LV_SYMBOL_NEXT "");
    lv_label_set_long_mode(ui.screen_1_label_next, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_next, 336, 351);
    lv_obj_set_size(ui.screen_1_label_next, 85, 85);
    lv_obj_add_flag(ui.screen_1_label_next, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui.screen_1_label_next, screen_1_btn_axis_down_event_handler, LV_EVENT_ALL, ui.screen_1_label_next);
    lv_obj_add_event_cb(ui.screen_1_label_next, move_minus, LV_EVENT_CLICKED, NULL);

    // Write style for screen_1_label_next, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_label_next, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_next, 5, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_next, lv_color_hex(0x6b6b6b), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_next, &lv_font_montserrat_80, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_next, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_next, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_next, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_next, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_next, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_next, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_next, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_next, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_next, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_next, 0, LV_PART_MAIN);

    // Write codes screen_1_label_prev
    ui.screen_1_label_prev = lv_label_create(tab);
    lv_label_set_text(ui.screen_1_label_prev, "" LV_SYMBOL_PREV "");
    lv_label_set_long_mode(ui.screen_1_label_prev, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_prev, 37, 351);
    lv_obj_set_size(ui.screen_1_label_prev, 85, 85);
    lv_obj_add_flag(ui.screen_1_label_prev, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui.screen_1_label_prev, screen_1_btn_axis_down_event_handler, LV_EVENT_ALL, ui.screen_1_label_prev);
    lv_obj_add_event_cb(ui.screen_1_label_prev, move_plus, LV_EVENT_CLICKED, NULL);

    // Write style for screen_1_label_prev, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_label_prev, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_prev, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_prev, lv_color_hex(0x6b6b6b), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_prev, &lv_font_montserrat_80, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_prev, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_prev, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_prev, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_prev, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_prev, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_prev, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_prev, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_prev, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_prev, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_prev, 0, LV_PART_MAIN);

    // Write codes screen_1_btn_inc_plus
    ui.screen_1_btn_inc_plus = lv_btn_create(tab);
    ui.screen_1_btn_inc_plus_label = lv_label_create(ui.screen_1_btn_inc_plus);
    lv_label_set_text(ui.screen_1_btn_inc_plus_label, "+");
    lv_label_set_long_mode(ui.screen_1_btn_inc_plus_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui.screen_1_btn_inc_plus_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui.screen_1_btn_inc_plus, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui.screen_1_btn_inc_plus_label, LV_PCT(100));
    lv_obj_set_pos(ui.screen_1_btn_inc_plus, 97, 112);
    lv_obj_set_size(ui.screen_1_btn_inc_plus, 65, 130);
    lv_obj_add_flag(ui.screen_1_btn_inc_plus, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui.screen_1_btn_inc_plus, screen_1_btn_axis_down_event_handler, LV_EVENT_ALL, ui.screen_1_img_inc_plus);
    lv_obj_add_event_cb(ui.screen_1_btn_inc_plus, btn_increase_cb, LV_EVENT_CLICKED, NULL);

    // Write style for screen_1_btn_inc_plus, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui.screen_1_btn_inc_plus, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(ui.screen_1_btn_inc_plus, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_btn_inc_plus, 50, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_btn_inc_plus, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_btn_inc_plus, lv_color_hex(0x00a8ff), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_btn_inc_plus, &lv_font_montserrat_30, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_btn_inc_plus, 255, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_btn_inc_plus, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    // Write codes screen_1_btn_inc_minus
    ui.screen_1_btn_inc_minus = lv_btn_create(tab);
    ui.screen_1_btn_inc_minus_label = lv_label_create(ui.screen_1_btn_inc_minus);
    lv_label_set_text(ui.screen_1_btn_inc_minus_label, "-");
    lv_label_set_long_mode(ui.screen_1_btn_inc_minus_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui.screen_1_btn_inc_minus_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui.screen_1_btn_inc_minus, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui.screen_1_btn_inc_minus_label, LV_PCT(100));
    lv_obj_set_pos(ui.screen_1_btn_inc_minus, 278, 110);
    lv_obj_set_size(ui.screen_1_btn_inc_minus, 65, 130);
    lv_obj_add_flag(ui.screen_1_btn_inc_minus, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui.screen_1_btn_inc_minus, screen_1_btn_axis_down_event_handler, LV_EVENT_ALL, ui.screen_1_img_inc_minus);
    lv_obj_add_event_cb(ui.screen_1_btn_inc_minus, btn_decrease_cb, LV_EVENT_CLICKED, NULL);

    // Write style for screen_1_btn_inc_minus, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui.screen_1_btn_inc_minus, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(ui.screen_1_btn_inc_minus, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_btn_inc_minus, 50, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_btn_inc_minus, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_btn_inc_minus, lv_color_hex(0x00a8ff), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_btn_inc_minus, &lv_font_montserrat_30, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_btn_inc_minus, 255, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_btn_inc_minus, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    // Write codes screen_1_btn_axis_down
    ui.screen_1_btn_axis_down = lv_btn_create(tab);
    ui.screen_1_btn_axis_down_label = lv_label_create(ui.screen_1_btn_axis_down);
    lv_label_set_text(ui.screen_1_btn_axis_down_label, "Z");
    lv_label_set_long_mode(ui.screen_1_btn_axis_down_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui.screen_1_btn_axis_down_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui.screen_1_btn_axis_down, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui.screen_1_btn_axis_down_label, LV_PCT(100));
    lv_obj_set_pos(ui.screen_1_btn_axis_down, 159, 230);
    lv_obj_set_size(ui.screen_1_btn_axis_down, 130, 65);
    lv_obj_add_flag(ui.screen_1_btn_axis_down, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui.screen_1_btn_axis_down, screen_1_btn_axis_down_event_handler, LV_EVENT_ALL, ui.screen_1_img_axis_down);
    lv_obj_add_event_cb(ui.screen_1_btn_axis_down, btn_down_cb, LV_EVENT_CLICKED, NULL);
    // Write style for screen_1_btn_axis_down, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui.screen_1_btn_axis_down, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(ui.screen_1_btn_axis_down, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_btn_axis_down, 50, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_btn_axis_down, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_btn_axis_down, lv_color_hex(0x00a8ff), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_btn_axis_down, &lv_font_montserrat_30, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_btn_axis_down, 255, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_btn_axis_down, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    // Write codes screen_1_btn_axis_up
    ui.screen_1_btn_axis_up = lv_btn_create(tab);
    ui.screen_1_btn_axis_up_label = lv_label_create(ui.screen_1_btn_axis_up);
    lv_label_set_text(ui.screen_1_btn_axis_up_label, "Z");
    lv_label_set_long_mode(ui.screen_1_btn_axis_up_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui.screen_1_btn_axis_up_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui.screen_1_btn_axis_up, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui.screen_1_btn_axis_up_label, LV_PCT(100));
    lv_obj_set_pos(ui.screen_1_btn_axis_up, 155, 55);
    lv_obj_set_size(ui.screen_1_btn_axis_up, 130, 65);
    lv_obj_add_flag(ui.screen_1_btn_axis_up, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui.screen_1_btn_axis_up, screen_1_btn_axis_down_event_handler, LV_EVENT_ALL, ui.screen_1_img_axis_up);
    lv_obj_add_event_cb(ui.screen_1_btn_axis_up, btn_up_cb, LV_EVENT_CLICKED, NULL);

    // Write style for screen_1_btn_axis_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui.screen_1_btn_axis_up, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(ui.screen_1_btn_axis_up, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_btn_axis_up, 50, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_btn_axis_up, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_btn_axis_up, lv_color_hex(0x00a8ff), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_btn_axis_up, &lv_font_montserrat_30, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_btn_axis_up, 255, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_btn_axis_up, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
}

typedef void (*tab_content_func_t)(lv_obj_t *tab);
static const tab_content_func_t tab_content_funcs[8] = {
    tab1, tab2, tab3, tab2, tab2, tab2, tab2, tab2};

void lvgl_UI()
{
    // Write codes screen_1
    ui.screen_1 = lv_obj_create(NULL);
    lv_scr_load(ui.screen_1);
    lv_obj_set_style_bg_color(ui.screen_1, lv_color_hex(BLACK), LV_PART_MAIN);

    ui.FluidNCLogo = lv_img_create(ui.screen_1);
    lv_img_set_src(ui.FluidNCLogo, &FluidNC);
    lv_obj_set_style_align(ui.FluidNCLogo, LV_ALIGN_CENTER, LV_PART_MAIN);
    lv_task_handler();
    delay(1000);
    // Write codes screen_1_cont_1
    ui.screen_1_cont_1 = lv_obj_create(ui.screen_1);
    lv_obj_set_pos(ui.screen_1_cont_1, 0, 0);
    lv_obj_set_size(ui.screen_1_cont_1, 270, 480);
    lv_obj_set_scrollbar_mode(ui.screen_1_cont_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_1_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_cont_1, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_cont_1, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_cont_1, 255, LV_PART_MAIN);
    lv_obj_set_style_bg_color(ui.screen_1_cont_1, lv_color_hex(0x1c1a17), LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(ui.screen_1_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_cont_1, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_cont_1, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_cont_1, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_cont_1, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_cont_1, 0, LV_PART_MAIN);

    // Write codes screen_1_img_FNC
    ui.screen_1_img_FNC = lv_img_create(ui.screen_1_cont_1);
    lv_obj_add_flag(ui.screen_1_img_FNC, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui.screen_1_img_FNC, &_FluidNC_alpha_240x93);
    lv_img_set_pivot(ui.screen_1_img_FNC, 1, 1);
    lv_img_set_angle(ui.screen_1_img_FNC, 0);
    lv_obj_set_pos(ui.screen_1_img_FNC, 14, 5);
    lv_obj_set_size(ui.screen_1_img_FNC, 240, 93);

    // Write codes MyState
    ui.MyState = lv_label_create(ui.screen_1_cont_1);
    lv_label_set_text(ui.MyState, "Please reset");
    lv_label_set_long_mode(ui.MyState, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.MyState, 0, 119);
    lv_obj_set_size(ui.MyState, 270, 27);
    lv_obj_set_style_text_color(ui.MyState, lv_color_hex(YELLOW), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.MyState, &lv_font_montserrat_30, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.MyState, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    // Write codes screen_1_label_gcodes
    ui.screen_1_label_gcodes = lv_label_create(ui.screen_1_cont_1);
    lv_label_set_text(ui.screen_1_label_gcodes, "G21 G54 G91");
    lv_label_set_long_mode(ui.screen_1_label_gcodes, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_gcodes, 60, 354);
    lv_obj_set_size(ui.screen_1_label_gcodes, 200, 15);

    // Write style for screen_1_label_gcodes, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_label_gcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_gcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_gcodes, lv_color_hex(0x5abd68), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_gcodes, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_gcodes, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_gcodes, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_gcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_gcodes, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_gcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_gcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_gcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_gcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_gcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_gcodes, 0, LV_PART_MAIN);

    // Write codes screen_1_label_mcodes
    ui.screen_1_label_mcodes = lv_label_create(ui.screen_1_cont_1);
    lv_label_set_text(ui.screen_1_label_mcodes, "M3 M7 M8");
    lv_label_set_long_mode(ui.screen_1_label_mcodes, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_mcodes, 60, 372);
    lv_obj_set_size(ui.screen_1_label_mcodes, 200, 15);

    // Write style for screen_1_label_mcodes, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_label_mcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_mcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_mcodes, lv_color_hex(0x5abd68), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_mcodes, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_mcodes, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_mcodes, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_mcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_mcodes, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_mcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_mcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_mcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_mcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_mcodes, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_mcodes, 0, LV_PART_MAIN);

    // Write codes screen_1_label_spindle_speed
    ui.screen_1_label_spindle_speed = lv_label_create(ui.screen_1_cont_1);
    lv_label_set_text(ui.screen_1_label_spindle_speed, "F1000 S2400");
    lv_label_set_long_mode(ui.screen_1_label_spindle_speed, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_spindle_speed, 60, 390);
    lv_obj_set_size(ui.screen_1_label_spindle_speed, 200, 15);

    // Write style for screen_1_label_spindle_speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_label_spindle_speed, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_spindle_speed, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_spindle_speed, lv_color_hex(0x5abd68), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_spindle_speed, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_spindle_speed, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_spindle_speed, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_spindle_speed, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_spindle_speed, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_spindle_speed, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_spindle_speed, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_spindle_speed, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_spindle_speed, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_spindle_speed, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_spindle_speed, 0, LV_PART_MAIN);

    // Write codes screen_1_label_fro_percent
    ui.screen_1_label_fro_percent = lv_label_create(ui.screen_1_cont_1);
    lv_label_set_text(ui.screen_1_label_fro_percent, "FRO: 100%");
    lv_label_set_long_mode(ui.screen_1_label_fro_percent, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_fro_percent, 60, 408);
    lv_obj_set_size(ui.screen_1_label_fro_percent, 200, 15);

    // Write style for screen_1_label_fro_percent, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_label_fro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_fro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_fro_percent, lv_color_hex(0x5abd68), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_fro_percent, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_fro_percent, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_fro_percent, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_fro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_fro_percent, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_fro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_fro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_fro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_fro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_fro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_fro_percent, 0, LV_PART_MAIN);

    // Write codes screen_1_label_sro_percent
    ui.screen_1_label_sro_percent = lv_label_create(ui.screen_1_cont_1);
    lv_label_set_text(ui.screen_1_label_sro_percent, "SRO: 100%");
    lv_label_set_long_mode(ui.screen_1_label_sro_percent, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_sro_percent, 60, 426);
    lv_obj_set_size(ui.screen_1_label_sro_percent, 200, 15);

    // Write style for screen_1_label_sro_percent, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_label_sro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_sro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_sro_percent, lv_color_hex(0x5abd68), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_sro_percent, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_sro_percent, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_sro_percent, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_sro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_sro_percent, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_sro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_sro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_sro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_sro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_sro_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_sro_percent, 0, LV_PART_MAIN);

    // Write codes screen_1_label_job_percent
    ui.screen_1_label_job_percent = lv_label_create(ui.screen_1_cont_1);
    lv_label_set_text(ui.screen_1_label_job_percent, "Job: 67%");
    lv_label_set_long_mode(ui.screen_1_label_job_percent, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui.screen_1_label_job_percent, 60, 444);
    lv_obj_set_size(ui.screen_1_label_job_percent, 200, 15);

    // Write style for screen_1_label_job_percent, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui.screen_1_label_job_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.screen_1_label_job_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.screen_1_label_job_percent, lv_color_hex(0x5abd68), LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.screen_1_label_job_percent, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_opa(ui.screen_1_label_job_percent, 255, LV_PART_MAIN);
    lv_obj_set_style_text_letter_space(ui.screen_1_label_job_percent, 2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui.screen_1_label_job_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.screen_1_label_job_percent, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.screen_1_label_job_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_top(ui.screen_1_label_job_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui.screen_1_label_job_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui.screen_1_label_job_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui.screen_1_label_job_percent, 0, LV_PART_MAIN);
    lv_obj_set_style_shadow_width(ui.screen_1_label_job_percent, 0, LV_PART_MAIN);

    // Write codes screen_1_tabview_1
    ui.screen_1_tabview_1 = lv_tabview_create(ui.screen_1, LV_DIR_RIGHT, 0);
    lv_obj_set_pos(ui.screen_1_tabview_1, 270, 0);
    lv_obj_set_size(ui.screen_1_tabview_1, 530 - 60, 480);
    lv_obj_set_style_bg_color(ui.screen_1_tabview_1, lv_color_hex(0x303030), LV_PART_MAIN);
    lv_obj_clear_flag(lv_tabview_get_content(ui.screen_1_tabview_1), LV_OBJ_FLAG_SCROLLABLE);

    // update_texts();
    // Bilder für Buttons
    static const lv_img_dsc_t *img_buttons[8] = {
        &hometp, &jogtp, &probetp, &statustp, &macrostp, &powertp, &abouttp, &filestp};

    const int button_width = 60;
    const int button_height = 60;
    const int margin = 0;

    for (int i = 0; i < 8; i++)
    {
        lv_obj_t *tab = lv_tabview_add_tab(ui.screen_1_tabview_1, "");
        tab_content_funcs[i](tab);

        // Erstelle den Container für jeden Button
        ui.tab_containers[i] = lv_obj_create(lv_scr_act());
        lv_obj_set_style_border_width(ui.tab_containers[i], 0, LV_PART_MAIN);
        lv_obj_set_style_radius(ui.tab_containers[i], 0, LV_PART_MAIN);
        lv_obj_set_size(ui.tab_containers[i], button_width, button_height);
        lv_obj_set_pos(ui.tab_containers[i], LCD_WIDTH - button_width - margin, i * (button_height + margin));
        lv_obj_set_style_bg_color(ui.tab_containers[i], lv_color_hex(0x000000), LV_PART_MAIN); // Standard Schwarz

        // Erstelle den Button (Bild) innerhalb des Containers
        lv_obj_t *btn = lv_img_create(ui.tab_containers[i]);
        lv_img_set_src(btn, img_buttons[i]);
        lv_obj_center(btn);

        // Setze den Container als User Data für den Button
        lv_obj_set_user_data(btn, (void *)i); // Setze den Index für den Tab
        lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(btn, img_button_event_cb, LV_EVENT_CLICKED, NULL);

        lv_obj_clear_flag(ui.tab_containers[i], LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_clear_flag(tab, LV_OBJ_FLAG_SCROLLABLE);
    }
    // Füge den Event-Callback für Tab-Wechsel hinzu
    lv_obj_add_event_cb(ui.screen_1_tabview_1, tab_changed_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
}

#endif