#include <Arduino.h>
#include "sensor.h"
#include "timer.h"
#include "fsm.h"
#include "led_controller.h"

// put function declarations here:

static Event const entryEvt = { ENTRY_EVENT };
static Event const exitEvt  = { EXIT_EVENT };
Fsm my_fsm = {
  .state = Lighting_OFF,
  .next_state = Lighting_OFF,
};

void Fsm_dispatch(Fsm * me, Event const * const e) {
    State status;
    StateHandler prev_state = me->state; /* save for later */

    status = (*me->state)(me, e);
    
    if (status == TRAN_STATUS) { /* transition taken? */
        (*prev_state)(me, &exitEvt);
        me->state = me->next_state;
        (*me->state)(me, &entryEvt);
    }
}

void setup() {
  // put your setup code here, to run once:
  Sensor_Init();
  led_controller_init();
  Serial.begin(9600);
}

Event translator(Sensor_State_t sensor_state)
{
  return (Event)(sensor_state);
}

Event ev = ENTRY_EVENT;

void loop() {
  Sensor_refresh();
  if( timer_update(10) == TIMEOUT_OCCURED)
  {
    ev = TIMEOUT;
  }
  else
  {
    ev = translator(Sensor_GetState());

  }

  Fsm_dispatch(&my_fsm, &ev);
  // put your main code here, to run repeatedly:
  delay(10);
}






