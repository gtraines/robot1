#include "Indicator.h"
#include "IndicatorConfig.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>

void Indicator::turnOnLed(int pinNumber) {
  digitalWrite(pinNumber, LOW);
}

void Indicator::turnOffLed(int pinNumber) {
  digitalWrite(pinNumber, HIGH);
}

void Indicator::momentaryLedOn(int pinNumber, int delay) {
    turnOnLed(pinNumber);
    vTaskDelay(delay / portTICK_PERIOD_MS );
    turnOffLed(pinNumber);
}

void Indicator::momentaryLedOn(int pinNumber) {
    turnOnLed(pinNumber);
    vTaskDelay(BLINK_MED_DELAY / portTICK_PERIOD_MS );
    turnOffLed(pinNumber);
}

void Indicator::alertBlink(int pinNumber) {
  Indicator::strobeLed(pinNumber, BLINK_MED_DELAY, ALERT_BLINK_TIMES);
}

void Indicator::alertBlinkFast(int pinNumber) {
    Indicator::strobeLed(pinNumber, BLINK_FAST_DELAY, ALERT_BLINK_TIMES);
}

void Indicator::alertBlinkSlow(int pinNumber) {
    Indicator::strobeLed(pinNumber, BLINK_SLOW_DELAY, ALERT_BLINK_TIMES);
}

void Indicator::strobeLed(int pinNumber, int delay, int numberTimes) {
  int iter = 0;
  for (iter = 0; iter < numberTimes; iter++) {
    turnOnLed(pinNumber);
    vTaskDelay(delay / portTICK_PERIOD_MS);
    turnOffLed(pinNumber);
    vTaskDelay(delay / portTICK_PERIOD_MS);
  }
}

void Indicator::strobeFast(int pinNumber, int numberTimes) {
    Indicator::strobeLed(pinNumber, STROBE_FAST_DELAY, numberTimes);
}

void Indicator::strobeMedium(int pinNumber, int numberTimes) {
    Indicator::strobeLed(pinNumber, STROBE_MED_DELAY, numberTimes);
}

void Indicator::strobeSlow(int pinNumber, int numberTimes) {
    Indicator::strobeLed(pinNumber, STROBE_SLOW_DELAY, numberTimes);
}

void Indicator::alertStrobe(int pinNumber) {
    Indicator::strobeMedium(pinNumber, ALERT_BLINK_TIMES);
}

void Indicator::alertStrobeSlow(int pinNumber) {
    Indicator::strobeSlow(pinNumber, ALERT_BLINK_TIMES);
}

void Indicator::alertStrobeFast(int pinNumber) {
    Indicator::strobeFast(pinNumber, ALERT_BLINK_TIMES);
}
