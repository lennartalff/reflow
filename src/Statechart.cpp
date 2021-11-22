/** Generated by YAKINDU Statechart Tools code generator. */


#include "../src/sc_types.h"

#include "Statechart.h"
#include "Statechart_required.h"

/*! \file Implementation of the state machine 'Statechart'
*/

#ifndef SC_UNUSED
#define SC_UNUSED(P) (void)(P)
#endif

/* prototypes of all internal functions */
static void enact_main_region_Operating_r1_Idle(Statechart* handle);
static void enact_main_region_Operating_r1_HeatRamp(Statechart* handle);
static void enact_main_region_Operating_r1_Abort(Statechart* handle);
static void enact_main_region_Operating_r1_Cooling(Statechart* handle);
static void enact_main_region_Operating_r1_Fail(Statechart* handle);
static void enact_main_region_Operating_r1_HeatConst(Statechart* handle);
static void enact_main_region_Operating_r2_ReadTemperature(Statechart* handle);
static void exact_main_region_Operating_r1_HeatRamp(Statechart* handle);
static void exact_main_region_Operating_r1_HeatConst(Statechart* handle);
static void exact_main_region_Operating_r2_ReadTemperature(Statechart* handle);
static void enseq_main_region_Operating_r1_Idle_default(Statechart* handle);
static void enseq_main_region_Operating_r1_HeatRamp_default(Statechart* handle);
static void enseq_main_region_Operating_r1_Abort_default(Statechart* handle);
static void enseq_main_region_Operating_r1_Cooling_default(Statechart* handle);
static void enseq_main_region_Operating_r1_Fail_default(Statechart* handle);
static void enseq_main_region_Operating_r1_HeatConst_default(Statechart* handle);
static void enseq_main_region_Operating_r2_ReadTemperature_default(Statechart* handle);
static void enseq_main_region_default(Statechart* handle);
static void enseq_main_region_Operating_r2_default(Statechart* handle);
static void exseq_main_region_Operating_r1_Idle(Statechart* handle);
static void exseq_main_region_Operating_r1_HeatRamp(Statechart* handle);
static void exseq_main_region_Operating_r1_Abort(Statechart* handle);
static void exseq_main_region_Operating_r1_Cooling(Statechart* handle);
static void exseq_main_region_Operating_r1_Fail(Statechart* handle);
static void exseq_main_region_Operating_r1_HeatConst(Statechart* handle);
static void exseq_main_region_Operating_r2_ReadTemperature(Statechart* handle);
static void exseq_main_region(Statechart* handle);
static void react_main_region__entry_Default(Statechart* handle);
static void react_main_region_Operating_r2__entry_Default(Statechart* handle);

/*! State machine reactions. */
static sc_integer react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state Operating. */
static sc_integer main_region_Operating_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state Idle. */
static sc_integer main_region_Operating_r1_Idle_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state HeatRamp. */
static sc_integer main_region_Operating_r1_HeatRamp_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state Abort. */
static sc_integer main_region_Operating_r1_Abort_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state Cooling. */
static sc_integer main_region_Operating_r1_Cooling_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state Fail. */
static sc_integer main_region_Operating_r1_Fail_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state HeatConst. */
static sc_integer main_region_Operating_r1_HeatConst_react(Statechart* handle, const sc_integer transitioned_before);

/*! The reactions of state ReadTemperature. */
static sc_integer main_region_Operating_r2_ReadTemperature_react(Statechart* handle, const sc_integer transitioned_before);


static void swap_in_events(Statechart* handle);

static void clear_in_events(Statechart* handle);

static void micro_step(Statechart* handle);





void statechart_init(Statechart* handle)
{
	sc_integer i;
	
	for (i = 0; i < STATECHART_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = Statechart_last_state;
	}
	
				
	clear_in_events(handle);
	swap_in_events(handle);
	
	
	/* Default init sequence for statechart Statechart */
	handle->iface.temperature = 0.0;
	handle->iface.temperature_int = 0;
	handle->ifaceLearn.current_state_time = 0;
	handle->ifaceLearn.total_time = 0;
	handle->ifaceLearn.duty_cycle = 0;
	handle->ifaceLearn.t_overtemp = 0;
	
	handle->isExecuting = bool_false;
}

