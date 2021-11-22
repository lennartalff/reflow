#ifndef SENSORS
#define SENSORS

#include "Statechart.h"
#include "MAX31855.h"

void sensors_init(Statechart *fsm_handle);
void sensors_update_temperature();

#endif /* SENSORS */
