#include <Arduino.h>
#include <Indicator.h>
#include <IndicatorConfig.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>

void Indicator::momentaryLedOn(int pinNumber)
{
  turnOnLed(pinNumber);
  vTaskDelay(MOMENTARY_LED_DELAY / portTICK_PERIOD_MS );
  turnOffLed(pinNumber);
}

void Indicator::strobeLed(int pinNumber, int numberTimes) 
{
  int iter = 0;
  for (iter = 0; iter < numberTimes; iter++) {
    turnOnLed(pinNumber);
    vTaskDelay(STROBE_LED_DELAY / portTICK_PERIOD_MS);
    turnOffLed(pinNumber);
    vTaskDelay(STROBE_LED_DELAY / portTICK_PERIOD_MS);
  }
}

void Indicator::turnOnLed(int pinNumber)
{
  digitalWrite(pinNumber, LOW);
}

void Indicator::turnOffLed(int pinNumber)
{
  digitalWrite(pinNumber, HIGH);
}