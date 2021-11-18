/*
 * learn.h
 *
 *  Created on: Nov 15, 2021
 *      Author: lennartalff
 */

#ifndef LEARN
#define LEARN
#include <stdint.h>
#include "globals.h"
#include "Statechart.h"

const uint16_t LEARN_RAMP_TIME_SECS = 200;
const uint16_t LEARN_CONST_TIME_SECS = 780;
const uint16_t LEARN_INERTIA_TIME_SECS = 120;
const uint16_t LEARN_COOLDOWN_TIME_SECS = 400;
const uint16_t LEARN_COOLED_DOWN_TEMP = 50;
const uint16_t LEARN_SOAKING_TEMP = 120;
const uint16_t LEARN_INERTIA_TEMP = 150;

const uint16_t LEARN_RAMP_REDUCTION_TEMP_DIFF = 30;
const uint16_t LEARN_RAMP_INITIAL_DUTY_CYCLE = 60;
const uint16_t LEARN_RAMP_REDUCTION_DUTY_CYCLE = 30;
const uint16_t LEARN_RAMP_COMPLETED_DUTY_CYCLE = 15;
const uint16_t LEARN_RAMP_COMPLETED_TEMP_DIFF = 15;

void learn_init(gslc_tsGui *m_gui, Statechart *fsm_handle);
void learn_setStateText(const char *text);
void learn_setProgress(int16_t progress);
void learn_setFailText(const char *text);
void learn_showFailPage();
void learn_setDutyCycle(uint8_t dutyCycle);
void learn_updateHeatRampDuty();
void learn_guiUpdateTargetTemperature(int32_t temperature);
void learn_guiUpdateCurrentTemperature(int32_t temperature);

#endif /* LEARN */
