#include "hardware.h"
#include "GrblParserC.h"

#ifdef USE_LVGL
#include <lvgl.h>

typedef struct
{
    const char *axesNames = "XYZABC";
    lv_obj_t *my_axis_labels[MAX_N_AXIS];
    lv_obj_t *menu;
    lv_obj_t *root_page;
    bool start = 0;

    lv_obj_t *screen;
    bool screen_del;
    lv_obj_t *screen_cont_1;
    lv_obj_t *screen_label_7;
    lv_obj_t *screen_label_8;
    lv_obj_t *screen_led_1;
    lv_obj_t *screen_label_11;
    lv_obj_t *screen_tabview_1;
    lv_obj_t *screen_tabview_1_tab_1;
    lv_obj_t *screen_tabview_1_tab_2;
    lv_obj_t *screen_tabview_1_tab_3;
    lv_obj_t *screen_tabview_1_tab_4;
    lv_obj_t *screen_tabview_1_tab_5;
    lv_obj_t *screen_table_1;
    lv_obj_t *screen_btnm_1;
    lv_obj_t *screen_tabview_2;
    lv_obj_t *screen_tabview_2_tab_1;
    lv_obj_t *screen_tabview_2_tab_2;
    lv_obj_t *screen_tabview_2_tab_3;
    lv_obj_t *screen_tabview_2_tab_4;
    lv_obj_t *screen_tabview_2_tab_5;
    lv_obj_t *screen_label_1;
    lv_obj_t *screen_label_2;
    lv_obj_t *screen_label_3;
    lv_obj_t *screen_label_4;
    lv_obj_t *screen_label_5;
    lv_obj_t *screen_label_6;
    lv_obj_t *screen_btn_1;
    lv_obj_t *screen_btn_1_label;
    lv_obj_t *screen_btn_2;
    lv_obj_t *screen_btn_2_label;
    lv_obj_t *screen_label_9;
    lv_obj_t *screen_label_10;
    lv_obj_t *screen_label_12;
    lv_obj_t *screen_label_13;
    lv_obj_t *screen_label_14;
    lv_obj_t *screen_ddlist_1;
    lv_obj_t *screen_roller_1;
    lv_obj_t *screen_spinbox_1;
    lv_obj_t *screen_spinbox_1_btn;
    lv_obj_t *screen_spinbox_1_btn_minus;
} UIElements;

extern UIElements ui;

void apply_styles();
void display_set_brightness(int brightness);
void update_axis_labels();
void settings();
void lvgl_begin();
void lvgl_UI();
void create_cnc_ui(lv_obj_t *parent);
// static void brightness_event_handler(lv_event_t *e);

#endif // #ifdef USE_LVGL

extern LGFX tft;

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define FNCSerial Serial
#define DebugSerial Serial1

void fnc_putstr(const char *str);
extern String myState;
extern float my_axis_positions[];
extern int my_n_axis;
extern bool myLimits[];
extern bool myProbe;
extern bool use_mm;
