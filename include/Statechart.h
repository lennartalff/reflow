/** Generated by YAKINDU Statechart Tools code generator. */

#ifndef STATECHART_H_
#define STATECHART_H_

#ifdef __cplusplus
extern "C" { 
#endif

/*!
* Forward declaration for the Statechart state machine.
*/
typedef struct Statechart Statechart;

/*!
* Forward declaration of the data structure for the StatechartIface interface scope.
*/
typedef struct StatechartIface StatechartIface;

/*!
* Forward declaration of the data structure for the StatechartIfaceLearn interface scope.
*/
typedef struct StatechartIfaceLearn StatechartIfaceLearn;

/*!
* Forward declaration of the data structure for the StatechartTimeEvents interface scope.
*/
typedef struct StatechartTimeEvents StatechartTimeEvents;

#ifdef __cplusplus
}
#endif

#include <learn.h>
#include <actuators.h>
#include <sensors.h>
#include "../src/sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'Statechart'.
*/

/*! Define number of states in the state enum */
#define STATECHART_STATE_COUNT 9

/*! Define dimension of the state configuration vector for orthogonal states. */
#define STATECHART_MAX_ORTHOGONAL_STATES 2
/*! Define maximum number of time events that can be active at once */
#define STATECHART_MAX_PARALLEL_TIME_EVENTS 2

/*! Define indices of states in the StateConfVector */
#define SCVI_STATECHART_MAIN_REGION_OPERATING 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_IDLE 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_HEATRAMP 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_ABORT 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_COOLING 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_FAIL 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_HEATCONST 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_INERTIA 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R2_READTEMPERATURE 1

/*! Enumeration of all states */ 
typedef enum
{
	Statechart_last_state,
	Statechart_main_region_Operating,
	Statechart_main_region_Operating_r1_Idle,
	Statechart_main_region_Operating_r1_HeatRamp,
	Statechart_main_region_Operating_r1_Abort,
	Statechart_main_region_Operating_r1_Cooling,
	Statechart_main_region_Operating_r1_Fail,
	Statechart_main_region_Operating_r1_HeatConst,
	Statechart_main_region_Operating_r1_Inertia,
	Statechart_main_region_Operating_r2_ReadTemperature
} StatechartStates;








/*! Type declaration of the data structure for the StatechartIface interface scope. */
struct StatechartIface
{
	float temperature;
	int16_t temperature_int;
	sc_boolean okPressed_raised;
	sc_boolean cancelPressed_raised;
	sc_boolean yesPressed_raised;
	sc_boolean noPressed_raised;
};



/*! Type declaration of the data structure for the StatechartIfaceLearn interface scope. */
struct StatechartIfaceLearn
{
	sc_boolean startPressed_raised;
	sc_boolean stopPressed_raised;
	sc_boolean cancelPressed_raised;
	sc_boolean phaseCompleted_raised;
	sc_boolean failure_raised;
	uint16_t current_state_time;
	uint16_t total_time;
	uint8_t duty_cycle;
	uint16_t t_overtemp;
	uint16_t duty_delay;
};



/*! Type declaration of the data structure for the StatechartTimeEvents interface scope. */
struct StatechartTimeEvents
{
	sc_boolean statechart_main_region_Operating_r1_HeatRamp_tev0_raised;
	sc_boolean statechart_main_region_Operating_r1_HeatConst_tev0_raised;
	sc_boolean statechart_main_region_Operating_r1_Inertia_tev0_raised;
	sc_boolean statechart_main_region_Operating_r2_ReadTemperature_tev0_raised;
};





typedef struct StatechartIfaceEvBuf StatechartIfaceEvBuf;
struct StatechartIfaceEvBuf {
	sc_boolean okPressed_raised;
	sc_boolean cancelPressed_raised;
	sc_boolean yesPressed_raised;
	sc_boolean noPressed_raised;
};

typedef struct StatechartIfaceLearnEvBuf StatechartIfaceLearnEvBuf;
struct StatechartIfaceLearnEvBuf {
	sc_boolean startPressed_raised;
	sc_boolean stopPressed_raised;
	sc_boolean cancelPressed_raised;
	sc_boolean phaseCompleted_raised;
	sc_boolean failure_raised;
};

typedef struct StatechartTimeEventsEvBuf StatechartTimeEventsEvBuf;
struct StatechartTimeEventsEvBuf {
	sc_boolean Statechart_main_region_Operating_r1_HeatRamp_time_event_0_raised;
	sc_boolean Statechart_main_region_Operating_r1_HeatConst_time_event_0_raised;
	sc_boolean Statechart_main_region_Operating_r1_Inertia_time_event_0_raised;
	sc_boolean Statechart_main_region_Operating_r2_ReadTemperature_time_event_0_raised;
};

