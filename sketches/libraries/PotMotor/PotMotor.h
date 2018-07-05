#ifndef ROBOT1_POTMOTOR_H
#define ROBOT1_POTMOTOR_H

enum class MotorDirection {
  INCREASE,
  DECREASE
};

class PotMotor {
    private:
        unsigned int _enablePin;
        unsigned int _increaseHighPin;
        unsigned int _decreaseHighPin;
        unsigned int _minPositionReading;
        unsigned int _maxPositionReading;
        unsigned int _readingGranularityDelta;
        unsigned int _lastPosition = 0;
        unsigned int _motorMinSpeed;
        unsigned int _motorMaxSpeed;
        unsigned int _motorMedSpeed;
        unsigned int _motorJerkSpeed;
    protected:
        void setMotorDirection(int motorDirection);
        boolean shouldIncreasePosition(unsigned int targetPosition, unsigned int currentPosition);
        boolean shouldDecreasePosition(unsigned int targetPosition, unsigned int currentPosition);
    public:
        PotMotor(unsigned int enablePin, 
            unsigned int increaseHighPin, 
            unsigned int decreaseHighPin, 
            unsigned int minPositionReading, 
            unsigned int maxPositionReading, 
            unsigned int readingGranularityDelta,
            unsigned int motorMinSpeed,
            unsigned int motorMaxSpeed,
            unsigned int motorMedSpeed,
            unsigned int motorJerkSpeed) {
                _enablePin = enablePin;
                _increaseHighPin = increaseHighPin;
                _decreaseHighPin = decreaseHighPin;
                _minPositionReading = minPositionReading;
                _maxPositionReading = maxPositionReading;
                _readingGranularityDelta = readingGranularityDelta;
                _motorMinSpeed = motorMinSpeed;
                _motorMaxSpeed = motorMaxSpeed;
                _motorMedSpeed = motorMedSpeed;
                _motorJerkSpeed = motorJerkSpeed;
            }
        ~PotMotor() { }
        int moveTo(unsigned int targetPosition);
        virtual void indicateError();
        virtual void indicateIncrease();
        virtual void indicateDecrease();
        virtual void motorStop();
        int getCurrentPosition();
        unsigned int getPositionTargetDeltaInSlices(unsigned int targetPosition);
        unsigned int getMotorSpeed(unsigned int targetPosition, unsigned int lastPosition);
        bool canMoveToPosition(unsigned int targetPosition);
};

#endif // ROBOT1_POTMOTOR_H
