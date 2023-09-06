#ifndef FSM_H
#define FSM_H

#include "sensor.h"

typedef enum
{
  ENTRY_EVENT = SENSOR_BOTH_ACTIVE+1, 
  TIMEOUT,
  EXIT_EVENT,
}Event;

typedef enum { TRAN_STATUS, HANDLED_STATUS, IGNORED_STATUS, INIT_STATUS } State;
typedef struct Fsm Fsm; /* forward declaration */
typedef State (*StateHandler)(Fsm * me, Event const * const e);

struct Fsm {
    StateHandler state; /* the "state variable" */
    StateHandler next_state;
};

State Lighting_ON(Fsm *me, Event const * const e);
State Lighting_OFF(Fsm *me, Event const * const e);
State Lighting_TURNING(Fsm *me, Event const * const e);
State Lighting_LIGHT_MODE_CHANGE(Fsm *me, Event const * const e);

#endif