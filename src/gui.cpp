#include "gui.h"

#include "ILI9341_T4.h"
#include "lvgl.h"
#include "Statechart.h"
static ILI9341_T4::ILI9341Driver tft(TFT_CS, TFT_DC, TFT_SCK, TFT_MOSI,
                                     TFT_MISO, TFT_RST, TOUCH_CS, TOUCH_IRQ);
#define SPI_FREQ 40000000
#define LVGL_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT / 10)
static ILI9341_T4::DiffBuffStatic<8192> diff_buf_1;
static ILI9341_T4::DiffBuffStatic<8192> diff_buf_2;
DMAMEM uint16_t internal_fb[TFT_WIDTH * TFT_HEIGHT];
// static XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);
static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;
static lv_color_t lvgl_buf[LVGL_BUF_SIZE];

static lv_indev_drv_t indev_drv;

static lv_obj_t *main_screen;
static lv_obj_t *learn_screen;
static lv_obj_t *learn_state;
static lv_obj_t *learn_temperature;
static lv_obj_t *learn_time;
static lv_obj_t *learn_duty;
static lv_obj_t *learn_text;
static lv_obj_t *learn_progress;
static lv_obj_t *learn_back_button;
static lv_obj_t *learn_start_button;
static lv_obj_t *learn_stop_button;

static Statechart *fsm;

static lv_obj_t *gui_set_title(lv_obj_t *parent, const char *text);

void gui_flush_display(lv_disp_drv_t *disp, const lv_area_t *area,
                       lv_color_t *color);
