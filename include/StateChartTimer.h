#ifndef A70F5C93_DBE8_4F67_B952_EEBB57D9DBB3
#define A70F5C93_DBE8_4F67_B952_EEBB57D9DBB3

#include "sc_types.h"
#include "Statechart.h"
#include <TeensyTimerTool.h>


class StateChartTimer
{
public:
    StateChartTimer(){this->timer = new TeensyTimerTool::PeriodicTimer(TeensyTimerTool::TCK);}
    void setTimer(const Statechart *sc_handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic);
    void unsetTimer();
    void init();
    void raiseTimeEvent();
    const Statechart *sc_handle;
    bool active = false;
    sc_eventid evid;
    sc_integer time_ms;
    sc_boolean periodic;

private:
    TeensyTimerTool::PeriodicTimer *timer;
    void callback();
};

#endif /* A70F5C93_DBE8_4F67_B952_EEBB57D9DBB3 */