void statechart_run_cycle(Statechart* handle)
{
	/* Performs a 'run to completion' step. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	swap_in_events(handle);
	micro_step(handle);
	handle->isExecuting = bool_false;
}

void statechart_enter(Statechart* handle)
{
	/* Activates the state machine. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	/* Default enter sequence for statechart Statechart */
	enseq_main_region_default(handle);
	handle->isExecuting = bool_false;
}

void statechart_exit(Statechart* handle)
{
	/* Deactivates the state machine. */
	if (handle->isExecuting == bool_true)
	{ 
		return;
	} 
	handle->isExecuting = bool_true;
	/* Default exit sequence for statechart Statechart */
	exseq_main_region(handle);
	handle->isExecuting = bool_false;
}


sc_boolean statechart_is_active(const Statechart* handle)
{
	sc_boolean result = bool_false;
	sc_integer i;
	
	for(i = 0; i < STATECHART_MAX_ORTHOGONAL_STATES; i++)
	{
		result = result || handle->stateConfVector[i] != Statechart_last_state;
	}
	
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean statechart_is_final(const Statechart* handle)
{
	SC_UNUSED(handle);
	return bool_false;
}

void statechart_raise_time_event(Statechart* handle, sc_eventid evid)
{
	if ( ((sc_intptr_t)evid) >= ((sc_intptr_t)&(handle->timeEvents))
		&&  ((sc_intptr_t)evid) < ((sc_intptr_t)&(handle->timeEvents)) + (unsigned)sizeof(StatechartTimeEvents))
		{
		*(sc_boolean*)evid = bool_true;
	}
}

sc_boolean statechart_is_state_active(const Statechart* handle, StatechartStates state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case Statechart_main_region_Operating :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_OPERATING] >= Statechart_main_region_Operating
				&& handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_OPERATING] <= Statechart_main_region_Operating_r2_ReadTemperature);
			break;
		case Statechart_main_region_Operating_r1_Idle :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_OPERATING_R1_IDLE] == Statechart_main_region_Operating_r1_Idle
			);
			break;
		case Statechart_main_region_Operating_r1_HeatRamp :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_OPERATING_R1_HEATRAMP] == Statechart_main_region_Operating_r1_HeatRamp
			);
			break;
		case Statechart_main_region_Operating_r1_Abort :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_OPERATING_R1_ABORT] == Statechart_main_region_Operating_r1_Abort
			);
			break;
		case Statechart_main_region_Operating_r1_Cooling :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_OPERATING_R1_COOLING] == Statechart_main_region_Operating_r1_Cooling
			);
			break;
		case Statechart_main_region_Operating_r1_Fail :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_OPERATING_R1_FAIL] == Statechart_main_region_Operating_r1_Fail
			);
			break;
		case Statechart_main_region_Operating_r1_HeatConst :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_OPERATING_R1_HEATCONST] == Statechart_main_region_Operating_r1_HeatConst
			);
			break;
		case Statechart_main_region_Operating_r2_ReadTemperature :
			result = (sc_boolean) (handle->stateConfVector[SCVI_STATECHART_MAIN_REGION_OPERATING_R2_READTEMPERATURE] == Statechart_main_region_Operating_r2_ReadTemperature
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}

static void swap_in_events(Statechart* handle)
{
	handle->current.iface.okPressed_raised = handle->iface.okPressed_raised;
	handle->iface.okPressed_raised = bool_false;
	handle->current.iface.cancelPressed_raised = handle->iface.cancelPressed_raised;
	handle->iface.cancelPressed_raised = bool_false;
	handle->current.iface.yesPressed_raised = handle->iface.yesPressed_raised;
	handle->iface.yesPressed_raised = bool_false;
	handle->current.iface.noPressed_raised = handle->iface.noPressed_raised;
	handle->iface.noPressed_raised = bool_false;
	handle->current.ifaceLearn.startPressed_raised = handle->ifaceLearn.startPressed_raised;
	handle->ifaceLearn.startPressed_raised = bool_false;
	handle->current.ifaceLearn.stopPressed_raised = handle->ifaceLearn.stopPressed_raised;
	handle->ifaceLearn.stopPressed_raised = bool_false;
	handle->current.ifaceLearn.cancelPressed_raised = handle->ifaceLearn.cancelPressed_raised;
	handle->ifaceLearn.cancelPressed_raised = bool_false;
	handle->current.ifaceLearn.phaseCompleted_raised = handle->ifaceLearn.phaseCompleted_raised;
	handle->ifaceLearn.phaseCompleted_raised = bool_false;
	handle->current.ifaceLearn.failure_raised = handle->ifaceLearn.failure_raised;
	handle->ifaceLearn.failure_raised = bool_false;
	handle->current.timeEvents.Statechart_main_region_Operating_r1_HeatRamp_time_event_0_raised = handle->timeEvents.statechart_main_region_Operating_r1_HeatRamp_tev0_raised;
	handle->timeEvents.statechart_main_region_Operating_r1_HeatRamp_tev0_raised = bool_false;
	handle->current.timeEvents.Statechart_main_region_Operating_r1_HeatConst_time_event_0_raised = handle->timeEvents.statechart_main_region_Operating_r1_HeatConst_tev0_raised;
	handle->timeEvents.statechart_main_region_Operating_r1_HeatConst_tev0_raised = bool_false;
	handle->current.timeEvents.Statechart_main_region_Operating_r2_ReadTemperature_time_event_0_raised = handle->timeEvents.statechart_main_region_Operating_r2_ReadTemperature_tev0_raised;
	handle->timeEvents.statechart_main_region_Operating_r2_ReadTemperature_tev0_raised = bool_false;
}

