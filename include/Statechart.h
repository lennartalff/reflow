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
#include "../src/sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'Statechart'.
*/

/*! Define number of states in the state enum */
#define STATECHART_STATE_COUNT 6

/*! Define dimension of the state configuration vector for orthogonal states. */
#define STATECHART_MAX_ORTHOGONAL_STATES 1
/*! Define maximum number of time events that can be active at once */
#define STATECHART_MAX_PARALLEL_TIME_EVENTS 1

/*! Define indices of states in the StateConfVector */
#define SCVI_STATECHART_MAIN_REGION_OPERATING 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_IDLE 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_HEATRAMP 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_ABORT 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_COOLING 0
#define SCVI_STATECHART_MAIN_REGION_OPERATING_R1_FAIL 0

/*! Enumeration of all states */ 
typedef enum
{
	Statechart_last_state,
	Statechart_main_region_Operating,
	Statechart_main_region_Operating_r1_Idle,
	Statechart_main_region_Operating_r1_HeatRamp,
	Statechart_main_region_Operating_r1_Abort,
	Statechart_main_region_Operating_r1_Cooling,
	Statechart_main_region_Operating_r1_Fail
} StatechartStates;






/*! Type declaration of the data structure for the StatechartIface interface scope. */
struct StatechartIface
{
	float temperature;
};



/*! Type declaration of the data structure for the StatechartIfaceLearn interface scope. */
struct StatechartIfaceLearn
{
	sc_boolean startPressed_raised;
	sc_boolean stopPressed_raised;
	sc_boolean okPressed_raised;
	uint16_t current_state_time;
	uint16_t total_time;
};



/*! Type declaration of the data structure for the StatechartTimeEvents interface scope. */
struct StatechartTimeEvents
{
	sc_boolean statechart_main_region_Operating_r1_HeatRamp_tev0_raised;
};





typedef struct StatechartIfaceLearnEvBuf StatechartIfaceLearnEvBuf;
struct StatechartIfaceLearnEvBuf {
	sc_boolean startPressed_raised;
	sc_boolean stopPressed_raised;
	sc_boolean okPressed_raised;
};

typedef struct StatechartTimeEventsEvBuf StatechartTimeEventsEvBuf;
struct StatechartTimeEventsEvBuf {
	sc_boolean Statechart_main_region_Operating_r1_HeatRamp_time_event_0_raised;
};

typedef struct StatechartEvBuf StatechartEvBuf;
struct StatechartEvBuf {
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
/*! Raises the in event 'startPressed' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_raise_startPressed(Statechart* handle);
/*! Raises the in event 'stopPressed' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_raise_stopPressed(Statechart* handle);
/*! Raises the in event 'okPressed' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_raise_okPressed(Statechart* handle);
/*! Gets the value of the variable 'current_state_time' that is defined in the interface scope 'learn'. */ 
extern uint16_t statechart_learn_get_current_state_time(const Statechart* handle);
/*! Sets the value of the variable 'current_state_time' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_set_current_state_time(Statechart* handle, uint16_t value);
/*! Gets the value of the variable 'total_time' that is defined in the interface scope 'learn'. */ 
extern uint16_t statechart_learn_get_total_time(const Statechart* handle);
/*! Sets the value of the variable 'total_time' that is defined in the interface scope 'learn'. */ 
extern void statechart_learn_set_total_time(Statechart* handle, uint16_t value);

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
