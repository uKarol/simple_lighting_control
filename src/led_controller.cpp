#include "led_controller.h"
#include "Arduino.h"
#include "math.h"
#define POWER_LIMIT 100

uint8_t led_power = 100;

float R; 

uint8_t set_duty_cycle(uint8_t power);


void led_controller_init(void)
{
    R = (100 * log10(2))/(log10(255));
    pinMode(PIN6, OUTPUT);
}

void led_on(void)
{
  analogWrite(PIN6, set_duty_cycle(led_power));
  Serial.println(led_power);
}

uint8_t set_duty_cycle(uint8_t power)
{
  uint8_t dc = (uint8_t)(pow(2, (power / R)) - 1);
  return dc;
}

void led_off(void)
{
  analogWrite(PIN6, 0);
}

void led_blink(void)
{
  analogWrite(PIN6, 0);
  delay(100);
  analogWrite(PIN6, set_duty_cycle(led_power));
}

void led_set_power(uint8_t power)
{
  led_power = power;
  analogWrite(PIN6, set_duty_cycle(led_power));
}

void led_dimming()
{
  if(led_power > 30)
  {
    led_power--;
  }
  //Serial.println(led_power);
  analogWrite(PIN6, set_duty_cycle(led_power));
}

void led_brightening()
{
  if(led_power < POWER_LIMIT)
  {
    led_power++;
  }
  analogWrite(PIN6, set_duty_cycle(led_power));
 // Serial.println(led_power);
}