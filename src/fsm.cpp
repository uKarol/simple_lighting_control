#include "fsm.h"
#include "led_controller.h"
#include "timer.h"
#include "Arduino.h"

#define MODE_CH_TIMEOUT 1500


LightFSM::LightFSM() : Fsm((State)&LightFSM::Lighting_OFF) 
{

}     

void LightFSM::Lighting_OFF(Event ev)
{
    switch(ev)
    {
        case ENTRY_EVENT:
            Serial.println("LED TURNING OFF");
            led_ctrl.led_off();

        break;

        case (Event)SENSOR_BOTH_ACTIVE:
            TRAN(&LightFSM::Lighting_TURNING);
        break;

        default:
        break; 
    }
}

void LightFSM::Lighting_TURNING(Event ev)
{
    switch(ev)
    {
        case (Event)SENSOR_IDLE:
            TRAN(&LightFSM::Lighting_ON);
        break;

        default:
        break; 
    }
}

void LightFSM::Lighting_ON(Event ev)
{
    switch(ev)
    {
        case ENTRY_EVENT:
            Serial.println("LED TURNING ON");
            led_ctrl.led_on();
        break;

        case (Event)SENSOR_BOTH_ACTIVE:
            TRAN(&LightFSM::Lighting_LIGHT_MODE_CHANGE);
        break;

        default:
        break; 
    }
}

void LightFSM::Lighting_LIGHT_MODE_CHANGE(Event ev)
{
    switch(ev)
    {
        case ENTRY_EVENT:
            Serial.println("MODE CHANGE");
            timer_activate(MODE_CH_TIMEOUT);
        break;
        case (Event)SENSOR_IDLE:
            TRAN(&LightFSM::Lighting_OFF);
        break;

        case EXIT_EVENT:
            timer_deactivate();     
        break;

        case TIMEOUT:
            led_ctrl.led_blink(); 
            TRAN(&LightFSM::Lighting_LIGHT_POWER_SETTING);
        break;

        default:
        break; 
    }
}

void LightFSM::Lighting_LIGHT_POWER_SETTING(Event ev)
{
    switch(ev)
    {
        case ENTRY_EVENT:
            Serial.println("MODE POWER SETTING");
        break;
        case (Event)SENSOR_IDLE:
            timer_activate(MODE_CH_TIMEOUT);
        break;

        case (Event)SENSOR_LEFT_ACTIVE:
            TRAN(&LightFSM::Lighting_LIGHT_BRIGHTENING);
        break;

        case (Event)SENSOR_RIGHT_ACTIVE:
            TRAN(&LightFSM::Lighting_LIGHT_DIMMING);
        break;

        case EXIT_EVENT:
            timer_deactivate();        
        break;

        case TIMEOUT:
            led_ctrl.led_blink();
            TRAN(&LightFSM::Lighting_ON);
        break;

        default:
            timer_deactivate();
        break; 
    }
}

void LightFSM::Lighting_LIGHT_DIMMING(Event ev)
{
    switch(ev)
    {
        case ENTRY_EVENT:
            Serial.println("MODE DIMMING");
        break;
        case (Event)SENSOR_IDLE:
            TRAN(&LightFSM::Lighting_LIGHT_POWER_SETTING);
        break;

        default:
            led_ctrl.led_dimming();
        break; 
    }
}

void LightFSM::Lighting_LIGHT_BRIGHTENING(Event ev)
{

    switch(ev)
    {
        case ENTRY_EVENT:
            Serial.println("MODE BRIGHTENING");
        break;
        case (Event)SENSOR_IDLE:
            TRAN(&LightFSM::Lighting_LIGHT_POWER_SETTING);
        break;

        default:
            led_ctrl.led_brightening();
        break; 
    }
}