static void clear_in_events(Statechart* handle)
{
	handle->iface.okPressed_raised = bool_false;
	handle->iface.cancelPressed_raised = bool_false;
	handle->iface.yesPressed_raised = bool_false;
	handle->iface.noPressed_raised = bool_false;
	handle->ifaceLearn.startPressed_raised = bool_false;
	handle->ifaceLearn.stopPressed_raised = bool_false;
	handle->ifaceLearn.cancelPressed_raised = bool_false;
	handle->ifaceLearn.phaseCompleted_raised = bool_false;
	handle->ifaceLearn.failure_raised = bool_false;
	handle->timeEvents.statechart_main_region_Operating_r1_HeatRamp_tev0_raised = bool_false;
	handle->timeEvents.statechart_main_region_Operating_r1_HeatConst_tev0_raised = bool_false;
	handle->timeEvents.statechart_main_region_Operating_r2_ReadTemperature_tev0_raised = bool_false;
}

static void micro_step(Statechart* handle)
{
 			sc_integer transitioned = -1;
	handle->stateConfVectorPosition = 0;
	switch(handle->stateConfVector[ 0 ])
	{
		case Statechart_main_region_Operating_r1_Idle :
		{
			transitioned = main_region_Operating_r1_Idle_react(handle, transitioned);
			break;
		}
		case Statechart_main_region_Operating_r1_HeatRamp :
		{
			transitioned = main_region_Operating_r1_HeatRamp_react(handle, transitioned);
			break;
		}
		case Statechart_main_region_Operating_r1_Abort :
		{
			transitioned = main_region_Operating_r1_Abort_react(handle, transitioned);
			break;
		}
		case Statechart_main_region_Operating_r1_Cooling :
		{
			transitioned = main_region_Operating_r1_Cooling_react(handle, transitioned);
			break;
		}
		case Statechart_main_region_Operating_r1_Fail :
		{
			transitioned = main_region_Operating_r1_Fail_react(handle, transitioned);
			break;
		}
		case Statechart_main_region_Operating_r1_HeatConst :
		{
			transitioned = main_region_Operating_r1_HeatConst_react(handle, transitioned);
			break;
		}
		default: break;
	}
	if ((handle->stateConfVectorPosition) < (1))
	{ 
		switch(handle->stateConfVector[ 1 ])
		{
			case Statechart_main_region_Operating_r2_ReadTemperature :
			{
				transitioned = main_region_Operating_r2_ReadTemperature_react(handle, transitioned);
				break;
			}
			default: break;
		}
	} 
}


void statechart_raise_okPressed(Statechart* handle)
{
	handle->iface.okPressed_raised = bool_true;
}

void statechart_raise_cancelPressed(Statechart* handle)
{
	handle->iface.cancelPressed_raised = bool_true;
}

void statechart_raise_yesPressed(Statechart* handle)
{
	handle->iface.yesPressed_raised = bool_true;
}

void statechart_raise_noPressed(Statechart* handle)
{
	handle->iface.noPressed_raised = bool_true;
}



