#include "MAX31855.h"
// #include "Statechart.h"
#include "gui.h"
#include "lvgl.h"





const int doPin = 21;
const int csPin = 20;
const int clPin = 22;

MAX31855 tc(clPin, csPin, doPin);

// Statechart fsm;



void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(115200);
  // Wait for USB Serial
  delay(500); // NOTE: Some devices require a delay after Serial.begin() before serial port can be used
  tc.begin();
  gui_init();

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  // learn_init(&m_gui, &fsm);
  // statechart_init(&fsm);
  // statechart_enter(&fsm);
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

    int status = tc.read();

    float internal = tc.getInternal();

    float temp = tc.getTemperature();
    // Serial.println(int(temp), DEC);
    // snprintf(txt, MAX_STR, "%3d", int(temp));
    // gslc_ElemSetTxtStr(&m_gui, m_pElemLearnTempCurrent, txt);
    // statechart_run_cycle(&fsm);
    // gslc_Update(&m_gui);
    lv_timer_handler();
    // lv_task_handler();
    t_last = now;
  }
}
