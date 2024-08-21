#ifdef USE_LVGL
#include "main.h"

void btn_event_handler(lv_event_t *e)
{
	settings();
}
void move_x(lv_event_t *e)
{
	fnc_send_line("$J=G91 F200 Y1", 0);
}
void move_x_(lv_event_t *e)
{
	fnc_send_line("$J=G91 F200 Y-1", 0);
}
void move_y(lv_event_t *e)
{
	fnc_send_line("$J=G91 F200 X1", 0);
}
void move_y_(lv_event_t *e)
{
	fnc_send_line("$J=G91 F200 X-1", 0);
}
void move_z(lv_event_t *e)
{
	fnc_send_line("$J=G91 F200 Z-1", 0);
}
void move_z_(lv_event_t *e)
{
	fnc_send_line("$J=G91 F200 Z1", 0);
}

static char *DRO_format(int axis_index, float position)
{
	static char buf[20];
	snprintf(buf, sizeof(buf), "%c: %.2f", ui.axesNames[axis_index], position);
	return buf;
}

void lvgl_UI()
{
	// screen = lv_scr_act();
	// Write codes screen
	ui.screen = lv_obj_create(NULL);
	lv_scr_load(ui.screen);
	lv_obj_set_scrollbar_mode(ui.screen, LV_SCROLLBAR_MODE_OFF);

	// Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui.screen, 255, LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui.screen, lv_color_hex(0xeaeff3), LV_PART_MAIN);
	lv_obj_set_style_bg_grad_dir(ui.screen, LV_GRAD_DIR_NONE, LV_PART_MAIN);

	// Write codes screen_cont_1
	ui.screen_cont_1 = lv_obj_create(ui.screen);
	lv_obj_set_pos(ui.screen_cont_1, 0, 430);
	lv_obj_set_size(ui.screen_cont_1, 800, 50);
	lv_obj_set_scrollbar_mode(ui.screen_cont_1, LV_SCROLLBAR_MODE_OFF);

	// Write style for screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_cont_1, 2, LV_PART_MAIN);
	lv_obj_set_style_border_opa(ui.screen_cont_1, 255, LV_PART_MAIN);
	lv_obj_set_style_border_color(ui.screen_cont_1, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_set_style_border_side(ui.screen_cont_1, LV_BORDER_SIDE_TOP, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_cont_1, 0, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_cont_1, 255, LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui.screen_cont_1, lv_color_hex(0x7eb1db), LV_PART_MAIN);
	lv_obj_set_style_bg_grad_dir(ui.screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_cont_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_cont_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_cont_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_cont_1, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_cont_1, 0, LV_PART_MAIN);

	// Write codes screen_label_7
	ui.screen_label_7 = lv_label_create(ui.screen_cont_1);
	lv_label_set_text(ui.screen_label_7, LV_SYMBOL_WIFI);
	lv_label_set_long_mode(ui.screen_label_7, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_7, 4, 0);
	lv_obj_set_size(ui.screen_label_7, 60, 45);

	// Write style for screen_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_7, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_7, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_7, lv_color_hex(0xffffff), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_7, &lv_font_montserrat_40, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_7, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_7, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_7, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_7, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_7, 3, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_7, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_7, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_7, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_7, 0, LV_PART_MAIN);

	// Write codes screen_label_8
	ui.screen_label_8 = lv_label_create(ui.screen_cont_1);
	lv_label_set_text(ui.screen_label_8, LV_SYMBOL_SETTINGS);
	lv_label_set_long_mode(ui.screen_label_8, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_8, 736, 1);
	lv_obj_set_size(ui.screen_label_8, 60, 45);
	lv_obj_add_flag(ui.screen_label_8, LV_OBJ_FLAG_CLICKABLE);

	// Write style for screen_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_8, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_8, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_8, lv_color_hex(0xffffff), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_8, &lv_font_montserrat_40, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_8, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_8, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_8, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_8, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_8, 2, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_8, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_8, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_8, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_8, 0, LV_PART_MAIN);

	// Write codes screen_led_1
	ui.screen_led_1 = lv_led_create(ui.screen_cont_1);
	lv_led_set_brightness(ui.screen_led_1, 255);
	lv_led_set_color(ui.screen_led_1, lv_color_hex(0xff0027));
	lv_obj_set_pos(ui.screen_led_1, 78, 7);
	lv_obj_set_size(ui.screen_led_1, 30, 30);

	// Write codes screen_label_11
	ui.screen_label_11 = lv_label_create(ui.screen_cont_1);
	lv_label_set_text(ui.screen_label_11, myState.c_str());
	lv_label_set_long_mode(ui.screen_label_11, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_11, 123, 2);
	lv_obj_set_size(ui.screen_label_11, 153, 38);

	// Write style for screen_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_11, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_11, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_11, lv_color_hex(0xff0027), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_11, &lv_font_montserrat_40, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_11, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_11, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_11, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_11, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_11, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_11, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_11, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_11, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_11, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_11, 0, LV_PART_MAIN);

	// Write codes screen_tabview_1
	ui.screen_tabview_1 = lv_tabview_create(ui.screen, LV_DIR_LEFT, 70);
	lv_obj_set_pos(ui.screen_tabview_1, 0, 0);
	lv_obj_set_size(ui.screen_tabview_1, 400, 430);
	lv_obj_set_scrollbar_mode(ui.screen_tabview_1, LV_SCROLLBAR_MODE_OFF);

	// Write style for screen_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui.screen_tabview_1, 255, LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui.screen_tabview_1, lv_color_hex(0xeaeff3), LV_PART_MAIN);
	lv_obj_set_style_bg_grad_dir(ui.screen_tabview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_tabview_1, &lv_font_montserrat_22, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_tabview_1, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_tabview_1, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_tabview_1, 16, LV_PART_MAIN);
	lv_obj_set_style_border_width(ui.screen_tabview_1, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_tabview_1, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_tabview_1, 0, LV_PART_MAIN);

	// Write style state: LV_STATE_DEFAULT for &style_screen_tabview_1_extra_btnm_main_default
	static lv_style_t style_screen_tabview_1_extra_btnm_main_default;
	lv_style_init(&style_screen_tabview_1_extra_btnm_main_default);

	lv_style_set_bg_opa(&style_screen_tabview_1_extra_btnm_main_default, 255);
	lv_style_set_bg_color(&style_screen_tabview_1_extra_btnm_main_default, lv_color_hex(0x7eb1db));
	lv_style_set_bg_grad_dir(&style_screen_tabview_1_extra_btnm_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_border_width(&style_screen_tabview_1_extra_btnm_main_default, 0);
	lv_style_set_radius(&style_screen_tabview_1_extra_btnm_main_default, 0);
	lv_obj_add_style(lv_tabview_get_tab_btns(ui.screen_tabview_1), &style_screen_tabview_1_extra_btnm_main_default, LV_PART_MAIN);

	// Write style state: LV_STATE_DEFAULT for &style_screen_tabview_1_extra_btnm_items_default
	static lv_style_t style_screen_tabview_1_extra_btnm_items_default;
	lv_style_init(&style_screen_tabview_1_extra_btnm_items_default);

	lv_style_set_text_color(&style_screen_tabview_1_extra_btnm_items_default, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_screen_tabview_1_extra_btnm_items_default, &lv_font_montserrat_20);
	lv_style_set_text_opa(&style_screen_tabview_1_extra_btnm_items_default, 255);
	lv_obj_add_style(lv_tabview_get_tab_btns(ui.screen_tabview_1), &style_screen_tabview_1_extra_btnm_items_default, LV_PART_ITEMS);

	// Write style state: LV_STATE_CHECKED for &style_screen_tabview_1_extra_btnm_items_checked
	static lv_style_t style_screen_tabview_1_extra_btnm_items_checked;
	lv_style_init(&style_screen_tabview_1_extra_btnm_items_checked);

	lv_style_set_text_color(&style_screen_tabview_1_extra_btnm_items_checked, lv_color_hex(0x2195f6));
	lv_style_set_text_font(&style_screen_tabview_1_extra_btnm_items_checked, &lv_font_montserrat_20);
	lv_style_set_text_opa(&style_screen_tabview_1_extra_btnm_items_checked, 255);
	lv_style_set_border_width(&style_screen_tabview_1_extra_btnm_items_checked, 4);
	lv_style_set_border_opa(&style_screen_tabview_1_extra_btnm_items_checked, 255);
	lv_style_set_border_color(&style_screen_tabview_1_extra_btnm_items_checked, lv_color_hex(0x2195f6));
	lv_style_set_border_side(&style_screen_tabview_1_extra_btnm_items_checked, LV_BORDER_SIDE_BOTTOM);
	lv_style_set_radius(&style_screen_tabview_1_extra_btnm_items_checked, 0);
	lv_style_set_bg_opa(&style_screen_tabview_1_extra_btnm_items_checked, 255);
	lv_style_set_bg_color(&style_screen_tabview_1_extra_btnm_items_checked, lv_color_hex(0xeaeff3));
	lv_style_set_bg_grad_dir(&style_screen_tabview_1_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_tabview_get_tab_btns(ui.screen_tabview_1), &style_screen_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS | LV_STATE_CHECKED);

	// Write codes POS
	ui.screen_tabview_1_tab_1 = lv_tabview_add_tab(ui.screen_tabview_1, "POS");
	lv_obj_t *screen_tabview_1_tab_1_label = lv_label_create(ui.screen_tabview_1_tab_1);
	lv_label_set_text(screen_tabview_1_tab_1_label, "");

	// Write codes tab_2
	ui.screen_tabview_1_tab_2 = lv_tabview_add_tab(ui.screen_tabview_1, "tab_2");
	lv_obj_t *screen_tabview_1_tab_2_label = lv_label_create(ui.screen_tabview_1_tab_2);
	lv_label_set_text(screen_tabview_1_tab_2_label, "");

	// Write codes tab_3
	ui.screen_tabview_1_tab_3 = lv_tabview_add_tab(ui.screen_tabview_1, "tab_3");
	lv_obj_t *screen_tabview_1_tab_3_label = lv_label_create(ui.screen_tabview_1_tab_3);
	lv_label_set_text(screen_tabview_1_tab_3_label, "");

	// Write codes tab_4
	ui.screen_tabview_1_tab_4 = lv_tabview_add_tab(ui.screen_tabview_1, "tab_4");
	lv_obj_t *screen_tabview_1_tab_4_label = lv_label_create(ui.screen_tabview_1_tab_4);
	lv_label_set_text(screen_tabview_1_tab_4_label, "");

	// Write codes Macro
	ui.screen_tabview_1_tab_5 = lv_tabview_add_tab(ui.screen_tabview_1, "Macro");
	lv_obj_t *screen_tabview_1_tab_5_label = lv_label_create(ui.screen_tabview_1_tab_5);
	lv_label_set_text(screen_tabview_1_tab_5_label, "");

	// Write codes screen_btnm_1
	ui.screen_btnm_1 = lv_btnmatrix_create(ui.screen_tabview_1_tab_5);
	static const char *screen_btnm_1_text_map[] = {
		"Reset Z",
		"Reset X",
		"Reset Y",
		"\n",
		"To Z 0",
		"To X 0",
		"To Y 0",
		"\n",
		"7",
		"8",
		"9",
		"\n",
		"Soft\nReset",
		"Unlock",
		"Get\nState",
		"",
	};
	lv_btnmatrix_set_map(ui.screen_btnm_1, screen_btnm_1_text_map);
	lv_obj_set_pos(ui.screen_btnm_1, -12, 7);
	lv_obj_set_size(ui.screen_btnm_1, 314, 383);

	// Write style for screen_btnm_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_btnm_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_btnm_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_btnm_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_btnm_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_btnm_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_row(ui.screen_btnm_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_column(ui.screen_btnm_1, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_btnm_1, 0, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_btnm_1, 0, LV_PART_MAIN);

	// Write style for screen_btnm_1, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_btnm_1, 1, LV_PART_ITEMS);
	lv_obj_set_style_border_opa(ui.screen_btnm_1, 255, LV_PART_ITEMS);
	lv_obj_set_style_border_color(ui.screen_btnm_1, lv_color_hex(0xc9c9c9), LV_PART_ITEMS);
	lv_obj_set_style_border_side(ui.screen_btnm_1, LV_BORDER_SIDE_FULL, LV_PART_ITEMS);
	lv_obj_set_style_text_color(ui.screen_btnm_1, lv_color_hex(0xffffff), LV_PART_ITEMS);
	lv_obj_set_style_text_font(ui.screen_btnm_1, &lv_font_montserrat_20, LV_PART_ITEMS);
	lv_obj_set_style_text_opa(ui.screen_btnm_1, 255, LV_PART_ITEMS);
	lv_obj_set_style_radius(ui.screen_btnm_1, 4, LV_PART_ITEMS);
	lv_obj_set_style_bg_opa(ui.screen_btnm_1, 255, LV_PART_ITEMS);
	lv_obj_set_style_bg_color(ui.screen_btnm_1, lv_color_hex(0x2195f6), LV_PART_ITEMS);
	lv_obj_set_style_bg_grad_dir(ui.screen_btnm_1, LV_GRAD_DIR_NONE, LV_PART_ITEMS);
	lv_obj_set_style_shadow_width(ui.screen_btnm_1, 0, LV_PART_ITEMS);

	// Write codes screen_tabview_2
	ui.screen_tabview_2 = lv_tabview_create(ui.screen, LV_DIR_RIGHT, 70);
	lv_obj_set_pos(ui.screen_tabview_2, 400, 0);
	lv_obj_set_size(ui.screen_tabview_2, 400, 430);
	lv_obj_set_scrollbar_mode(ui.screen_tabview_2, LV_SCROLLBAR_MODE_OFF);

	// Write style for screen_tabview_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui.screen_tabview_2, 255, LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui.screen_tabview_2, lv_color_hex(0xeaeff3), LV_PART_MAIN);
	lv_obj_set_style_bg_grad_dir(ui.screen_tabview_2, LV_GRAD_DIR_NONE, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_tabview_2, lv_color_hex(0x4d4d4d), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_tabview_2, &lv_font_montserrat_22, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_tabview_2, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_tabview_2, 0, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_tabview_2, 0, LV_PART_MAIN);
	lv_obj_set_style_border_width(ui.screen_tabview_2, 1, LV_PART_MAIN);
	lv_obj_set_style_border_opa(ui.screen_tabview_2, 255, LV_PART_MAIN);
	lv_obj_set_style_border_color(ui.screen_tabview_2, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_set_style_border_side(ui.screen_tabview_2, LV_BORDER_SIDE_LEFT, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_tabview_2, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_tabview_2, 0, LV_PART_MAIN);

	// Write style state: LV_STATE_DEFAULT for &style_screen_tabview_2_extra_btnm_main_default
	static lv_style_t style_screen_tabview_2_extra_btnm_main_default;
	lv_style_init(&style_screen_tabview_2_extra_btnm_main_default);

	lv_style_set_bg_opa(&style_screen_tabview_2_extra_btnm_main_default, 255);
	lv_style_set_bg_color(&style_screen_tabview_2_extra_btnm_main_default, lv_color_hex(0x7eb1db));
	lv_style_set_bg_grad_dir(&style_screen_tabview_2_extra_btnm_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_border_width(&style_screen_tabview_2_extra_btnm_main_default, 0);
	lv_style_set_radius(&style_screen_tabview_2_extra_btnm_main_default, 0);
	lv_obj_add_style(lv_tabview_get_tab_btns(ui.screen_tabview_2), &style_screen_tabview_2_extra_btnm_main_default, LV_PART_MAIN);

	// Write style state: LV_STATE_DEFAULT for &style_screen_tabview_2_extra_btnm_items_default
	static lv_style_t style_screen_tabview_2_extra_btnm_items_default;
	lv_style_init(&style_screen_tabview_2_extra_btnm_items_default);

	lv_style_set_text_color(&style_screen_tabview_2_extra_btnm_items_default, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_screen_tabview_2_extra_btnm_items_default, &lv_font_montserrat_20);
	lv_style_set_text_opa(&style_screen_tabview_2_extra_btnm_items_default, 255);
	lv_obj_add_style(lv_tabview_get_tab_btns(ui.screen_tabview_2), &style_screen_tabview_2_extra_btnm_items_default, LV_PART_ITEMS);

	// Write style state: LV_STATE_CHECKED for &style_screen_tabview_2_extra_btnm_items_checked
	static lv_style_t style_screen_tabview_2_extra_btnm_items_checked;
	lv_style_init(&style_screen_tabview_2_extra_btnm_items_checked);

	lv_style_set_text_color(&style_screen_tabview_2_extra_btnm_items_checked, lv_color_hex(0x2195f6));
	lv_style_set_text_font(&style_screen_tabview_2_extra_btnm_items_checked, &lv_font_montserrat_20);
	lv_style_set_text_opa(&style_screen_tabview_2_extra_btnm_items_checked, 255);
	lv_style_set_border_width(&style_screen_tabview_2_extra_btnm_items_checked, 4);
	lv_style_set_border_opa(&style_screen_tabview_2_extra_btnm_items_checked, 255);
	lv_style_set_border_color(&style_screen_tabview_2_extra_btnm_items_checked, lv_color_hex(0x2195f6));
	lv_style_set_border_side(&style_screen_tabview_2_extra_btnm_items_checked, LV_BORDER_SIDE_BOTTOM);
	lv_style_set_radius(&style_screen_tabview_2_extra_btnm_items_checked, 0);
	lv_style_set_bg_opa(&style_screen_tabview_2_extra_btnm_items_checked, 255);
	lv_style_set_bg_color(&style_screen_tabview_2_extra_btnm_items_checked, lv_color_hex(0xeaeff3));
	lv_style_set_bg_grad_dir(&style_screen_tabview_2_extra_btnm_items_checked, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_tabview_get_tab_btns(ui.screen_tabview_2), &style_screen_tabview_2_extra_btnm_items_checked, LV_PART_ITEMS | LV_STATE_CHECKED);

	// Write codes Move
	ui.screen_tabview_2_tab_1 = lv_tabview_add_tab(ui.screen_tabview_2, "Move");
	lv_obj_t *screen_tabview_2_tab_1_label = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(screen_tabview_2_tab_1_label, "");

	// Write codes screen_label_1
	ui.screen_label_1 = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(ui.screen_label_1, LV_SYMBOL_LEFT " ");
	lv_label_set_long_mode(ui.screen_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_1, -4, 128);
	lv_obj_set_size(ui.screen_label_1, 51, 65);

	// Write style for screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_1, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_1, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_1, lv_color_hex(0x2195f6), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_1, &lv_font_montserrat_48, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_1, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_1, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_1, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_1, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_1, 0, LV_PART_MAIN);

	// Write codes screen_label_2
	ui.screen_label_2 = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(ui.screen_label_2, LV_SYMBOL_RIGHT);
	lv_label_set_long_mode(ui.screen_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_2, 139, 126);
	lv_obj_set_size(ui.screen_label_2, 60, 65);

	// Write style for screen_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_2, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_2, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_2, lv_color_hex(0x2195f6), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_2, &lv_font_montserrat_48, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_2, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_2, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_2, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_2, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_2, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_2, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_2, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_2, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_2, 0, LV_PART_MAIN);

	// Write codes screen_label_3
	ui.screen_label_3 = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(ui.screen_label_3, LV_SYMBOL_UP);
	lv_label_set_long_mode(ui.screen_label_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_3, 55, 50);
	lv_obj_set_size(ui.screen_label_3, 65, 60);

	// Write style for screen_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_3, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_3, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_3, lv_color_hex(0x2195f6), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_3, &lv_font_montserrat_48, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_3, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_3, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_3, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_3, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_3, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_3, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_3, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_3, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_3, 0, LV_PART_MAIN);

	// Write codes screen_label_4
	ui.screen_label_4 = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(ui.screen_label_4, LV_SYMBOL_DOWN);
	lv_label_set_long_mode(ui.screen_label_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_4, 59, 205);
	lv_obj_set_size(ui.screen_label_4, 60, 59);

	// Write style for screen_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_4, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_4, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_4, lv_color_hex(0x2195f6), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_4, &lv_font_montserrat_48, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_4, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_4, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_4, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_4, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_4, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_4, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_4, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_4, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_4, 0, LV_PART_MAIN);

	// Write codes screen_label_5
	ui.screen_label_5 = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(ui.screen_label_5, LV_SYMBOL_UP);
	lv_label_set_long_mode(ui.screen_label_5, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_5, 231, 50);
	lv_obj_set_size(ui.screen_label_5, 40, 50);

	// Write style for screen_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_5, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_5, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_5, lv_color_hex(0x2195f6), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_5, &lv_font_montserrat_48, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_5, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_5, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_5, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_5, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_5, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_5, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_5, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_5, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_5, 0, LV_PART_MAIN);

	// Write codes screen_label_6
	ui.screen_label_6 = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(ui.screen_label_6, LV_SYMBOL_DOWN);
	lv_label_set_long_mode(ui.screen_label_6, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_6, 231, 205);
	lv_obj_set_size(ui.screen_label_6, 40, 50);

	// Write style for screen_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_6, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_6, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_6, lv_color_hex(0x2195f6), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_6, &lv_font_montserrat_48, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_6, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_6, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_6, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_6, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_6, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_6, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_6, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_6, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_6, 0, LV_PART_MAIN);

	// Write codes screen_btn_1
	ui.screen_btn_1 = lv_btn_create(ui.screen_tabview_2_tab_1);
	ui.screen_btn_1_label = lv_label_create(ui.screen_btn_1);
	lv_label_set_text(ui.screen_btn_1_label, LV_SYMBOL_HOME);
	lv_label_set_long_mode(ui.screen_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui.screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui.screen_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui.screen_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui.screen_btn_1, 50, 115);
	lv_obj_set_size(ui.screen_btn_1, 75, 75);

	// Write style for screen_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui.screen_btn_1, 157, LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui.screen_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN);
	lv_obj_set_style_bg_grad_dir(ui.screen_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN);
	lv_obj_set_style_border_width(ui.screen_btn_1, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_btn_1, 40, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_btn_1, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_btn_1, &lv_font_montserrat_30, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_btn_1, 255, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

	// Write codes screen_btn_2
	ui.screen_btn_2 = lv_btn_create(ui.screen_tabview_2_tab_1);
	ui.screen_btn_2_label = lv_label_create(ui.screen_btn_2);
	lv_label_set_text(ui.screen_btn_2_label, LV_SYMBOL_HOME);
	lv_label_set_long_mode(ui.screen_btn_2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui.screen_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui.screen_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui.screen_btn_2_label, LV_PCT(100));
	lv_obj_set_pos(ui.screen_btn_2, 213, 115);
	lv_obj_set_size(ui.screen_btn_2, 75, 75);

	// Write style for screen_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui.screen_btn_2, 157, LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui.screen_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN);
	lv_obj_set_style_bg_grad_dir(ui.screen_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN);
	lv_obj_set_style_border_width(ui.screen_btn_2, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_btn_2, 40, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_btn_2, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_btn_2, &lv_font_montserrat_30, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_btn_2, 255, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

	// Write codes screen_label_9
	ui.screen_label_9 = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(ui.screen_label_9, "Z");
	lv_label_set_long_mode(ui.screen_label_9, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_9, 239, 22);
	lv_obj_set_size(ui.screen_label_9, 30, 28);

	// Write style for screen_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_9, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_9, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_9, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_9, &lv_font_montserrat_30, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_9, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_9, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_9, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_9, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_9, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_9, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_9, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_9, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_9, 0, LV_PART_MAIN);

	// Write codes screen_label_10
	ui.screen_label_10 = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(ui.screen_label_10, "X/Y");
	lv_label_set_long_mode(ui.screen_label_10, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_10, 47, 24);
	lv_obj_set_size(ui.screen_label_10, 81, 28);

	// Write style for screen_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_10, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_10, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_10, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_10, &lv_font_montserrat_30, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_10, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_10, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_10, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_10, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_10, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_10, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_10, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_10, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_10, 0, LV_PART_MAIN);

	// Write codes screen_label_12
	ui.screen_label_12 = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(ui.screen_label_12, "Step size XY");
	lv_label_set_long_mode(ui.screen_label_12, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_12, -1, 287);
	lv_obj_set_size(ui.screen_label_12, 165, 32);

	// Write style for screen_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_12, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_12, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_12, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_12, &lv_font_montserrat_22, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_12, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_12, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_12, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_12, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_12, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_12, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_12, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_12, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_12, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_12, 0, LV_PART_MAIN);

	// Write codes screen_label_13
	ui.screen_label_13 = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(ui.screen_label_13, "Step size Z");
	lv_label_set_long_mode(ui.screen_label_13, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_13, 0, 345);
	lv_obj_set_size(ui.screen_label_13, 150, 32);

	// Write style for screen_label_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_13, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_13, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_13, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_13, &lv_font_montserrat_22, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_13, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_13, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_13, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_13, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_13, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_13, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_13, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_13, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_13, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_13, 0, LV_PART_MAIN);

	// Write codes screen_label_14
	ui.screen_label_14 = lv_label_create(ui.screen_tabview_2_tab_1);
	lv_label_set_text(ui.screen_label_14, "Feed rate");
	lv_label_set_long_mode(ui.screen_label_14, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui.screen_label_14, -1, 395);
	lv_obj_set_size(ui.screen_label_14, 132, 32);

	// Write style for screen_label_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui.screen_label_14, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_label_14, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_label_14, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_label_14, &lv_font_montserrat_22, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_label_14, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_label_14, 2, LV_PART_MAIN);
	lv_obj_set_style_text_line_space(ui.screen_label_14, 0, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_label_14, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_label_14, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_label_14, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_label_14, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_label_14, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_label_14, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_label_14, 0, LV_PART_MAIN);

	// Write codes screen_ddlist_1
	ui.screen_ddlist_1 = lv_dropdown_create(ui.screen_tabview_2_tab_1);
	lv_dropdown_set_options(ui.screen_ddlist_1, "0.1\n0.5\n1\n10\n100");
	lv_obj_set_pos(ui.screen_ddlist_1, 185, 279);
	lv_obj_set_size(ui.screen_ddlist_1, 99, 30);

	// Write style for screen_ddlist_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui.screen_ddlist_1, lv_color_hex(0x0D3055), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_ddlist_1, &lv_font_montserrat_22, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_ddlist_1, 255, LV_PART_MAIN);
	lv_obj_set_style_border_width(ui.screen_ddlist_1, 1, LV_PART_MAIN);
	lv_obj_set_style_border_opa(ui.screen_ddlist_1, 255, LV_PART_MAIN);
	lv_obj_set_style_border_color(ui.screen_ddlist_1, lv_color_hex(0xe1e6ee), LV_PART_MAIN);
	lv_obj_set_style_border_side(ui.screen_ddlist_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_ddlist_1, 8, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_ddlist_1, 6, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_ddlist_1, 6, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_ddlist_1, 3, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_ddlist_1, 255, LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui.screen_ddlist_1, lv_color_hex(0xffffff), LV_PART_MAIN);
	lv_obj_set_style_bg_grad_dir(ui.screen_ddlist_1, LV_GRAD_DIR_NONE, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_ddlist_1, 0, LV_PART_MAIN);

	// Write style state: LV_STATE_CHECKED for &style_screen_ddlist_1_extra_list_selected_checked
	static lv_style_t style_screen_ddlist_1_extra_list_selected_checked;
	lv_style_init(&style_screen_ddlist_1_extra_list_selected_checked);

	lv_style_set_border_width(&style_screen_ddlist_1_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_screen_ddlist_1_extra_list_selected_checked, 255);
	lv_style_set_border_color(&style_screen_ddlist_1_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_ddlist_1_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_ddlist_1_extra_list_selected_checked, 3);
	lv_style_set_bg_opa(&style_screen_ddlist_1_extra_list_selected_checked, 255);
	lv_style_set_bg_color(&style_screen_ddlist_1_extra_list_selected_checked, lv_color_hex(0x00a1b5));
	lv_style_set_bg_grad_dir(&style_screen_ddlist_1_extra_list_selected_checked, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui.screen_ddlist_1), &style_screen_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

	// Write style state: LV_STATE_DEFAULT for &style_screen_ddlist_1_extra_list_main_default
	static lv_style_t style_screen_ddlist_1_extra_list_main_default;
	lv_style_init(&style_screen_ddlist_1_extra_list_main_default);

	lv_style_set_max_height(&style_screen_ddlist_1_extra_list_main_default, 90);
	lv_style_set_text_color(&style_screen_ddlist_1_extra_list_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_ddlist_1_extra_list_main_default, &lv_font_montserrat_22);
	lv_style_set_text_opa(&style_screen_ddlist_1_extra_list_main_default, 255);
	lv_style_set_border_width(&style_screen_ddlist_1_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_screen_ddlist_1_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_ddlist_1_extra_list_main_default, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_ddlist_1_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_ddlist_1_extra_list_main_default, 3);
	lv_style_set_bg_opa(&style_screen_ddlist_1_extra_list_main_default, 255);
	lv_style_set_bg_color(&style_screen_ddlist_1_extra_list_main_default, lv_color_hex(0xffffff));
	lv_style_set_bg_grad_dir(&style_screen_ddlist_1_extra_list_main_default, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui.screen_ddlist_1), &style_screen_ddlist_1_extra_list_main_default, LV_PART_MAIN);

	// Write style state: LV_STATE_DEFAULT for &style_screen_ddlist_1_extra_list_scrollbar_default
	static lv_style_t style_screen_ddlist_1_extra_list_scrollbar_default;
	lv_style_init(&style_screen_ddlist_1_extra_list_scrollbar_default);

	lv_style_set_radius(&style_screen_ddlist_1_extra_list_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_screen_ddlist_1_extra_list_scrollbar_default, 255);
	lv_style_set_bg_color(&style_screen_ddlist_1_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
	lv_style_set_bg_grad_dir(&style_screen_ddlist_1_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui.screen_ddlist_1), &style_screen_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR);

	// Write codes screen_roller_1
	ui.screen_roller_1 = lv_roller_create(ui.screen_tabview_2_tab_1);
	lv_roller_set_options(ui.screen_roller_1, "0.1\n0.5\n1\n5\n10\n100", LV_ROLLER_MODE_INFINITE);
	lv_obj_set_pos(ui.screen_roller_1, 183, 338);
	lv_obj_set_width(ui.screen_roller_1, 100);

	// Write style for screen_roller_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui.screen_roller_1, 5, LV_PART_MAIN);
	lv_obj_set_style_bg_opa(ui.screen_roller_1, 255, LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui.screen_roller_1, lv_color_hex(0xffffff), LV_PART_MAIN);
	lv_obj_set_style_bg_grad_dir(ui.screen_roller_1, LV_GRAD_DIR_NONE, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_roller_1, lv_color_hex(0x333333), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_roller_1, &lv_font_montserrat_16, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_roller_1, 255, LV_PART_MAIN);
	lv_obj_set_style_text_align(ui.screen_roller_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
	lv_obj_set_style_border_width(ui.screen_roller_1, 2, LV_PART_MAIN);
	lv_obj_set_style_border_opa(ui.screen_roller_1, 255, LV_PART_MAIN);
	lv_obj_set_style_border_color(ui.screen_roller_1, lv_color_hex(0xe6e6e6), LV_PART_MAIN);
	lv_obj_set_style_border_side(ui.screen_roller_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_roller_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_roller_1, 0, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_roller_1, 0, LV_PART_MAIN);

	// Write style for screen_roller_1, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui.screen_roller_1, 255, LV_PART_SELECTED);
	lv_obj_set_style_bg_color(ui.screen_roller_1, lv_color_hex(0x2195f6), LV_PART_SELECTED);
	lv_obj_set_style_bg_grad_dir(ui.screen_roller_1, LV_GRAD_DIR_NONE, LV_PART_SELECTED);
	lv_obj_set_style_text_color(ui.screen_roller_1, lv_color_hex(0xFFFFFF), LV_PART_SELECTED);
	lv_obj_set_style_text_font(ui.screen_roller_1, &lv_font_montserrat_22, LV_PART_SELECTED);
	lv_obj_set_style_text_opa(ui.screen_roller_1, 255, LV_PART_SELECTED);
	lv_obj_set_style_text_align(ui.screen_roller_1, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED);

	lv_roller_set_visible_row_count(ui.screen_roller_1, 1);
	// Write codes screen_spinbox_1
	ui.screen_spinbox_1 = lv_spinbox_create(ui.screen_tabview_2_tab_1);
	lv_obj_set_pos(ui.screen_spinbox_1, 174, 381);
	lv_obj_set_width(ui.screen_spinbox_1, 95);
	lv_obj_set_height(ui.screen_spinbox_1, 40);
	lv_spinbox_set_digit_format(ui.screen_spinbox_1, 5, 3);
	lv_spinbox_set_range(ui.screen_spinbox_1, -99999, 99999);
	lv_coord_t screen_spinbox_1_h = lv_obj_get_height(ui.screen_spinbox_1);
	ui.screen_spinbox_1_btn = lv_btn_create(ui.screen_tabview_2_tab_1);
	lv_obj_set_size(ui.screen_spinbox_1_btn, screen_spinbox_1_h, screen_spinbox_1_h);
	lv_obj_align_to(ui.screen_spinbox_1_btn, ui.screen_spinbox_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
	lv_obj_set_style_bg_img_src(ui.screen_spinbox_1_btn, LV_SYMBOL_PLUS, 0);
	// lv_obj_add_event_cb(ui.screen_spinbox_1_btn, lv_screen_spinbox_1_increment_event_cb, LV_EVENT_ALL, NULL);
	ui.screen_spinbox_1_btn_minus = lv_btn_create(ui.screen_tabview_2_tab_1);
	lv_obj_set_size(ui.screen_spinbox_1_btn_minus, screen_spinbox_1_h, screen_spinbox_1_h);
	lv_obj_align_to(ui.screen_spinbox_1_btn_minus, ui.screen_spinbox_1, LV_ALIGN_OUT_LEFT_MID, -5, 0);
	lv_obj_set_style_bg_img_src(ui.screen_spinbox_1_btn_minus, LV_SYMBOL_MINUS, 0);
	// lv_obj_add_event_cb(ui.screen_spinbox_1_btn_minus, lv_screen_spinbox_1_decrement_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_set_pos(ui.screen_spinbox_1, 174, 381);

	// Write style for screen_spinbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui.screen_spinbox_1, 255, LV_PART_MAIN);
	lv_obj_set_style_bg_color(ui.screen_spinbox_1, lv_color_hex(0xffffff), LV_PART_MAIN);
	lv_obj_set_style_bg_grad_dir(ui.screen_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_MAIN);
	lv_obj_set_style_border_width(ui.screen_spinbox_1, 2, LV_PART_MAIN);
	lv_obj_set_style_border_opa(ui.screen_spinbox_1, 255, LV_PART_MAIN);
	lv_obj_set_style_border_color(ui.screen_spinbox_1, lv_color_hex(0x2195f6), LV_PART_MAIN);
	lv_obj_set_style_border_side(ui.screen_spinbox_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN);
	lv_obj_set_style_pad_top(ui.screen_spinbox_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_right(ui.screen_spinbox_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_bottom(ui.screen_spinbox_1, 0, LV_PART_MAIN);
	lv_obj_set_style_pad_left(ui.screen_spinbox_1, 0, LV_PART_MAIN);
	lv_obj_set_style_text_color(ui.screen_spinbox_1, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_set_style_text_font(ui.screen_spinbox_1, &lv_font_montserrat_20, LV_PART_MAIN);
	lv_obj_set_style_text_opa(ui.screen_spinbox_1, 255, LV_PART_MAIN);
	lv_obj_set_style_text_letter_space(ui.screen_spinbox_1, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(ui.screen_spinbox_1, 5, LV_PART_MAIN);
	lv_obj_set_style_shadow_width(ui.screen_spinbox_1, 0, LV_PART_MAIN);

	// Write style for screen_spinbox_1, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui.screen_spinbox_1, lv_color_hex(0xffffff), LV_PART_CURSOR);
	lv_obj_set_style_text_font(ui.screen_spinbox_1, &lv_font_montserrat_20, LV_PART_CURSOR);
	lv_obj_set_style_text_opa(ui.screen_spinbox_1, 255, LV_PART_CURSOR);
	lv_obj_set_style_bg_opa(ui.screen_spinbox_1, 255, LV_PART_CURSOR);
	lv_obj_set_style_bg_color(ui.screen_spinbox_1, lv_color_hex(0x2195f6), LV_PART_CURSOR);
	lv_obj_set_style_bg_grad_dir(ui.screen_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_CURSOR);

	// Write style state: LV_STATE_DEFAULT for &style_screen_spinbox_1_extra_btns_main_default
	static lv_style_t style_screen_spinbox_1_extra_btns_main_default;
	lv_style_init(&style_screen_spinbox_1_extra_btns_main_default);

	lv_style_set_text_color(&style_screen_spinbox_1_extra_btns_main_default, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_screen_spinbox_1_extra_btns_main_default, &lv_font_montserrat_16);
	lv_style_set_text_opa(&style_screen_spinbox_1_extra_btns_main_default, 255);
	lv_style_set_bg_opa(&style_screen_spinbox_1_extra_btns_main_default, 255);
	lv_style_set_bg_color(&style_screen_spinbox_1_extra_btns_main_default, lv_color_hex(0x2195f6));
	lv_style_set_bg_grad_dir(&style_screen_spinbox_1_extra_btns_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_border_width(&style_screen_spinbox_1_extra_btns_main_default, 0);
	lv_style_set_radius(&style_screen_spinbox_1_extra_btns_main_default, 5);
	lv_obj_add_style(ui.screen_spinbox_1_btn, &style_screen_spinbox_1_extra_btns_main_default, LV_PART_MAIN);
	lv_obj_add_style(ui.screen_spinbox_1_btn_minus, &style_screen_spinbox_1_extra_btns_main_default, LV_PART_MAIN);

	// Write codes Probe
	ui.screen_tabview_2_tab_2 = lv_tabview_add_tab(ui.screen_tabview_2, "Probe");
	lv_obj_t *screen_tabview_2_tab_2_label = lv_label_create(ui.screen_tabview_2_tab_2);
	lv_label_set_text(screen_tabview_2_tab_2_label, "");

	// Write codes tab_3
	ui.screen_tabview_2_tab_3 = lv_tabview_add_tab(ui.screen_tabview_2, "tab_3");
	lv_obj_t *screen_tabview_2_tab_3_label = lv_label_create(ui.screen_tabview_2_tab_3);
	lv_label_set_text(screen_tabview_2_tab_3_label, "");

	// Write codes tab_4
	ui.screen_tabview_2_tab_4 = lv_tabview_add_tab(ui.screen_tabview_2, "tab_4");
	lv_obj_t *screen_tabview_2_tab_4_label = lv_label_create(ui.screen_tabview_2_tab_4);
	lv_label_set_text(screen_tabview_2_tab_4_label, "");

	// Write codes tab_5
	ui.screen_tabview_2_tab_5 = lv_tabview_add_tab(ui.screen_tabview_2, "tab_5");
	lv_obj_t *screen_tabview_2_tab_5_label = lv_label_create(ui.screen_tabview_2_tab_5);
	lv_label_set_text(screen_tabview_2_tab_5_label, "");

	lv_obj_add_flag(ui.screen_label_1, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(ui.screen_label_2, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(ui.screen_label_3, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(ui.screen_label_4, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(ui.screen_label_5, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(ui.screen_label_6, LV_OBJ_FLAG_CLICKABLE);

	lv_obj_add_event_cb(ui.screen_label_1, move_x_, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(ui.screen_label_2, move_x, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(ui.screen_label_3, move_y, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(ui.screen_label_4, move_y_, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(ui.screen_label_5, move_z, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(ui.screen_label_6, move_z_, LV_EVENT_CLICKED, NULL);
}

void update_axis_labels()
{
	if (my_n_axis > 0)
	{
		if (ui.start == 0)
		{
			for (int i = 0; i < my_n_axis; i++)
			{
				ui.my_axis_labels[i] = lv_label_create(ui.screen_tabview_1_tab_1);
				// lv_label_set_text(ui.my_axis_labels[i], DRO_format(i, my_axis_positions[i]));
				lv_obj_set_pos(ui.my_axis_labels[i], 0, 60 * i);
				// lv_table_set_row_cnt(ui.screen_table_1, my_n_axis);
				// lv_table_set_cell_value(ui.screen_table_1, i, 0, &ui.axesNames[i]);
				// lv_table_set_row_cnt(ui.screen_table_1, my_n_axis);
				// lv_table_set_cell_value(ui.screen_table_1, i, 1, DRO_format(i, my_axis_positions[i]));
			}
			ui.start = 1;
		}

		for (int i = 0; i < my_n_axis; i++)
		{

			lv_label_set_text(ui.my_axis_labels[i], DRO_format(i, my_axis_positions[i]));
		}

		lv_label_set_text(ui.screen_label_11, myState.c_str());
	}
}
#endif