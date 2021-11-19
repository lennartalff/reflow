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
static Statechart *fsm;

void learn_init(gslc_tsGui *m_gui, Statechart *fsm_handle)
{
	gui = m_gui;
	fsm = fsm_handle;
}

void learn_setStateText(const char *text)
{
	gslc_ElemSetTxtStr(gui, m_pElemState, text);
}
void learn_setProgress(int16_t progress_percent)
{
	gslc_ElemXProgressSetVal(gui, m_pElemProgress1, progress_percent);
}
void learn_setFailText(const char *text)
{
	// TODO
	// void gslc_ElemXTextboxReset(gslc_tsGui* pGui,gslc_tsElemRef* pElemRef);
	// and
	// void gslc_ElemXTextboxAdd(gslc_tsGui* pGui,gslc_tsElemRef* pElemRef,char* pTxt);
}

void learn_showFailPage()
{
	gslc_PopupShow(gui, E_PG_ALERT, true);
}

void learn_setDutyCycle(uint8_t duty_cycle)
{
	statechart_learn_set_duty_cycle(fsm, duty_cycle);
	actuators_set_heating_duty(statechart_learn_get_duty_cycle(fsm));
	learn_guiUpdateDutyCycle(duty_cycle);
}

void learn_updateHeatRampDuty()
{
	int32_t temp = (int32_t)statechart_get_temperature(fsm);
	uint8_t duty_cycle = LEARN_RAMP_INITIAL_DUTY_CYCLE;
	int32_t temp_diff = temp > LEARN_SOAKING_TEMP ? 0 : LEARN_SOAKING_TEMP - temp;
	if (temp_diff <= LEARN_RAMP_REDUCTION_TEMP_DIFF)
	{
		duty_cycle = LEARN_RAMP_REDUCTION_DUTY_CYCLE;
	}
	if (temp_diff <= LEARN_RAMP_COMPLETED_TEMP_DIFF)
	{
		duty_cycle = LEARN_RAMP_COMPLETED_DUTY_CYCLE;
		statechart_learn_raise_phaseCompleted(fsm);
	}
	learn_setDutyCycle(duty_cycle);
}

void learn_updateHeatConstDuty() {
	int32_t temp = (int32_t)statechart_get_temperature(fsm);
	uint16_t t_overtemp = statechart_learn_get_t_overtemp(fsm);
	uint16_t t_now = statechart_learn_get_current_state_time(fsm);
	if(temp > LEARN_SOAKING_TEMP) {
		actuators_switchHeating(false);
		// update duty cycle only after a certain guard time
		if(t_now - t_overtemp > LEARN_CONST_DUTY_GUARD_TIME_SECS) {
			statechart_learn_set_t_overtemp(fsm, t_now);
			// TODO: complete the code
		}
	}
}

void learn_guiUpdateTargetTemperature(int32_t temperature)
{
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "%d", temperature);
	gslc_ElemSetTxtStr(gui, m_pElemLearnTempTarget, buffer);
}

void learn_guiUpdateCurrentTemperature(int32_t temperature)
{
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "%d", temperature);
	gslc_ElemSetTxtStr(gui, m_pElemLearnTempCurrent, buffer);
}

void learn_guiUpdateDutyCycle(uint8_t duty_cycle)
{
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "%d", duty_cycle);
	gslc_ElemSetTxtStr(gui, m_pElemLearnDuty, buffer);
}