void gui_read_touch(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static void gui_create_main_screen();
static void gui_create_learn_screen();
static lv_obj_t* gui_create_label_value_row(const char *text, lv_obj_t *parent);
static lv_obj_t *gui_create_back_button(lv_obj_t *parent);
static lv_obj_t *gui_create_learn_infobox(lv_obj_t *parent);
static lv_obj_t *gui_create_learn_progressbox(lv_obj_t *parent);

/*******************************************************************************
***************************** BUTTON CALLBACKS *********************************
*******************************************************************************/

static void gui_on_ok_button(lv_event_t *e);
// MAIN button callbacks
static void gui_on_learn_button(lv_event_t *e);

// LEARN button callbacks
static void gui_on_learn_start_button(lv_event_t *e);
static void gui_on_learn_stop_button(lv_event_t *e);

void gui_init(Statechart *fsm_handle) {
  fsm = fsm_handle;
  tft.begin(SPI_FREQ);
  tft.setRotation(1);
  tft.setFramebuffers(internal_fb);
  tft.setDiffBuffers(&diff_buf_1, &diff_buf_2);
  tft.setDiffGap(4);
  tft.setVSyncSpacing(1);
  tft.setRefreshRate(100);
  tft.clear(0b000000000011111);
  int touch_calib[4] = {644, 3508, 3663, 568};
  tft.setTouchCalibration(touch_calib);

  lv_init();
  lv_disp_draw_buf_init(&draw_buf, lvgl_buf, NULL, LVGL_BUF_SIZE);
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = TFT_WIDTH;
  disp_drv.ver_res = TFT_HEIGHT;
  disp_drv.flush_cb = gui_flush_display;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = gui_read_touch;
  lv_indev_drv_register(&indev_drv);

  gui_create_main_screen();
  gui_create_learn_screen();
}

void gui_learn_set_state(const char *text) {
  lv_label_set_text(learn_state, text);
}

void gui_learn_set_time(uint16_t time) {
  lv_label_set_text_fmt(learn_time, "%d", time);
}

void gui_learn_set_temperature(int16_t temperature) {
  lv_label_set_text_fmt(learn_temperature, "%d", temperature);
}

void gui_learn_set_duty(uint8_t duty) {
  lv_label_set_text_fmt(learn_duty, "%d %%", duty);
}

void gui_learn_set_progress(uint8_t progress) {
  lv_bar_set_value(learn_progress, progress, LV_ANIM_OFF);
}

void gui_learn_set_info_text(const char* text) {
  lv_label_set_text(learn_text, text);
}

void gui_flush_display(lv_disp_drv_t *disp, const lv_area_t *area,
                       lv_color_t *color) {
  // tft.drawImageAsync(area->x1, area->y1, area->x2, area->y2,
  //                    (uint16_t *)color);
  const bool redraw_now = lv_disp_flush_is_last(disp);
  tft.updateRegion(redraw_now, (uint16_t *)color, area->x1, area->x2, area->y1,
                   area->y2);
  // tft.writeRect(area->x1, area->y1, w, h, (uint16_t *)color);
  // tft.updateScreenAsync();
  lv_disp_flush_ready(disp);
}
void gui_read_touch(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
  int x, y, z;
  bool touched = tft.readTouch(x, y, z);
  // x = map(x, TOUCH_X_MIN, TOUCH_X_MAX, 0, TFT_WIDTH);
  // y = map(y, TOUCH_Y_MIN, TOUCH_Y_MAX, 0, TFT_HEIGHT);
  data->state = touched ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
  data->point.x = x;
  data->point.y = y;
}

static void gui_create_main_screen() {
  main_screen = lv_obj_create(NULL);
  lv_scr_load(main_screen);

  lv_obj_t *title = gui_set_title(main_screen, "Main Menue");

  lv_obj_t *col = lv_obj_create(main_screen);
  lv_obj_update_layout(title);
  lv_obj_set_size(col, LV_PCT(80), TFT_HEIGHT - lv_obj_get_height(title));
  lv_obj_align(col, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_flex_flow(col, LV_FLEX_FLOW_COLUMN);

  lv_obj_t *button = lv_btn_create(col);
  lv_obj_add_event_cb(button, gui_on_learn_button, LV_EVENT_ALL, NULL);
  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, "Learn");
  lv_obj_center(label);
  lv_obj_set_width(button, LV_PCT(100));

  button = lv_btn_create(col);
  label = lv_label_create(button);
  lv_label_set_text(label, "Reflow");
  lv_obj_center(label);
  lv_obj_set_width(button, LV_PCT(100));
}

static void gui_create_learn_screen() {
  learn_screen = lv_obj_create(NULL);

  learn_back_button = gui_create_back_button(learn_screen);

  lv_obj_t *title = gui_set_title(learn_screen, "Learn Params");
  lv_obj_update_layout(title);
  lv_obj_t *outer_col = lv_obj_create(learn_screen);
  lv_obj_set_style_pad_all(outer_col, 0, LV_STATE_DEFAULT);
  lv_obj_set_size(outer_col, LV_PCT(100),
                  TFT_HEIGHT - lv_obj_get_height(title));
  lv_obj_set_flex_flow(outer_col, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_style_border_side(outer_col, LV_BORDER_SIDE_NONE,
                               LV_STATE_DEFAULT);
  lv_obj_align(outer_col, LV_ALIGN_TOP_MID, 0, lv_obj_get_height(title));

  lv_obj_t *row = lv_obj_create(outer_col);
  lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(row, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_START);
  lv_obj_set_style_border_side(row, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(row, 0, LV_STATE_DEFAULT);
  lv_obj_set_flex_grow(row, 1);
  lv_obj_set_width(row, LV_PCT(100));
  lv_obj_set_height(row, LV_SIZE_CONTENT);

  lv_obj_t* infobox = gui_create_learn_infobox(row);
  lv_obj_set_flex_grow(infobox, 3);

  lv_obj_t* progressbox = gui_create_learn_progressbox(row);
  lv_obj_set_flex_grow(progressbox, 2);

  lv_obj_t *text_box = lv_obj_create(outer_col);
  lv_obj_set_width(text_box, LV_PCT(100));
  learn_text = lv_label_create(text_box);
  lv_obj_set_align(learn_text, LV_ALIGN_TOP_LEFT);
  lv_obj_set_width(learn_text, LV_PCT(100));
  lv_label_set_long_mode(learn_text, LV_LABEL_LONG_WRAP);
  lv_label_set_text(learn_text,
                    "Hello, this is a very long text. Probably it needs to be "
                    "wrapped. At least it should be able to do so.");
  lv_obj_set_flex_grow(text_box, 1);
}

static lv_obj_t *gui_create_learn_infobox(lv_obj_t *parent) {
  lv_obj_t *col = lv_obj_create(parent);
  lv_obj_set_flex_flow(col, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_style_pad_row(col, 0, LV_STATE_DEFAULT);

  learn_state = gui_create_label_value_row("State: ", col);
  learn_time = gui_create_label_value_row("Time: ", col);
  learn_temperature = gui_create_label_value_row("T: ", col);
  learn_duty = gui_create_label_value_row("Duty: ", col);
  lv_obj_set_flex_grow(col, 1);
  lv_obj_set_style_pad_ver(col, 0, LV_STATE_DEFAULT);
  lv_obj_set_height(col, LV_SIZE_CONTENT);
  return col;
}

static lv_obj_t *gui_create_learn_progressbox(lv_obj_t *parent) {
  lv_obj_t *col = lv_obj_create(parent);
  lv_obj_set_flex_flow(col, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_style_flex_main_place(col, LV_FLEX_ALIGN_SPACE_EVENLY, LV_STATE_DEFAULT);
  lv_obj_set_style_flex_cross_place(col, LV_FLEX_ALIGN_CENTER, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(col, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_ver(col, 0, LV_STATE_DEFAULT);
  lv_obj_set_height(col, LV_SIZE_CONTENT);

  learn_progress = lv_bar_create(col);
  lv_obj_set_height(learn_progress, 20);
  lv_obj_set_width(learn_progress, LV_PCT(100));

  lv_obj_t *row = lv_obj_create(col);
  lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
  lv_obj_set_style_flex_main_place(row, LV_FLEX_ALIGN_SPACE_EVENLY, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(row, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(row, 0, LV_STATE_DEFAULT);
  lv_obj_set_size(row, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  
  learn_start_button = lv_btn_create(row);
  lv_obj_t *label = lv_label_create(learn_start_button);
  lv_label_set_text(label, LV_SYMBOL_PLAY);
  lv_obj_set_size(learn_start_button, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_add_event_cb(learn_start_button, gui_on_learn_start_button, LV_EVENT_CLICKED, NULL);

  learn_stop_button = lv_btn_create(row);
  label = lv_label_create(learn_stop_button);
  lv_label_set_text(label, LV_SYMBOL_STOP);
  lv_obj_set_size(learn_stop_button, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_add_event_cb(learn_stop_button, gui_on_learn_stop_button, LV_EVENT_CLICKED, NULL);

  return col;
}

static lv_obj_t* gui_create_label_value_row(const char *text, lv_obj_t *parent) {
  // create flex row
  lv_obj_t *row = lv_obj_create(parent);
  lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);

  lv_obj_t *label = lv_label_create(row);
  lv_label_set_text(label, text);
  lv_obj_t *value = lv_label_create(row);
  lv_label_set_text(value, "---");

  // let the value expand, but keep the label static
  lv_obj_set_flex_grow(label, 0);
  lv_obj_set_flex_grow(value, 1);

  lv_obj_set_height(row, LV_SIZE_CONTENT);
  lv_obj_set_width(row, LV_PCT(100));

  // remove borders and padding
  lv_obj_set_style_pad_all(row, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(row, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);
  return value;
}

void gui_show_ok_msg_box(const char* title, const char* text) {
  static const char *btns[] = {"OK"};
  lv_obj_t *box = lv_msgbox_create(NULL, title, text, btns, false);
  lv_obj_add_event_cb(box, gui_on_ok_button, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_center(box);
}

static void gui_on_learn_button(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    // TODO raise event
    lv_scr_load_anim(learn_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 1000, 0, false);
  }
}

static void gui_on_back_button(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    // TODO raise event
    lv_scr_load_anim(main_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 1000, 0, false);
  }
}

static void gui_on_learn_start_button(lv_event_t *e){
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    statechart_learn_raise_startPressed(fsm);
  }
}
static void gui_on_learn_stop_button(lv_event_t *e){
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    statechart_learn_raise_stopPressed(fsm);
  }
}

static void gui_on_ok_button(lv_event_t *e){
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_current_target(e);
  if (strcmp(lv_msgbox_get_active_btn_text(obj), "OK") == 0) {
    statechart_raise_okPressed(fsm);
  }
}

static lv_obj_t *gui_create_back_button(lv_obj_t *parent) {
  lv_obj_t *button = lv_btn_create(parent);
  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, LV_SYMBOL_LEFT);
  lv_obj_set_size(button, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_obj_align(button, LV_ALIGN_TOP_LEFT, 5, 5);
  lv_obj_add_event_cb(button, gui_on_back_button, LV_EVENT_CLICKED, NULL);
  return button;
}

static lv_obj_t *gui_set_title(lv_obj_t *parent, const char *text) {
  lv_obj_t *label = lv_label_create(parent);
  lv_obj_set_style_pad_all(label, 10, LV_STATE_DEFAULT);
  lv_label_set_text(label, text);
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_20, LV_STATE_DEFAULT);
  return label;
}