float statechart_get_temperature(const Statechart* handle)
{
	return handle->iface.temperature;
}
void statechart_set_temperature(Statechart* handle, float value)
{
	handle->iface.temperature = value;
}
int16_t statechart_get_temperature_int(const Statechart* handle)
{
	return handle->iface.temperature_int;
}
void statechart_set_temperature_int(Statechart* handle, int16_t value)
{
	handle->iface.temperature_int = value;
}
void statechart_learn_raise_startPressed(Statechart* handle)
{
	handle->ifaceLearn.startPressed_raised = bool_true;
}

void statechart_learn_raise_stopPressed(Statechart* handle)
{
	handle->ifaceLearn.stopPressed_raised = bool_true;
}

void statechart_learn_raise_cancelPressed(Statechart* handle)
{
	handle->ifaceLearn.cancelPressed_raised = bool_true;
}

void statechart_learn_raise_phaseCompleted(Statechart* handle)
{
	handle->ifaceLearn.phaseCompleted_raised = bool_true;
}

void statechart_learn_raise_failure(Statechart* handle)
{
	handle->ifaceLearn.failure_raised = bool_true;
}



uint16_t statechart_learn_get_current_state_time(const Statechart* handle)
{
	return handle->ifaceLearn.current_state_time;
}
void statechart_learn_set_current_state_time(Statechart* handle, uint16_t value)
{
	handle->ifaceLearn.current_state_time = value;
}
uint16_t statechart_learn_get_total_time(const Statechart* handle)
{
	return handle->ifaceLearn.total_time;
}
void statechart_learn_set_total_time(Statechart* handle, uint16_t value)
{
	handle->ifaceLearn.total_time = value;
}
uint8_t statechart_learn_get_duty_cycle(const Statechart* handle)
{
	return handle->ifaceLearn.duty_cycle;
}
void statechart_learn_set_duty_cycle(Statechart* handle, uint8_t value)
{
	handle->ifaceLearn.duty_cycle = value;
}
uint16_t statechart_learn_get_t_overtemp(const Statechart* handle)
{
	return handle->ifaceLearn.t_overtemp;
}
void statechart_learn_set_t_overtemp(Statechart* handle, uint16_t value)
{
	handle->ifaceLearn.t_overtemp = value;
}

/* implementations of all internal functions */

/* Entry action for state 'Idle'. */
static void enact_main_region_Operating_r1_Idle(Statechart* handle)
{
	SC_UNUSED(handle);
	/* Entry action for state 'Idle'. */
	learn_guiSetStateText((sc_string) "idle");
	actuators_switchHeating(bool_false);
	learn_guiSetInfoText((sc_string) "Ready to start the learning procedure.");
}

/* Entry action for state 'HeatRamp'. */
static void enact_main_region_Operating_r1_HeatRamp(Statechart* handle)
{
	/* Entry action for state 'HeatRamp'. */
	statechart_set_timer(handle, (sc_eventid) &(handle->timeEvents.statechart_main_region_Operating_r1_HeatRamp_tev0_raised) , 1000, bool_true);
	learn_guiSetStateText((sc_string) "HeatRamp");
	learn_guiSetInfoText((sc_string) "Keep heating until reaching soak temperature.");
	handle->ifaceLearn.current_state_time = 0;
	handle->ifaceLearn.total_time = 0;
	learn_setDutyCycle(LEARN_RAMP_INITIAL_DUTY_CYCLE);
}

/* Entry action for state 'Abort'. */
static void enact_main_region_Operating_r1_Abort(Statechart* handle)
{
	SC_UNUSED(handle);
	/* Entry action for state 'Abort'. */
	learn_guiSetStateText((sc_string) "aborted");
	actuators_switchHeating(bool_false);
}

/* Entry action for state 'Cooling'. */
static void enact_main_region_Operating_r1_Cooling(Statechart* handle)
{
	SC_UNUSED(handle);
	/* Entry action for state 'Cooling'. */
	learn_guiSetStateText((sc_string) "cooling");
	actuators_switchHeating(bool_false);
	learn_setDutyCycle(0);
	learn_guiSetInfoText((sc_string) "Wait until oven temperature is below threshold.");
}

/* Entry action for state 'Fail'. */
static void enact_main_region_Operating_r1_Fail(Statechart* handle)
{
	SC_UNUSED(handle);
	/* Entry action for state 'Fail'. */
	learn_setDutyCycle(0);
	learn_showFailPage();
}