typedef struct StatechartEvBuf StatechartEvBuf;
struct StatechartEvBuf {
	StatechartIfaceEvBuf iface;
	StatechartIfaceLearnEvBuf ifaceLearn;
	StatechartTimeEventsEvBuf timeEvents;
};


/*! 
 * Type declaration of the data structure for the Statechart state machine.
 * This data structure has to be allocated by the client code. 
 */
struct Statechart
{
	StatechartStates stateConfVector[STATECHART_MAX_ORTHOGONAL_STATES];
	StatechartIface iface;
	StatechartIfaceLearn ifaceLearn;
	StatechartTimeEvents timeEvents;
	StatechartEvBuf current;
	sc_boolean isExecuting;
	sc_integer stateConfVectorPosition;
};



/*! Initializes the Statechart state machine data structures. Must be called before first usage.*/
extern void statechart_init(Statechart* handle);


/*! Performs a 'run to completion' step. */
extern void statechart_run_cycle(Statechart* handle);

/*! Activates the state machine. */
extern void statechart_enter(Statechart* handle);

/*! Deactivates the state machine. */
extern void statechart_exit(Statechart* handle);



/*! Raises a time event. */
extern void statechart_raise_time_event(Statechart* handle, sc_eventid evid);

/*! Gets the value of the variable 'temperature' that is defined in the default interface scope. */ 
extern float statechart_get_temperature(const Statechart* handle);
/*! Sets the value of the variable 'temperature' that is defined in the default interface scope. */ 
extern void statechart_set_temperature(Statechart* handle, float value);
/*! Gets the value of the variable 'temperature_int' that is defined in the default interface scope. */ 
extern int16_t statechart_get_temperature_int(const Statechart* handle);
/*! Sets the value of the variable 'temperature_int' that is defined in the default interface scope. */ 
extern void statechart_set_temperature_int(Statechart* handle, int16_t value);
/*! Raises the in event 'okPressed' that is defined in the default interface scope. */ 
extern void statechart_raise_okPressed(Statechart* handle);
/*! Raises the in event 'cancelPressed' that is defined in the default interface scope. */ 
extern void statechart_raise_cancelPressed(Statechart* handle);
/*! Raises the in event 'yesPressed' that is defined in the default interface scope. */ 
extern void statechart_raise_yesPressed(Statechart* handle);
/*! Raises the in event 'noPressed' that is defined in the default interface scope. */ 
extern void statechart_raise_noPressed(Statechart* handle);
/*! Raises the in event 'startPressed' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_raise_startPressed(Statechart* handle);
/*! Raises the in event 'stopPressed' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_raise_stopPressed(Statechart* handle);
/*! Raises the in event 'cancelPressed' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_raise_cancelPressed(Statechart* handle);
/*! Raises the in event 'phaseCompleted' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_raise_phaseCompleted(Statechart* handle);
/*! Raises the in event 'failure' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_raise_failure(Statechart* handle);
/*! Gets the value of the variable 'current_state_time' that is defined in the interface scope 'learn'. */ 
extern uint16_t statechart_learn_get_current_state_time(const Statechart* handle);
/*! Sets the value of the variable 'current_state_time' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_set_current_state_time(Statechart* handle, uint16_t value);
/*! Gets the value of the variable 'total_time' that is defined in the interface scope 'learn'. */ 
extern uint16_t statechart_learn_get_total_time(const Statechart* handle);
/*! Sets the value of the variable 'total_time' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_set_total_time(Statechart* handle, uint16_t value);
/*! Gets the value of the variable 'duty_cycle' that is defined in the interface scope 'learn'. */ 
extern uint8_t statechart_learn_get_duty_cycle(const Statechart* handle);
/*! Sets the value of the variable 'duty_cycle' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_set_duty_cycle(Statechart* handle, uint8_t value);
/*! Gets the value of the variable 't_overtemp' that is defined in the interface scope 'learn'. */ 
extern uint16_t statechart_learn_get_t_overtemp(const Statechart* handle);
/*! Sets the value of the variable 't_overtemp' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_set_t_overtemp(Statechart* handle, uint16_t value);
/*! Gets the value of the variable 'duty_delay' that is defined in the interface scope 'learn'. */ 
extern uint16_t statechart_learn_get_duty_delay(const Statechart* handle);
/*! Sets the value of the variable 'duty_delay' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_set_duty_delay(Statechart* handle, uint16_t value);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean statechart_is_active(const Statechart* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean statechart_is_final(const Statechart* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean statechart_is_state_active(const Statechart* handle, StatechartStates state);


#ifdef __cplusplus
}
#endif 

#endif /* STATECHART_H_ */
