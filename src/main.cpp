#include <Arduino.h>
#include "sensor.h"
#include "timer.h"
#include "fsm.h"
#include "led_controller.h"

// put function declarations here:

static Event const entryEvt = { ENTRY_EVENT };
static Event const exitEvt  = { EXIT_EVENT };
LightFSM my_fsm;


void setup() {
  // put your setup code here, to run once:
  Sensor_Init();
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
    //Serial.println(ev);

  }

  my_fsm.dispatch(ev);
  // put your main code here, to run repeatedly:
  delay(10);
}