/* Entry action for state 'HeatConst'. */
static void enact_main_region_Operating_r1_HeatConst(Statechart* handle)
{
	/* Entry action for state 'HeatConst'. */
	statechart_set_timer(handle, (sc_eventid) &(handle->timeEvents.statechart_main_region_Operating_r1_HeatConst_tev0_raised) , 1000, bool_true);
	learn_guiSetStateText((sc_string) "HeatConst");
	handle->ifaceLearn.current_state_time = 0;
	handle->ifaceLearn.t_overtemp = 0;
}

/* Entry action for state 'ReadTemperature'. */
static void enact_main_region_Operating_r2_ReadTemperature(Statechart* handle)
{
	/* Entry action for state 'ReadTemperature'. */
	statechart_set_timer(handle, (sc_eventid) &(handle->timeEvents.statechart_main_region_Operating_r2_ReadTemperature_tev0_raised) , 200, bool_true);
}

/* Exit action for state 'HeatRamp'. */
static void exact_main_region_Operating_r1_HeatRamp(Statechart* handle)
{
	/* Exit action for state 'HeatRamp'. */
	statechart_unset_timer(handle, (sc_eventid) &(handle->timeEvents.statechart_main_region_Operating_r1_HeatRamp_tev0_raised) );		
}

/* Exit action for state 'HeatConst'. */
static void exact_main_region_Operating_r1_HeatConst(Statechart* handle)
{
	/* Exit action for state 'HeatConst'. */
	statechart_unset_timer(handle, (sc_eventid) &(handle->timeEvents.statechart_main_region_Operating_r1_HeatConst_tev0_raised) );		
}

/* Exit action for state 'ReadTemperature'. */
static void exact_main_region_Operating_r2_ReadTemperature(Statechart* handle)
{
	/* Exit action for state 'ReadTemperature'. */
	statechart_unset_timer(handle, (sc_eventid) &(handle->timeEvents.statechart_main_region_Operating_r2_ReadTemperature_tev0_raised) );		
}

