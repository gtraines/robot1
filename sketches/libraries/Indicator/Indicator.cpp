#include <Indicator.h>
#include <Arduino.h>

void Indicator::momentaryLedOn(int pinNumber)
{
  turnOnLed(pinNumber);
  delay(500);
  turnOffLed(pinNumber);
}

void Indicator::strobeLed(int pinNumber, int numberTimes) 
{
  int iter = 0;
  for (iter = 0; iter < numberTimes; iter++) {
    turnOnLed(pinNumber);
    delay(50);
    turnOffLed(pinNumber);
    delay(50);
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