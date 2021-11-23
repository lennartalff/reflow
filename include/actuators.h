/*
 * actuators.h
 *
 *  Created on: Nov 15, 2021
 *      Author: lennartalff
 */

#ifndef INCLUDE_ACTUATORS_H_
#define INCLUDE_ACTUATORS_H_
#include <stdbool.h>
#include <stdint.h>

void actuators_init();
void actuators_switchHeating(bool on);
void actuators_set_heating_duty(uint8_t duty);

#endif /* INCLUDE_ACTUATORS_H_ */
