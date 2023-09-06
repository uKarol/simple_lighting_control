#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "stdint.h"

void led_on(void);
void led_off(void);
void led_blink(void);
void led_set_power(uint8_t power);
void led_brightening();
void led_dimming();
void led_controller_init(void);
#endif