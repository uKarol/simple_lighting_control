#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"

typedef enum{
    TIMER_NOT_ACTIVE,
    TIMER_ACTIVE,
    TIMEOUT_OCCURED,
} timer_event_t;

void timer_activate(uint16_t timeout);
timer_event_t timer_update(uint8_t milisec);
void timer_deactivate();

#endif