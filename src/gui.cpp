#include "gui.h"

#include "lvgl.h"
// #include "ILI9341_t3n.h"
#include "ILI9341_T4.h"
// #include "XPT2046_Touchscreen.h"

// static ILI9341_t3n tft =
//     ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCK, TFT_MISO);

static ILI9341_T4::ILI9341Driver tft(TFT_CS, TFT_DC, TFT_SCK, TFT_MOSI,
                                     TFT_MISO, TFT_RST, TOUCH_CS, TOUCH_IRQ);
#define SPI_FREQ 40000000
static ILI9341_T4::DiffBuffStatic<8192> diff_buf_1;
static ILI9341_T4::DiffBuffStatic<8192> diff_buf_2;
DMAMEM uint16_t internal_fb[TFT_WIDTH * TFT_HEIGHT];
// static XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);
static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;
static lv_color_t lvgl_buf[TFT_WIDTH * TFT_HEIGHT];

static lv_indev_drv_t indev_drv;

lv_obj_t *p_main_screen;

void gui_flush_display(lv_disp_drv_t *disp, const lv_area_t *area,
                       lv_color_t *color);
void gui_read_touch(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
void gui_create_main_screen();
static void event_handler(lv_event_t *e);

void gui_init() {
  tft.begin(SPI_FREQ);
  tft.setRotation(1);
  tft.setFramebuffers(internal_fb);
  tft.setDiffBuffers(&diff_buf_1, &diff_buf_2);
  tft.setDiffGap(4);
  tft.setVSyncSpacing(1);
  tft.setRefreshRate(100);
  tft.clear(0b000000000011111);
  // int touch_calib[4] = {TOUCH_X_MIN, TOUCH_X_MAX, TOUCH_Y_MIN, TOUCH_Y_MAX};
  int touch_calib[4] = {644, 3508, 3663, 568};
  tft.setTouchCalibration(touch_calib);

  lv_init();
  // tft.setHandleDmaComplete([]() {
  //   lv_disp_flush_ready(&disp_drv);
  //   Serial.println("DMA complete");
  // });
  lv_disp_draw_buf_init(&draw_buf, lvgl_buf, NULL, TFT_WIDTH * TFT_HEIGHT);
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
}

void gui_flush_display(lv_disp_drv_t *disp, const lv_area_t *area,
                       lv_color_t *color) {
  // tft.drawImageAsync(area->x1, area->y1, area->x2, area->y2,
  //                    (uint16_t *)color);
  const bool redraw_now = lv_disp_flush_is_last(disp);
  tft.updateRegion(redraw_now, (uint16_t*)color, area->x1, area->x2, area->y1, area->y2);
  // tft.writeRect(area->x1, area->y1, w, h, (uint16_t *)color);
  // tft.updateScreenAsync();
  lv_disp_flush_ready(disp);
}
void gui_read_touch(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
  int x, y, z;
  bool touched = tft.readTouch(x, y, z);
  data->state = touched ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
  data->point.x = x;
  data->point.y = y;
}

void gui_create_main_screen() {
  p_main_screen = lv_obj_create(NULL);
  lv_scr_load(p_main_screen);
  lv_obj_t *title = lv_label_create(p_main_screen);
  lv_label_set_text(title, "Main Menue");
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

  lv_obj_t *col = lv_obj_create(p_main_screen);
  lv_obj_set_size(col, 200, 150);
  lv_obj_center(col);
  lv_obj_set_flex_flow(col, LV_FLEX_FLOW_COLUMN);

  lv_obj_t *button = lv_btn_create(col);
  lv_obj_add_event_cb(button, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, "Learn");
  lv_obj_center(label);

  label = lv_label_create(col);
  lv_obj_set_size(button, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  lv_label_set_text_fmt(label, "x: %d, y: %d, xe: %d, ye: %d",
                        lv_obj_get_x(button), lv_obj_get_y(button),
                        lv_obj_get_x2(button), lv_obj_get_y2(button));
  button = lv_btn_create(p_main_screen);
  lv_obj_set_size(button, 50, 10);
}

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_CLICKED) {
    Serial.println("Clicked");
  } else if (code == LV_EVENT_VALUE_CHANGED) {
    Serial.println("Toggled");
  }
}
