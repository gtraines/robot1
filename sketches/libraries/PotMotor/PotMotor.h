#ifndef ROBOT1_POTMOTOR_H
#define ROBOT1_POTMOTOR_H

#include <Arduino.h>

struct PotMotorConfig {
    int MotorEnablePin;
    int IncreaseHighPin;
    int DecreaseHighPin;
    int PotentiometerReadingPin;
    int MinPotReadingLimit;
    int MaxPotReadingLimit;
    int ReadingGranularity;
    int MinSpeed;
    int MaxSpeed;
    int MediumSpeed;
    int JerkSpeed;
    int ReadingDelay;
};

enum class MotorDirection {
  INCREASE,
  DECREASE
};

class PotMotor {
    private:
        int _enablePin;
        int _increaseHighPin;
        int _decreaseHighPin;
        int _potReadingPin;
        int _minPositionReading;
        int _maxPositionReading;
        int _readingGranularityDelta;
        int _lastPosition = 0;
        int _motorMinSpeed;
        int _motorMaxSpeed;
        int _motorMedSpeed;
        int _motorJerkSpeed;
        int _readingDelay = 60;

public:
        explicit PotMotor(const PotMotorConfig& motorInstanceConfig);
        PotMotor(int enablePin, 
            int increaseHighPin, 
            int decreaseHighPin,
            int potReadingPin, 
            int minPositionReading, 
            int maxPositionReading, 
            int readingGranularityDelta,
            int motorMinSpeed,
            int motorMaxSpeed,
            int motorMedSpeed,
            int motorJerkSpeed) {
                _enablePin = enablePin;
                _increaseHighPin = increaseHighPin;
                _decreaseHighPin = decreaseHighPin;
                _potReadingPin = potReadingPin;
                _minPositionReading = minPositionReading;
                _maxPositionReading = maxPositionReading;
                _readingGranularityDelta = readingGranularityDelta;
                _motorMinSpeed = motorMinSpeed;
                _motorMaxSpeed = motorMaxSpeed;
                _motorMedSpeed = motorMedSpeed;
                _motorJerkSpeed = motorJerkSpeed;
            }
        ~PotMotor() { }
        int moveTo(int targetPosition);
        virtual void indicateError();
        virtual void indicateIncrease();
        virtual void indicateDecrease();
        virtual void motorStop();
        int getCurrentPosition();
        int getPositionTargetDeltaInSlices(int targetPosition);
        void setReadingDelay(int delayMilliseconds);
        int getMotorSpeed(int targetPosition, int lastPosition);
        boolean canMoveToPosition(int targetPosition);
        void setMotorDirection(int motorDirection);
        boolean shouldContinueMoving(int motorDirection, int targetPosition, int currentPosition);
        boolean shouldIncreasePosition(int targetPosition, int currentPosition);
        boolean shouldDecreasePosition(int targetPosition, int currentPosition);
};

#endif // ROBOT1_POTMOTOR_H
