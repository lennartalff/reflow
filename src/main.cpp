#include "MAX31855.h"
#include "reflow_GSLC.h"
#include "Statechart.h"

const int doPin = 21;
const int csPin = 20;
const int clPin = 22;

MAX31855 tc(clPin, csPin, doPin);

struct Statechart fsm;

gslc_tsElemRef *m_pElemDTempCurrent = NULL;
gslc_tsElemRef *m_pElemDTempTarget = NULL;
gslc_tsElemRef *m_pElemLearnDuty = NULL;
gslc_tsElemRef *m_pElemLearnTempCurrent = NULL;
gslc_tsElemRef *m_pElemLearnTempTarget = NULL;
gslc_tsElemRef *m_pElemProgress1 = NULL;
gslc_tsElemRef *m_pElemState = NULL;

// void setup()
// {
//   Serial.begin(115200);
//   Serial.print("Start max31855_demo0: ");
//   Serial.println(MAX31855_VERSION);
//   Serial.println();

//   tc.begin();
// }

// void loop()
// {
//   int status = tc.read();
//   Serial.print("stat:\t\t");
//   Serial.println(status);

//   float internal = tc.getInternal();
//   Serial.print("internal:\t");
//   Serial.println(internal, 3);

//   float temp = tc.getTemperature();
//   Serial.print("temperature:\t");
//   Serial.println(temp, 3);
//   delay(1000);
// }

//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch)
{
  if (ch == (char)'\n')
    Serial.println("");
  else
    Serial.write(ch);
  return 0;
}
uint32_t t_last = 0;

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void *pvGui, void *pvElemRef, gslc_teTouch eTouch, int16_t nX, int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui *pGui = (gslc_tsGui *)(pvGui);
  gslc_tsElemRef *pElemRef = (gslc_tsElemRef *)(pvElemRef);
  gslc_tsElem *pElem = gslc_GetElemFromRef(pGui, pElemRef);

  if (eTouch == GSLC_TOUCH_UP_IN)
  {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId)
    {
      //<Button Enums !Start!>
    case E_ELEM_BTN5:
      gslc_SetPageCur(&m_gui, E_PG_LEARN);
      break;
    case E_ELEM_LEARN_START_BUTTON:
      statechart_learn_raise_startPressed(&fsm);
      break;
    case E_ELEM_LEARN_STOP_BUTTON:
      statechart_learn_raise_stopPressed(&fsm);
      break;
    case E_ELEM_BTN4:
      gslc_SetPageCur(&m_gui, E_PG_MAIN);
      break;
      //<Button Enums !End!>
    default:
      break;
    }
  }
  return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>
//<Slider Callback !Start!>
//<Slider Callback !End!>
//<Tick Callback !Start!>
//<Tick Callback !End!>

void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(115200);
  // Wait for USB Serial
  delay(5000); // NOTE: Some devices require a delay after Serial.begin() before serial port can be used
  tc.begin();
  gslc_InitDebug(&DebugOut);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();
  learn_init(&m_gui);
  statechart_init(&fsm);
  statechart_enter(&fsm);
  Serial.println("Update GUI");
  gslc_Update(&m_gui);
}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------

  //TODO - Add update code for any text, gauges, or sliders

  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  uint32_t now = millis();
  if (now - t_last >= 20)
  {

    int status = tc.read();

    float internal = tc.getInternal();

    float temp = tc.getTemperature();
    char txt[MAX_STR];
    snprintf(txt, MAX_STR, "%3d", int(temp));
    gslc_ElemSetTxtStr(&m_gui, m_pElemLearnTempCurrent, txt);
    statechart_run_cycle(&fsm);
    gslc_Update(&m_gui);
    t_last = now;
  }
}
