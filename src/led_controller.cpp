#include "led_controller.h"
#include "Arduino.h"
#include "math.h"
// #define POWER_LIMIT 100

// PIN6

LedController::LedController()
{
  led_controller_init();
}

void LedController::led_controller_init(void)
{
  led_pin = PIN6;
  led_power = 100;
  power_limit = 100;
  R = (100 * log10(2))/(log10(255));
  pinMode(PIN6, OUTPUT);
}

void LedController::led_on(void)
{
  analogWrite(led_pin, set_duty_cycle(led_power));
 // #if DEBUG_ACTIVE == 1
  Serial.println("power of led");
  Serial.println(led_power);
 // #endif
}

uint8_t LedController::set_duty_cycle(uint8_t power)
{
  uint8_t dc = (uint8_t)(pow(2, (power / R)) - 1);
  return dc;
}

void LedController::led_off(void)
{
  Serial.println("power of led");
  Serial.println(led_power);
  analogWrite(led_pin, 0);
}

void LedController::led_blink(void)
{
  analogWrite(led_pin, 0);
  delay(100);
  analogWrite(led_pin, set_duty_cycle(led_power));
}

void LedController::led_set_power(uint8_t power)
{
  led_power = power;
  analogWrite(led_pin, set_duty_cycle(led_power));
}

void LedController::led_dimming()
{
  if(led_power > 30)
  {
    led_power--;
  }
  #if DEBUG_ACTIVE == 1
  Serial.println(led_power);
  #endif
  analogWrite(led_pin, set_duty_cycle(led_power));
}

void LedController::led_brightening()
{
  if(led_power < power_limit)
  {
    led_power++;
  }
  analogWrite(led_pin, set_duty_cycle(led_power));  
  #if DEBUG_ACTIVE == 1
  Serial.println(led_power);
  #endif
}