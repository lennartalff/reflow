/*
 * learn.h
 *
 *  Created on: Nov 15, 2021
 *      Author: lennartalff
 */

#ifndef INCLUDE_LEARN_H_
#define INCLUDE_LEARN_H_
#include <stdint.h>
#include "globals.h"

#define LEARN_TEST 10

const uint16_t LEARN_RAMP_TIME_SECS = 200;
const uint16_t LEARN_CONST_TIME_SECS = 780;
const uint16_t LEARN_INERTIA_TIME_SECS = 120;
const uint16_t LEARN_COOLDOWN_TIME_SECS = 400;

const uint16_t LEARN_COOLED_DOWN_TEMP = 50;

void learn_init(gslc_tsGui * m_gui);
void learn_setStateText(const char * text);
void learn_setProgress(int16_t progress);
void learn_setProgressBounds(int16_t min, int16_t max);
void learn_setTempCurrentText(int32_t temperature);
void learn_setTempTargetText(int32_t temperature);
void learn_setDTempCurrentText(float dT);
void learn_setDTempTargetText(float dT);

#endif /* INCLUDE_LEARN_H_ */
