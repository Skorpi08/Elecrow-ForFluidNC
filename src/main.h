#include "hardware.h"
#include "GrblParserC.h"

#ifdef USE_LVGL
#include <lvgl.h>

#define _pic1_alpha_75x161 pic
#define _FluidNC_alpha_240x93 FluidNC

LV_IMG_DECLARE(pic);
LV_IMG_DECLARE(FluidNC);
LV_IMG_DECLARE(hometp);
LV_IMG_DECLARE(jogtp);
LV_IMG_DECLARE(probetp);
LV_IMG_DECLARE(statustp);
LV_IMG_DECLARE(macrostp);
LV_IMG_DECLARE(powertp);
LV_IMG_DECLARE(abouttp);
LV_IMG_DECLARE(filestp);

LV_FONT_DECLARE(lv_font_montserrat_80)

typedef struct
{
    bool start = 0;
    const char *axesNames = "XYZABC";
    lv_obj_t *MyState;
    lv_obj_t *my_axis_labels[MAX_N_AXIS];
    lv_obj_t *my_limits_labels[MAX_N_AXIS];
    lv_obj_t *tab_containers[8];
    lv_obj_t *tab_buttons[8];
    lv_obj_t *tabs[8];
    lv_obj_t *FluidNCLogo;
    int axis_index = 0;
    float inc_value = 0.0;
    int v_val= 20;

    lv_obj_t *screen_1;
    lv_obj_t *screen_1_roller_1;
    lv_obj_t *screen_1_sw_1;
    lv_obj_t *screen_1_cont_1;
    lv_obj_t *screen_1_tabview_1;
    lv_obj_t *screen_1_label_gcodes;
    lv_obj_t *screen_1_label_mcodes;
    lv_obj_t *screen_1_label_spindle_speed;
    lv_obj_t *screen_1_label_fro_percent;
    lv_obj_t *screen_1_label_sro_percent;
    lv_obj_t *screen_1_label_job_percent;
    lv_obj_t *screen_1_label_jogging;
    lv_obj_t *screen_1_label_continuous;
    lv_obj_t *screen_1_label_rate;
    lv_obj_t *screen_1_label_inc;
    lv_obj_t *screen_1_label_axis;
    lv_obj_t *screen_1_label_next;
    lv_obj_t *screen_1_label_prev;
    lv_obj_t *screen_1_img_FNC;
    lv_obj_t *screen_1_img_inc_plus;
    lv_obj_t *screen_1_img_inc_minus;
    lv_obj_t *screen_1_img_axis_up;
    lv_obj_t *screen_1_img_axis_down;
    lv_obj_t *screen_1_btn_inc_plus;
    lv_obj_t *screen_1_btn_inc_plus_label;
    lv_obj_t *screen_1_btn_inc_minus;
    lv_obj_t *screen_1_btn_inc_minus_label;
    lv_obj_t *screen_1_btn_axis_down;
    lv_obj_t *screen_1_btn_axis_down_label;
    lv_obj_t *screen_1_btn_axis_up;
    lv_obj_t *screen_1_btn_axis_up_label;

} UIElements;

extern UIElements ui;

void update_texts();
void update_label();
void apply_styles();
void display_set_brightness(int brightness);
void update_axis_labels();
void settings();
void lvgl_begin();
void lvgl_UI();

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
#define DebugSerial Serial

void fnc_putstr(const char *str);
extern String myState;
extern float my_axis_positions[];
extern int my_n_axis;
extern bool myLimits[];
extern bool myProbe;
extern bool use_mm;
