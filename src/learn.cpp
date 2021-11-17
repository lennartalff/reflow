/*
 * learn.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: lennartalff
 */

#include "learn.h"
#include "globals.h"
#include "Arduino.h"
#include "elem/XProgress.h"

static gslc_tsGui *gui;

void learn_init(gslc_tsGui *m_gui)
{
	gui = m_gui;
}

void learn_setStateText(const char *text)
{
	Serial.println(text);
	gslc_ElemSetTxtStr(gui, m_pElemState, text);
}
void learn_setProgress(int16_t progress_percent){
	Serial.println("Progress");
	gslc_ElemXProgressSetVal(gui, m_pElemProgress1, progress_percent);
}
void learn_setTempCurrentText(int32_t temperature) {}
void learn_setTempTargetText(int32_t temperature) {}
void learn_setDTempCurrentText(float dT) {}
void learn_setDTempTargetText(float dT) {}
