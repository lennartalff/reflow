#include "MAX31855.h"
#include "Statechart.h"
#include "gui.h"
#include "lvgl.h"
#include "sensors.h"
#include "actuators.h"







Statechart fsm;



void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(115200);
  // Wait for USB Serial
  actuators_init();
  sensors_init(&fsm);
  gui_init(&fsm);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  learn_init(&fsm);
  statechart_init(&fsm);
  statechart_enter(&fsm);
}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{
  static uint32_t t_last = 0;
  uint32_t now = millis();
  if (now - t_last >= 5)
  {
    lv_timer_handler();
    statechart_run_cycle(&fsm);
    t_last = now;
  }
}
