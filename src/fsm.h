#ifndef FSM_H
#define FSM_H

#include "sensor.h"
#include "led_controller.h"

typedef enum
{
  ENTRY_EVENT = SENSOR_STATE_NUM, 
  TIMEOUT,
  EXIT_EVENT,
}Event;
class Fsm {
public:
   typedef void(Fsm::*State)(Event ev);
   Fsm(State initial) : myState(initial) {}                 
   void init() { (this->*myState)(ENTRY_EVENT); }
   void dispatch(Event ev) { (this->*myState)(ev); }
protected:
   void tran(State target) { 
      dispatch(EXIT_EVENT);   
      myState = target; 
      dispatch(ENTRY_EVENT);
   }
   #define TRAN(target_) tran(static_cast<State>(target_))
protected:   
   State myState;
};


class LightFSM : public Fsm {
public:
   LightFSM();

private:
   LedController led_ctrl;
   void Lighting_OFF(Event ev);
   void Lighting_TURNING(Event ev);
   void Lighting_ON(Event ev);
   void Lighting_LIGHT_MODE_CHANGE(Event ev);
   void Lighting_LIGHT_POWER_SETTING(Event ev);
   void Lighting_LIGHT_DIMMING(Event ev);
   void Lighting_LIGHT_BRIGHTENING(Event ev);
};



#endif  // FSM_H