//<File !Start!>
// FILE: [reflow_GSLC.h]
// Created by GUIslice Builder version: [0.17.0]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XProgress.h"
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#include <SPI.h>
#include "font_Arial.h"
#include "font_ArialBold.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_PG_LEARN,E_PG_POPUP1};
enum {E_DRAW_LINE1,E_DRAW_LINE3,E_ELEM_BOX1,E_ELEM_BOX2,E_ELEM_BTN4
      ,E_ELEM_BTN5,E_ELEM_LEARN_DTEMP_CURRENT,E_ELEM_LEARN_DTEMP_TARGET
      ,E_ELEM_LEARN_DUTY,E_ELEM_LEARN_START_BUTTON
      ,E_ELEM_LEARN_STOP_BUTTON,E_ELEM_LEARN_TEMP_CURRENT
      ,E_ELEM_LEARN_TEMP_TARGET,E_ELEM_PROGRESS1,E_ELEM_STATE
      ,E_ELEM_TEXT11,E_ELEM_TEXT13,E_ELEM_TEXT4,E_ELEM_TEXT6
      ,E_ELEM_TEXT8,E_ELEM_TEXT9};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_ARIAL_12,E_ARIAL_18_BOLD,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                3

#define MAX_ELEM_PG_MAIN 2 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG_LEARN 19 // # Elems total on page
#define MAX_ELEM_PG_LEARN_RAM MAX_ELEM_PG_LEARN // # Elems in RAM

