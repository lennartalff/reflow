#include "StateChartTimer.h"
#include <TeensyTimerTool.h>
#include "Statechart_required.h"
#include "Arduino.h"

#define MAX_TIMERS 5
StateChartTimer timers[MAX_TIMERS];

void statechart_set_timer(Statechart *handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic)
{
    Serial.print("Setting timer for event:");
    Serial.println((sc_intptr_t)evid, DEC);
    for(uint8_t i=0; i<MAX_TIMERS; i++) {


        if(!timers[i].active) {
            timers[i].setTimer(handle, evid, time_ms, periodic);
            break;
        }
    }
}

void statechart_unset_timer(Statechart* handle, const sc_eventid evid){
    for(uint8_t i=0; i<MAX_TIMERS; i++) {
        if(timers[i].evid == evid) {
            timers[i].unsetTimer();
        }
    }
}

void StateChartTimer::setTimer(const Statechart *sc_handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic) {
    this->sc_handle = sc_handle;
    this->active = true;
    this->periodic = periodic;
    this->time_ms = time_ms;
    this->evid = evid;
    timer->begin([this]{this->callback();}, time_ms * 1000);
}

void StateChartTimer::unsetTimer() {
    timer->stop();
    this->active = false;
}

void StateChartTimer::callback()
{
    Serial.println("Time Event Raised.");
    statechart_raise_time_event(this->sc_handle, this->evid);
    if(!this->periodic) {
        timer->stop();
        this->active = false;
    }
}