
#include "PotMotor.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Taskr.h>
#include <Indicator.h>


int PotMotor::moveTo(int targetPosition)
{
    motorStop();
    
    int currentPosition = getCurrentPosition();
    int currentDirection;

    if (canMoveToPosition(targetPosition)) {
        if (targetPosition > currentPosition) {
            currentDirection = (int)MotorDirection::INCREASE;
        } else {
            currentDirection = (int)MotorDirection::DECREASE;
        }
        analogWrite(_enablePin, _motorJerkSpeed);
        setMotorDirection(currentDirection);
  
        int currentMotorSpeed = _motorJerkSpeed;
        int motorSpeedUpdated = currentMotorSpeed;
        
        while (shouldContinueMoving(currentDirection, targetPosition, currentPosition) 
            && getPositionTargetDeltaInSlices(targetPosition) > 1) {
            Taskr::delayMs(_readingDelay);
    
            motorSpeedUpdated = getMotorSpeed(targetPosition, currentPosition);
            if (motorSpeedUpdated != currentMotorSpeed) {
                analogWrite(_enablePin, motorSpeedUpdated);
                currentMotorSpeed = motorSpeedUpdated;
            }
    
            currentPosition = getCurrentPosition();    
        }
  
        motorStop();
        if (getPositionTargetDeltaInSlices(targetPosition) > 1) {
            moveTo(targetPosition);
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

void PotMotor::setReadingDelay(int delayMilliseconds) {
    _readingDelay = delayMilliseconds;
}

boolean PotMotor::shouldContinueMoving(int motorDirection, int targetPosition, int currentPosition) {
    if (motorDirection == (int)MotorDirection::INCREASE) {
        return shouldIncreasePosition(targetPosition, currentPosition);
    }
    if (motorDirection == (int)MotorDirection::DECREASE) {
        return shouldDecreasePosition(targetPosition, currentPosition);
    }
    return false;
}

boolean PotMotor::shouldIncreasePosition(int targetPosition, int currentPosition) {
  return targetPosition > currentPosition;
}

boolean PotMotor::shouldDecreasePosition(int targetPosition, int currentPosition) {
  return targetPosition < currentPosition;
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

int PotMotor::getCurrentPosition() {
    return (int)analogRead(_potReadingPin);
}

bool PotMotor::canMoveToPosition(int targetPosition) {
    return targetPosition >= _minPositionReading && targetPosition <= _maxPositionReading 
        && (getPositionTargetDeltaInSlices(targetPosition) > 1);    
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
PotMotor::PotMotor(const PotMotorConfig& motorInstanceConfig) {
    this->_enablePin = motorInstanceConfig.MotorEnablePin;
    this->_increaseHighPin = motorInstanceConfig.IncreaseHighPin;
    this->_decreaseHighPin = motorInstanceConfig.DecreaseHighPin;
    this->_potReadingPin = motorInstanceConfig.PotentiometerReadingPin;
    this->_minPositionReading = motorInstanceConfig.MinPotReadingLimit;
    this->_maxPositionReading = motorInstanceConfig.MaxPotReadingLimit;
    this->_readingGranularityDelta = motorInstanceConfig.ReadingGranularity;
    this->_motorMinSpeed = motorInstanceConfig.MinSpeed;
    this->_motorMaxSpeed = motorInstanceConfig.MaxSpeed;
    this->_motorMedSpeed = motorInstanceConfig.MediumSpeed;
    this->_motorJerkSpeed = motorInstanceConfig.JerkSpeed;
}