/* 'default' enter sequence for state Idle */
static void enseq_main_region_Operating_r1_Idle_default(Statechart* handle)
{
	/* 'default' enter sequence for state Idle */
	enact_main_region_Operating_r1_Idle(handle);
	handle->stateConfVector[0] = Statechart_main_region_Operating_r1_Idle;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state HeatRamp */
static void enseq_main_region_Operating_r1_HeatRamp_default(Statechart* handle)
{
	/* 'default' enter sequence for state HeatRamp */
	enact_main_region_Operating_r1_HeatRamp(handle);
	handle->stateConfVector[0] = Statechart_main_region_Operating_r1_HeatRamp;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Abort */
static void enseq_main_region_Operating_r1_Abort_default(Statechart* handle)
{
	/* 'default' enter sequence for state Abort */
	enact_main_region_Operating_r1_Abort(handle);
	handle->stateConfVector[0] = Statechart_main_region_Operating_r1_Abort;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Cooling */
static void enseq_main_region_Operating_r1_Cooling_default(Statechart* handle)
{
	/* 'default' enter sequence for state Cooling */
	enact_main_region_Operating_r1_Cooling(handle);
	handle->stateConfVector[0] = Statechart_main_region_Operating_r1_Cooling;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state Fail */
static void enseq_main_region_Operating_r1_Fail_default(Statechart* handle)
{
	/* 'default' enter sequence for state Fail */
	enact_main_region_Operating_r1_Fail(handle);
	handle->stateConfVector[0] = Statechart_main_region_Operating_r1_Fail;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state HeatConst */
static void enseq_main_region_Operating_r1_HeatConst_default(Statechart* handle)
{
	/* 'default' enter sequence for state HeatConst */
	enact_main_region_Operating_r1_HeatConst(handle);
	handle->stateConfVector[0] = Statechart_main_region_Operating_r1_HeatConst;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state ReadTemperature */
static void enseq_main_region_Operating_r2_ReadTemperature_default(Statechart* handle)
{
	/* 'default' enter sequence for state ReadTemperature */
	enact_main_region_Operating_r2_ReadTemperature(handle);
	handle->stateConfVector[1] = Statechart_main_region_Operating_r2_ReadTemperature;
	handle->stateConfVectorPosition = 1;
}

/* 'default' enter sequence for region main region */
static void enseq_main_region_default(Statechart* handle)
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default(handle);
}

/* 'default' enter sequence for region r2 */
static void enseq_main_region_Operating_r2_default(Statechart* handle)
{
	/* 'default' enter sequence for region r2 */
	react_main_region_Operating_r2__entry_Default(handle);
}

/* Default exit sequence for state Idle */
static void exseq_main_region_Operating_r1_Idle(Statechart* handle)
{
	/* Default exit sequence for state Idle */
	handle->stateConfVector[0] = Statechart_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state HeatRamp */
static void exseq_main_region_Operating_r1_HeatRamp(Statechart* handle)
{
	/* Default exit sequence for state HeatRamp */
	handle->stateConfVector[0] = Statechart_last_state;
	handle->stateConfVectorPosition = 0;
	exact_main_region_Operating_r1_HeatRamp(handle);
}

/* Default exit sequence for state Abort */
static void exseq_main_region_Operating_r1_Abort(Statechart* handle)
{
	/* Default exit sequence for state Abort */
	handle->stateConfVector[0] = Statechart_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Cooling */
static void exseq_main_region_Operating_r1_Cooling(Statechart* handle)
{
	/* Default exit sequence for state Cooling */
	handle->stateConfVector[0] = Statechart_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Fail */
static void exseq_main_region_Operating_r1_Fail(Statechart* handle)
{
	/* Default exit sequence for state Fail */
	handle->stateConfVector[0] = Statechart_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state HeatConst */
static void exseq_main_region_Operating_r1_HeatConst(Statechart* handle)
{
	/* Default exit sequence for state HeatConst */
	handle->stateConfVector[0] = Statechart_last_state;
	handle->stateConfVectorPosition = 0;
	exact_main_region_Operating_r1_HeatConst(handle);
}

/* Default exit sequence for state ReadTemperature */
static void exseq_main_region_Operating_r2_ReadTemperature(Statechart* handle)
{
	/* Default exit sequence for state ReadTemperature */
	handle->stateConfVector[1] = Statechart_last_state;
	handle->stateConfVectorPosition = 1;
	exact_main_region_Operating_r2_ReadTemperature(handle);
}

/* Default exit sequence for region main region */
static void exseq_main_region(Statechart* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of Statechart.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case Statechart_main_region_Operating_r1_Idle :
		{
			exseq_main_region_Operating_r1_Idle(handle);
			break;
		}
		case Statechart_main_region_Operating_r1_HeatRamp :
		{
			exseq_main_region_Operating_r1_HeatRamp(handle);
			break;
		}
		case Statechart_main_region_Operating_r1_Abort :
		{
			exseq_main_region_Operating_r1_Abort(handle);
			break;
		}
		case Statechart_main_region_Operating_r1_Cooling :
		{
			exseq_main_region_Operating_r1_Cooling(handle);
			break;
		}
		case Statechart_main_region_Operating_r1_Fail :
		{
			exseq_main_region_Operating_r1_Fail(handle);
			break;
		}
		case Statechart_main_region_Operating_r1_HeatConst :
		{
			exseq_main_region_Operating_r1_HeatConst(handle);
			break;
		}
		default: break;
	}
	/* Handle exit of all possible states (of Statechart.main_region) at position 1... */
	switch(handle->stateConfVector[ 1 ])
	{
		case Statechart_main_region_Operating_r2_ReadTemperature :
		{
			exseq_main_region_Operating_r2_ReadTemperature(handle);
			break;
		}
		default: break;
	}
}

/* Default react sequence for initial entry  */
static void react_main_region__entry_Default(Statechart* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Operating_r1_Idle_default(handle);
	enseq_main_region_Operating_r2_default(handle);
}

/* Default react sequence for initial entry  */
static void react_main_region_Operating_r2__entry_Default(Statechart* handle)
{
	/* Default react sequence for initial entry  */
	enseq_main_region_Operating_r2_ReadTemperature_default(handle);
}


static sc_integer react(Statechart* handle, const sc_integer transitioned_before)
{
	/* State machine reactions. */
	SC_UNUSED(handle);
	return transitioned_before;
}

static sc_integer main_region_Operating_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state Operating. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
	} /* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = react(handle, transitioned_before);
	} return transitioned_after;
}

static sc_integer main_region_Operating_r1_Idle_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state Idle. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (((handle->current.ifaceLearn.startPressed_raised) == bool_true) && (((handle->iface.temperature) < (LEARN_COOLED_DOWN_TEMP)) == bool_true))
		{ 
			exseq_main_region_Operating_r1_Idle(handle);
			enseq_main_region_Operating_r1_HeatRamp_default(handle);
			transitioned_after = 0;
		}  else
		{
			if ((handle->iface.temperature) > (LEARN_COOLED_DOWN_TEMP))
			{ 
				exseq_main_region_Operating_r1_Idle(handle);
				enseq_main_region_Operating_r1_Cooling_default(handle);
				transitioned_after = 0;
			} 
		}
	} return transitioned_after;
}

static sc_integer main_region_Operating_r1_HeatRamp_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state HeatRamp. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (handle->current.ifaceLearn.stopPressed_raised == bool_true)
		{ 
			exseq_main_region_Operating_r1_HeatRamp(handle);
			enseq_main_region_Operating_r1_Abort_default(handle);
			transitioned_after = 0;
		}  else
		{
			if ((handle->ifaceLearn.current_state_time) >= (LEARN_RAMP_TIME_SECS))
			{ 
				exseq_main_region_Operating_r1_HeatRamp(handle);
				learn_setFailText((sc_string) "Failed to reach target temperature in time!\nStop heating.");
				enseq_main_region_Operating_r1_Fail_default(handle);
				transitioned_after = 0;
			}  else
			{
				if (handle->current.ifaceLearn.phaseCompleted_raised == bool_true)
				{ 
					exseq_main_region_Operating_r1_HeatRamp(handle);
					enseq_main_region_Operating_r1_HeatConst_default(handle);
					transitioned_after = 0;
				} 
			}
		}
	} /* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		if (handle->current.timeEvents.Statechart_main_region_Operating_r1_HeatRamp_time_event_0_raised == bool_true)
		{ 
			handle->ifaceLearn.current_state_time++;
			handle->ifaceLearn.total_time++;
			learn_setProgress(((100 * handle->iface.temperature_int) / ((LEARN_SOAKING_TEMP - LEARN_RAMP_COMPLETED_TEMP_DIFF))));
			learn_updateHeatRampDuty();
			learn_guiSetTime((LEARN_RAMP_TIME_SECS - handle->ifaceLearn.current_state_time));
		} 
	} return transitioned_after;
}

static sc_integer main_region_Operating_r1_Abort_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state Abort. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		exseq_main_region_Operating_r1_Abort(handle);
		enseq_main_region_Operating_r1_Cooling_default(handle);
		transitioned_after = 0;
	} return transitioned_after;
}

static sc_integer main_region_Operating_r1_Cooling_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state Cooling. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if ((handle->iface.temperature) < (LEARN_COOLED_DOWN_TEMP))
		{ 
			exseq_main_region_Operating_r1_Cooling(handle);
			enseq_main_region_Operating_r1_Idle_default(handle);
			transitioned_after = 0;
		} 
	} return transitioned_after;
}

static sc_integer main_region_Operating_r1_Fail_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state Fail. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (handle->current.iface.okPressed_raised == bool_true)
		{ 
			exseq_main_region_Operating_r1_Fail(handle);
			enseq_main_region_Operating_r1_Abort_default(handle);
			transitioned_after = 0;
		} 
	} return transitioned_after;
}

static sc_integer main_region_Operating_r1_HeatConst_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state HeatConst. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
	} /* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		if (handle->current.timeEvents.Statechart_main_region_Operating_r1_HeatConst_time_event_0_raised == bool_true)
		{ 
			handle->ifaceLearn.current_state_time++;
			handle->ifaceLearn.total_time++;
			learn_setProgress(((handle->ifaceLearn.current_state_time * 100) / LEARN_CONST_TIME_SECS));
			learn_updateHeatConstDuty();
			learn_guiSetTime((LEARN_CONST_TIME_SECS - handle->ifaceLearn.current_state_time));
		} 
	} return transitioned_after;
}

static sc_integer main_region_Operating_r2_ReadTemperature_react(Statechart* handle, const sc_integer transitioned_before)
{
	/* The reactions of state ReadTemperature. */
 			sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
	} /* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		if (handle->current.timeEvents.Statechart_main_region_Operating_r2_ReadTemperature_time_event_0_raised == bool_true)
		{ 
			sensors_update_temperature();
			learn_guiUpdateCurrentTemperature(handle->iface.temperature_int);
		} 
		transitioned_after = main_region_Operating_react(handle, transitioned_before);
	} return transitioned_after;
}




