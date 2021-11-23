/*
 * learn.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: lennartalff
 */

#include "learn.h"

#include "Arduino.h"
#include "gui.h"

static Statechart *fsm;
static char msg_buf[128];

void learn_init(Statechart *fsm_handle) { fsm = fsm_handle; }

void learn_setProgress(int8_t progress_percent) {
  gui_learn_set_progress(progress_percent);
}
void learn_setFailText(const char *text) {
  strncpy(msg_buf, text, sizeof(msg_buf));
  msg_buf[sizeof(msg_buf) - 1] = '\0';
}

void learn_showFailPage() { gui_show_ok_msg_box("Failure", msg_buf); }

void learn_setDutyCycle(uint8_t duty_cycle) {
  statechart_learn_set_duty_cycle(fsm, duty_cycle);
  actuators_set_heating_duty(statechart_learn_get_duty_cycle(fsm));
  learn_guiUpdateDutyCycle(duty_cycle);
}

void learn_updateHeatRampDuty() {
  int32_t temp = (int32_t)statechart_get_temperature(fsm);
  uint8_t duty_cycle = LEARN_RAMP_INITIAL_DUTY_CYCLE;
  int32_t temp_diff = temp > LEARN_SOAKING_TEMP ? 0 : LEARN_SOAKING_TEMP - temp;
  if (temp_diff <= LEARN_RAMP_REDUCTION_TEMP_DIFF) {
    duty_cycle = LEARN_RAMP_REDUCTION_DUTY_CYCLE;
  }
  if (temp_diff <= LEARN_RAMP_COMPLETED_TEMP_DIFF) {
    duty_cycle = LEARN_RAMP_COMPLETED_DUTY_CYCLE;
    statechart_learn_raise_phaseCompleted(fsm);
  }
  learn_setDutyCycle(duty_cycle);
}

void learn_updateHeatConstDuty() {
  int16_t temp = statechart_get_temperature_int(fsm);
  uint16_t t_overtemp = statechart_learn_get_t_overtemp(fsm);
  uint16_t t_now = statechart_learn_get_current_state_time(fsm);
  uint8_t duty = statechart_learn_get_duty_cycle(fsm);
  uint16_t duty_delay = statechart_learn_get_duty_delay(fsm);
  
  if (temp > LEARN_SOAKING_TEMP) {
    actuators_switchHeating(false);
    // update duty cycle only after a certain guard time
    if (t_now - t_overtemp > LEARN_CONST_DUTY_GUARD_TIME_SECS) {
      statechart_learn_set_t_overtemp(fsm, t_now);

      // decrease duty cycle since we are too hot ;-)
      if (duty > 0) {
        duty--;
        learn_setDutyCycle(duty);
      }
      statechart_learn_set_duty_delay(fsm, 0);
    }
  } else {
    actuators_switchHeating(true);
    if (LEARN_SOAKING_TEMP - temp > 1) {
      duty_delay++;
    }
    if (LEARN_SOAKING_TEMP - temp > 5) {
      duty_delay++;
    }
    statechart_learn_set_duty_delay(fsm, duty_delay);
    if (duty_delay > 30) {
      statechart_learn_set_duty_delay(fsm, 0);
      if (duty < 100) {
        duty++;
        learn_setDutyCycle(duty);
      }
    }
  }
}

void learn_guiUpdateCurrentTemperature(int16_t temperature) {
  gui_learn_set_temperature(temperature);
}

void learn_guiUpdateDutyCycle(uint8_t duty_cycle) {
  gui_learn_set_duty(duty_cycle);
}
void learn_guiSetInfoText(const char *text) { gui_learn_set_info_text(text); }
void learn_guiSetStateText(const char *text) { gui_learn_set_state(text); }
void learn_guiSetTime(uint16_t time) { gui_learn_set_time(time); }