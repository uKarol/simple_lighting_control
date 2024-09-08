#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "stdint.h"

class LedController
{
    private:
        uint8_t led_power;
        float R;
        uint8_t power_limit; 
        uint8_t led_pin;
        void led_controller_init(void);
        uint8_t set_duty_cycle(uint8_t power);
    public:
    LedController();
    void led_on(void);
    void led_off(void);
    void led_blink(void);
    void led_set_power(uint8_t power);
    void led_brightening();
    void led_dimming();
};

#endif