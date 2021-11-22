#include "MAX31855.h"
#include "Statechart.h"
#include "gui.h"
#include "lvgl.h"
#include "sensors.h"







Statechart fsm;



void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(115200);
  // Wait for USB Serial
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

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------

  //TODO - Add update code for any text, gauges, or sliders

  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  uint32_t now = millis();
  if (now - t_last >= 5)
  {
    // snprintf(txt, MAX_STR, "%3d", int(temp));
    lv_timer_handler();
    statechart_run_cycle(&fsm);
    // gslc_Update(&m_gui);
    t_last = now;
  }
}
