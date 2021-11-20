#include "gui.h"

static ILI9341_t3n tft =
    ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCK, TFT_MISO);
static XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);

static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;
DMAMEM static lv_color_t buf1[TFT_WIDTH * TFT_HEIGHT];
DMAMEM static lv_color_t buf2[TFT_WIDTH * TFT_HEIGHT];

static lv_indev_drv_t indev_drv;

lv_obj_t *p_main_screen;

void gui_flush_display(lv_disp_drv_t *disp, const lv_area_t *area,
                       lv_color_t *color);
bool gui_read_touch(lv_indev_data_t *data);
bool gui_create_main_screen();

void gui_init() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLUE);
  tft.useFrameBuffer(true);
  ts.begin();
  ts.setRotation(1);

  lv_init();
  tft.setHandleDmaComplete([](){lv_disp_flush_ready(&disp_drv);});
  lv_disp_draw_buf_init(&draw_buf, buf1, buf2, TFT_WIDTH * TFT_HEIGHT);
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
  uint16_t w = area->x2 - area->x1 + 1;
  uint16_t h = area->y2 - area->y1 + 1;
  tft.setClipRect(area->x1, area->y1, w, h);
  tft.writeRect(area->x1, area->y1, w, h, (uint16_t*)color);
  tft.updateScreenAsync();
}
bool gui_read_touch(lv_indev_data_t *data) {
  tft.waitUpdateAsyncComplete();
  TS_Point p = ts.getPoint();
  data->point.x = map(p.x, TOUCH_X_MIN, TOUCH_X_MAX, 0, TFT_WIDTH);
  data->point.y = map(p.y, TOUCH_Y_MIN, TOUCH_Y_MAX, 0, TFT_HEIGHT);
  data->state = ts.touched() ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
  return false;
}

bool gui_create_main_screen() {
  p_main_screen = lv_obj_create(NULL);
  lv_scr_load(p_main_screen);
  lv_obj_t *title = lv_label_create(p_main_screen);
  lv_label_set_text(title, "Main Menue");
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);
}