#include "fsm.h"
#include "led_controller.h"
#include "timer.h"
#include "Arduino.h"

#define MODE_CH_TIMEOUT 1500

State Lighting_LIGHT_POWER_SETTING(Fsm *me, Event const * const e);
State Lighting_LIGHT_BRIGHTENING(Fsm *me, Event const * const e);
State Lighting_LIGHT_DIMMING(Fsm *me, Event const * const e);

State Lighting_OFF(Fsm *me, Event const * const e)
{
    
    State ret_val;
    switch(*e)
    {
        case ENTRY_EVENT:
            led_off();
            ret_val = HANDLED_STATUS;
        break;

        case SENSOR_BOTH_ACTIVE:
            me->next_state = Lighting_TURNING;
            ret_val = TRAN_STATUS;
        break;

        default:
            ret_val = IGNORED_STATUS;
        break; 
    }
    return ret_val;
}

State Lighting_TURNING(Fsm *me, Event const * const e)
{
    State ret_val;
    switch(*e)
    {
        case SENSOR_IDLE:

            me->next_state = Lighting_ON;
            ret_val = TRAN_STATUS;
        break;

        default:
            ret_val = IGNORED_STATUS;
        break; 
    }

    return ret_val;
}

State Lighting_ON(Fsm *me, Event const * const e)
{
    State ret_val;
    switch(*e)
    {
        case ENTRY_EVENT:
            led_on();
            ret_val = HANDLED_STATUS;
        break;

        case SENSOR_BOTH_ACTIVE:
            me->next_state = Lighting_LIGHT_MODE_CHANGE;
            ret_val = TRAN_STATUS;
        break;

        default:
            ret_val = IGNORED_STATUS;
        break; 
    }
    return ret_val;
}

State Lighting_LIGHT_MODE_CHANGE(Fsm *me, Event const * const e)
{
    State ret_val;
    switch(*e)
    {
        case ENTRY_EVENT:
            timer_activate(MODE_CH_TIMEOUT);
            ret_val = HANDLED_STATUS;   
        break;
        case SENSOR_IDLE:
            me->next_state = Lighting_OFF;
            ret_val = TRAN_STATUS;
        break;

        case EXIT_EVENT:
            timer_deactivate();
            led_blink();
            ret_val = HANDLED_STATUS;            
        break;

        case TIMEOUT:
            me->next_state = Lighting_LIGHT_POWER_SETTING;
            ret_val = TRAN_STATUS;
        break;

        default:
            ret_val = IGNORED_STATUS;
        break; 
    }
    return ret_val;
}

State Lighting_LIGHT_POWER_SETTING(Fsm *me, Event const * const e)
{
    State ret_val;
    switch(*e)
    {
        case ENTRY_EVENT:

            ret_val = HANDLED_STATUS;   
        break;
        case SENSOR_IDLE:
            timer_activate(MODE_CH_TIMEOUT);
            ret_val = HANDLED_STATUS;
        break;

        case SENSOR_LEFT_ACTIVE:
            me->next_state = Lighting_LIGHT_BRIGHTENING;
            ret_val = TRAN_STATUS;
        break;

        case SENSOR_RIGHT_ACTIVE:
            me->next_state = Lighting_LIGHT_DIMMING;
            ret_val = TRAN_STATUS;
        break;

        case EXIT_EVENT:
            timer_deactivate();
            ret_val = HANDLED_STATUS;            
        break;

        case TIMEOUT:
            led_blink();
            me->next_state = Lighting_ON;
            ret_val = TRAN_STATUS;
        break;

        default:
            timer_deactivate();
            ret_val = IGNORED_STATUS;
        break; 
    }
    return ret_val;
}

State Lighting_LIGHT_DIMMING(Fsm *me, Event const * const e)
{
    State ret_val;
    switch(*e)
    {
        case SENSOR_IDLE:
            me->next_state = Lighting_LIGHT_POWER_SETTING;
            ret_val = TRAN_STATUS;
        break;

        default:
            led_dimming();
            ret_val = IGNORED_STATUS;
        break; 
    }
    return ret_val;
}

State Lighting_LIGHT_BRIGHTENING(Fsm *me, Event const * const e)
{
    State ret_val;
   // Serial.println("BRIGHTENING");
    switch(*e)
    {
        case SENSOR_IDLE:
            me->next_state = Lighting_LIGHT_POWER_SETTING;
            ret_val = TRAN_STATUS;
        break;

        default:
            led_brightening();
            ret_val = IGNORED_STATUS;
        break; 
    }
    return ret_val;
}