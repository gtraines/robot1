#include <Arduino.h>
#include "PotMotor.h"
#include "Indicator.h"

int PotMotor::moveTo(int targetPosition)
{
    motorStop();
    
    int elev = getCurrentPosition();
    int currentDirection;

    if (canMoveToPosition(targetPosition)) {
      if (targetPosition > elev) {
        currentDirection = (int)MotorDirection::INCREASE;
      } else {
        currentDirection = (int)MotorDirection::DECREASE;
      }
        return 0;

    } else {
      return -1;
    }
    
}

void PotMotor::motorStop() {
    digitalWrite(_increaseHighPin, LOW);
    digitalWrite(_decreaseHighPin, LOW);
}

void PotMotor::setMotorDirection(int motorDirection) {
    if (motorDirection == (int)MotorDirection::INCREASE) {
        digitalWrite(_increaseHighPin, HIGH);
        digitalWrite(_decreaseHighPin, LOW);
    } 
    if (motorDirection == (int)MotorDirection::DECREASE) {
        digitalWrite(_increaseHighPin, LOW);
        digitalWrite(_decreaseHighPin, HIGH);
    }
}
boolean shouldIncreasePosition(int targetPosition, int currentPosition) {
  bool shouldIncrease = targetPosition > currentPosition;

  return shouldIncrease;
}

boolean shouldDecreasePosition(int targetPosition, int currentPosition) {
  bool shouldDecrease = targetPosition < currentPosition;

  return shouldDecrease;
}

void PotMotor::indicateError()
{

}

void PotMotor::indicateIncrease()
{

}

void PotMotor::indicateDecrease()
{

}

void PotMotor::indicateStop() 
{

}

bool PotMotor::canMoveToPosition(int targetPosition) {
    return targetPosition >= _minPositionReading && targetPosition <= _maxPositionReading;    
}

int PotMotor::getPositionTargetDeltaInSlices(int targetPosition)  {
    int deltaAnalog = abs(targetPosition - getCurrentPosition());

    return deltaAnalog/_readingGranularityDelta;
}

int PotMotor::getMotorSpeed(int targetPosition, int lastPosition) {
    int deltaSlices = getPositionTargetDeltaInSlices(targetPosition);
    if (deltaSlices > 25 || (abs(getCurrentPosition() - lastPosition) < _readingGranularityDelta)) {
        return _motorJerkSpeed;
    } else if (deltaSlices > 15) {
        return _motorMaxSpeed;
    } else if (deltaSlices > 5) {
        return _motorMedSpeed;
    } else {
        return _motorMinSpeed;
    }
}