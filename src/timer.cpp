#include "timer.h"
#include "Arduino.h"

uint16_t timer = 0;
timer_event_t timer_state = TIMER_NOT_ACTIVE;
uint16_t timeout_value;

void timer_activate(uint16_t timeout)
{
    if(timer_state != TIMER_ACTIVE)
    {
        timer_state = TIMER_ACTIVE;
        timeout_value = timeout;
        timer = 0;
    }
    else
    {

    }
}

timer_event_t timer_update(uint8_t milisec)
{
    timer_event_t ret_val;
    if(timer_state == TIMER_ACTIVE)
    {
        timer += milisec;
        if(timer >= timeout_value)
        {
            timer_state = TIMER_NOT_ACTIVE;
            ret_val = TIMEOUT_OCCURED;
        }
        else
        {   
            ret_val = TIMER_ACTIVE;
        }
    }
    else
    {
        ret_val = TIMER_NOT_ACTIVE;
    }
    return ret_val;
}

void timer_deactivate()
{
    timer_state = TIMER_NOT_ACTIVE;
}
