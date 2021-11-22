#include "sensors.h"

static const int doPin = 21;
static const int csPin = 20;
static const int clPin = 22;

static Statechart *fsm;

static MAX31855 tc(clPin, csPin, doPin);

void sensors_init(Statechart *fsm_handle) {
    fsm = fsm_handle;
    tc.begin();
}

void sensors_update_temperature() {
    tc.read();
    float temp = tc.getTemperature();
    statechart_set_temperature(fsm, temp);
    statechart_set_temperature_int(fsm, (int16_t) temp);
}