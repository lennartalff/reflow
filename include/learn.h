/*
 * learn.h
 *
 *  Created on: Nov 15, 2021
 *      Author: lennartalff
 */

#ifndef LEARN
#define LEARN
#include <stdint.h>

#include "Statechart.h"

const uint16_t LEARN_RAMP_TIME_SECS = 200;
const uint16_t LEARN_CONST_TIME_SECS = 780;
const uint16_t LEARN_INERTIA_TIME_SECS = 120;
const uint16_t LEARN_COOLDOWN_TIME_SECS = 400;
const int32_t LEARN_COOLED_DOWN_TEMP = 50;
const int32_t LEARN_SOAKING_TEMP = 120;
const int32_t LEARN_INERTIA_TEMP = 150;

const int32_t LEARN_RAMP_REDUCTION_TEMP_DIFF = 30;
const uint8_t LEARN_RAMP_INITIAL_DUTY_CYCLE = 60;
const uint8_t LEARN_RAMP_REDUCTION_DUTY_CYCLE = 30;
const uint8_t LEARN_RAMP_COMPLETED_DUTY_CYCLE = 15;
const int32_t LEARN_RAMP_COMPLETED_TEMP_DIFF = 15;

const uint8_t LEARN_INERTIA_DUTY_CYCLE = 80;

const uint16_t LEARN_CONST_DUTY_GUARD_TIME_SECS = 30;

void learn_init(Statechart *fsm_handle);
void learn_setProgress(int8_t progress);
void learn_setFailText(const char *text);
void learn_showFailPage();
void learn_setDutyCycle(uint8_t dutyCycle);
void learn_updateHeatRampDuty();
void learn_updateHeatConstDuty();
void learn_guiSetStateText(const char *text);
void learn_guiUpdateCurrentTemperature(int16_t temperature);
void learn_guiUpdateDutyCycle(uint8_t duty_cycle);
void learn_guiSetInfoText(const char *text);
void learn_guiSetTime(uint16_t time);

#endif /* LEARN */