#define MAX_ELEM_PG_POPUP1 0 // # Elems total on page
#define MAX_ELEM_PG_POPUP1_RAM MAX_ELEM_PG_POPUP1 // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_LEARN_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_LEARN];
gslc_tsElem                     m_asPopup1Elem[MAX_ELEM_PG_POPUP1_RAM];
gslc_tsElemRef                  m_asPopup1ElemRef[MAX_ELEM_PG_POPUP1];
gslc_tsXProgress                m_sXBarGauge1;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemDTempCurrent;
extern gslc_tsElemRef* m_pElemDTempTarget;
extern gslc_tsElemRef* m_pElemLearnDuty;
extern gslc_tsElemRef* m_pElemLearnTempCurrent;
extern gslc_tsElemRef* m_pElemLearnTempTarget;
extern gslc_tsElemRef* m_pElemProgress1;
extern gslc_tsElemRef* m_pElemState;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_ARIAL_12,GSLC_FONTREF_PTR,&Arial_12,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_12, GSLC_FONTREF_MODE_1);	
    if (!gslc_FontSet(&m_gui,E_ARIAL_18_BOLD,GSLC_FONTREF_PTR,&Arial_18_Bold,1)) { return; }
    gslc_FontSetMode(&m_gui, E_ARIAL_18_BOLD, GSLC_FONTREF_MODE_1);	
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG_LEARN,m_asPage2Elem,MAX_ELEM_PG_LEARN_RAM,m_asPage2ElemRef,MAX_ELEM_PG_LEARN);
  gslc_PageAdd(&m_gui,E_PG_POPUP1,m_asPopup1Elem,MAX_ELEM_PG_POPUP1_RAM,m_asPopup1ElemRef,MAX_ELEM_PG_POPUP1);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_WHITE);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // Create E_ELEM_TEXT8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT8,E_PG_MAIN,(gslc_tsRect){88,10,143,20},
    (char*)"Main Menue",0,E_ARIAL_18_BOLD);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // create E_ELEM_BTN5 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN5,E_PG_MAIN,
    (gslc_tsRect){10,60,80,40},(char*)"Learn",0,E_ARIAL_12,&CbBtnCommon);

  // -----------------------------------
  // PAGE: E_PG_LEARN
  
   
  // Create E_ELEM_BOX1 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX1,E_PG_LEARN,(gslc_tsRect){10,40,140,140});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_WHITE);
  
  // create E_ELEM_LEARN_START_BUTTON button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_LEARN_START_BUTTON,E_PG_LEARN,
    (gslc_tsRect){10,190,80,40},(char*)"Start",0,E_ARIAL_12,&CbBtnCommon);
  
  // create E_ELEM_LEARN_STOP_BUTTON button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_LEARN_STOP_BUTTON,E_PG_LEARN,
    (gslc_tsRect){120,190,80,40},(char*)"Stop",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // create E_ELEM_BTN4 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN4,E_PG_LEARN,
    (gslc_tsRect){230,190,80,40},(char*)"Back",0,E_ARIAL_12,&CbBtnCommon);
  gslc_ElemSetTxtEnc(&m_gui,pElemRef,GSLC_TXT_ENC_UTF8);
  
  // Create E_ELEM_TEXT4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT4,E_PG_LEARN,(gslc_tsRect){77,10,165,20},
    (char*)"Learn Params",0,E_ARIAL_18_BOLD);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT6,E_PG_LEARN,(gslc_tsRect){20,50,47,14},
    (char*)"State: ",0,E_ARIAL_12);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_STATE runtime modifiable text
  static char m_sDisplayText7[21] = "p_|I";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_STATE,E_PG_LEARN,(gslc_tsRect){70,50,80,16},
    (char*)m_sDisplayText7,21,E_ARIAL_12);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_WHITE);
  m_pElemState = pElemRef;

  // Create progress bar E_ELEM_PROGRESS1 
  pElemRef = gslc_ElemXProgressCreate(&m_gui,E_ELEM_PROGRESS1,E_PG_LEARN,&m_sXBarGauge1,
    (gslc_tsRect){20,70,120,12},0,100,0,GSLC_COL_GREEN,false);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_BLACK);
  m_pElemProgress1 = pElemRef;
   
  // Create E_ELEM_BOX2 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX2,E_PG_LEARN,(gslc_tsRect){170,40,140,140});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_WHITE);
  
  // Create E_ELEM_TEXT9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT9,E_PG_LEARN,(gslc_tsRect){20,90,50,16},
    (char*)"Temp: ",0,E_ARIAL_12);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_LEARN_TEMP_CURRENT runtime modifiable text
  static char m_sDisplayText10[4] = "000";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_LEARN_TEMP_CURRENT,E_PG_LEARN,(gslc_tsRect){70,90,27,13},
    (char*)m_sDisplayText10,4,E_ARIAL_12);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_WHITE);
  m_pElemLearnTempCurrent = pElemRef;
  
  // Create E_ELEM_TEXT11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT11,E_PG_LEARN,(gslc_tsRect){20,110,41,13},
    (char*)"dT/dt:",0,E_ARIAL_12);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_LEARN_DTEMP_CURRENT runtime modifiable text
  static char m_sDisplayText12[5] = "0.00";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_LEARN_DTEMP_CURRENT,E_PG_LEARN,(gslc_tsRect){70,110,35,13},
    (char*)m_sDisplayText12,5,E_ARIAL_12);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_WHITE);
  m_pElemDTempCurrent = pElemRef;
  
  // Create E_ELEM_TEXT13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT13,E_PG_LEARN,(gslc_tsRect){20,130,44,16},
    (char*)"Duty: ",0,E_ARIAL_12);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create E_ELEM_LEARN_DUTY runtime modifiable text
  static char m_sDisplayText14[4] = "0";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_LEARN_DUTY,E_PG_LEARN,(gslc_tsRect){60,130,27,13},
    (char*)m_sDisplayText14,4,E_ARIAL_12);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_WHITE);
  m_pElemLearnDuty = pElemRef;

  // Create E_DRAW_LINE1 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE1,E_PG_LEARN,100,90,100,103);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // Create E_ELEM_LEARN_TEMP_TARGET runtime modifiable text
  static char m_sDisplayText16[4] = ".";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_LEARN_TEMP_TARGET,E_PG_LEARN,(gslc_tsRect){101,90,27,13},
    (char*)m_sDisplayText16,4,E_ARIAL_12);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_WHITE);
  m_pElemLearnTempTarget = pElemRef;

  // Create E_DRAW_LINE3 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE3,E_PG_LEARN,105,110,105,123);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_BLACK,GSLC_COL_BLACK);
  
  // Create E_ELEM_LEARN_DTEMP_TARGET runtime modifiable text
  static char m_sDisplayText17[5] = ".";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_LEARN_DTEMP_TARGET,E_PG_LEARN,(gslc_tsRect){106,110,36,13},
    (char*)m_sDisplayText17,5,E_ARIAL_12);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_WHITE);
  m_pElemDTempTarget = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_POPUP1
  
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
