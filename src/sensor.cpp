#include "Arduino.h"
#include "stdint.h"
#include "sensor.h"
#include "lighting_cfg.h"

#define LEFT_SENSOR_POS 0
#define RIGHT_SENSOR_POS 1

typedef struct
{
    uint8_t pin;
    uint16_t last_signal_state;
    uint16_t lastDebounceTime;
    uint16_t debounceDelay;
    uint16_t current_signal_state;

}Sensor_signals_t;

void debounce_signals(uint8_t signal);

Sensor_signals_t sensor_signals[MAX_NUMBER_OF_SIGNALS] = 
{
    {
        .pin = SENSOR_LEFT_PIN,
        .last_signal_state = HIGH,
        .lastDebounceTime = 0,
        .debounceDelay = LEFT_DEBOUNCE_DELAY,
        .current_signal_state = HIGH,
    },
    {
        .pin = SENSOR_RIGHT_PIN,
        .last_signal_state = HIGH,
        .lastDebounceTime = 0,
        .debounceDelay = RIGHT_DEBOUNCE_DELAY,
        .current_signal_state = HIGH,
    },
};

void Sensor_Init(void)
{
    pinMode(SENSOR_LEFT_PIN, INPUT);
    pinMode(SENSOR_RIGHT_PIN, INPUT);
    digitalWrite(SENSOR_LEFT_PIN, HIGH);
    digitalWrite(SENSOR_RIGHT_PIN, HIGH);
}

void Sensor_refresh(void)
{
    debounce_signals(LEFT_SENSOR_POS);
    debounce_signals(RIGHT_SENSOR_POS);
}

Sensor_State_t Sensor_GetState(void)
{
    Sensor_State_t ret_val; 
    if(
        (sensor_signals[LEFT_SENSOR_POS].current_signal_state == HIGH) && 
        (sensor_signals[RIGHT_SENSOR_POS].current_signal_state == LOW) 
    )
    {
        ret_val = SENSOR_RIGHT_ACTIVE;
    }
    else if(
        (sensor_signals[LEFT_SENSOR_POS].current_signal_state == LOW) && 
        (sensor_signals[RIGHT_SENSOR_POS].current_signal_state == HIGH) 
    )
    {
        ret_val = SENSOR_LEFT_ACTIVE;
    }
    else if(
        (sensor_signals[LEFT_SENSOR_POS].current_signal_state == LOW) && 
        (sensor_signals[RIGHT_SENSOR_POS].current_signal_state == LOW) 
    )
    {

        ret_val = SENSOR_BOTH_ACTIVE;
    }
    else
    {
        ret_val = SENSOR_IDLE;
    }
    return ret_val;
}


void debounce_signals(uint8_t signal)
{
  if(signal < MAX_NUMBER_OF_SIGNALS)
  {
    uint8_t reading = digitalRead(sensor_signals[signal].pin);

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != sensor_signals[signal].last_signal_state) {
      // reset the debouncing timer
      sensor_signals[signal].lastDebounceTime = millis();
    }

    if ((millis() - sensor_signals[signal].lastDebounceTime) > sensor_signals[signal].debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading != sensor_signals[signal].current_signal_state) {
        sensor_signals[signal].current_signal_state = reading;
      }
    }
    // save the reading. Next time through the loop, it'll be the lastButtonState:
    sensor_signals[signal].last_signal_state = reading;    
  }
}