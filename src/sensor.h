#ifndef SENSOR_H
#define SENSOR_H

typedef enum
{
    SENSOR_IDLE,
    SENSOR_LEFT_ACTIVE,
    SENSOR_RIGHT_ACTIVE,
    SENSOR_BOTH_ACTIVE,
}Sensor_State_t;

void Sensor_Init(void);
void Sensor_refresh(void);
Sensor_State_t Sensor_GetState(void);

#endif