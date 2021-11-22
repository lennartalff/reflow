#ifndef E4BB2AF4_E8C2_47C5_96DB_C67D95BA2330
#define E4BB2AF4_E8C2_47C5_96DB_C67D95BA2330

#include "Statechart.h"

#define TFT_DC 10
#define TFT_CS 9
#define TFT_RST 8
#define TFT_MOSI 11
#define TFT_SCK 13
#define TFT_MISO 12
#define TFT_WIDTH 320
#define TFT_HEIGHT 240

#define TOUCH_CS 7
#define TOUCH_IRQ 255

#define TOUCH_X_MIN 3801
#define TOUCH_X_MAX 275
#define TOUCH_Y_MIN 3887
#define TOUCH_Y_MAX 360

void gui_init(Statechart *fsm_handle);
void gui_show_ok_msg_box(const char* title, const char* text);

void gui_learn_set_state(const char *text);
void gui_learn_set_time(uint16_t time);
void gui_learn_set_temperature(int16_t temperature);
void gui_learn_set_duty(uint8_t duty);
void gui_learn_set_progress(uint8_t progress);
void gui_learn_set_info_text(const char* text);

#endif /* E4BB2AF4_E8C2_47C5_96DB_C67D95BA2330 */
