#ifndef ROBOT1__POT_MOTOR_RTOS__H
#define ROBOT1__POT_MOTOR_RTOS__H

#include <Arduino.h>

typedef struct POT_MOTOR_CFG {
    uint8_t MotorEnablePin;
    uint8_t IncreaseHighPin;
    uint8_t DecreaseHighPin;
    uint8_t PotentiometerReadingPin;
    int MinPotReadingLimit;
    int MaxPotReadingLimit;
    int ReadingGranularity;
    int MinSpeed;
    int MaxSpeed;
    int MediumSpeed;
    int JerkSpeed;
} PotMotorConfig;

enum class MotorDirection {
  INCREASE,
  DECREASE,
  NEUTRAL
};

enum class MotorSpeed {
    SLOW,
    MEDIUM,
    FAST,
    JERK,
    STOP
};

class PotMotorRtos {
private:
    uint8_t _enablePin;
    uint8_t _increaseHighPin;
    uint8_t _decreaseHighPin;
    uint8_t _potReadingPin;
    int _minPositionReading;
    int _maxPositionReading;
    int _readingGranularityDelta;
    int _lastPosition = 0;
    int _motorMinSpeed;
    int _motorMaxSpeed;
    int _motorMedSpeed;
    int _motorJerkSpeed;
protected:

    int getPositionTargetDeltaInSlices(int targetPosition);
    MotorSpeed getAdjustedMotorSpeed();
        
    void setMotorDirection(MotorDirection motorDirection);
    void setMotorSpeed(MotorSpeed motorSpeed);
    int getMotorSpeedValueFromMotorSpeed(MotorSpeed motorSpeed);
    MotorDirection getMotorDirectionToTarget();
    boolean canMoveToPosition(int targetPosition);
    boolean shouldContinueMoving();
    boolean shouldIncreasePosition(int targetPosition, int currentPosition);
    boolean shouldDecreasePosition(int targetPosition, int currentPosition);

public:
    explicit PotMotorRtos(const PotMotorConfig& motorInstanceConfig);
    PotMotorRtos(uint8_t enablePin,
                 uint8_t increaseHighPin,
                 uint8_t decreaseHighPin,
                 uint8_t potReadingPin,
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
            this->currentDirection = MotorDirection::NEUTRAL;
            this->adjustedSpeed = MotorSpeed::STOP;
    }
    ~PotMotorRtos() { }
    MotorDirection currentDirection = MotorDirection::NEUTRAL;
    MotorSpeed commandedSpeed = MotorSpeed::STOP;
    MotorSpeed adjustedSpeed = MotorSpeed::STOP;
    int targetPosition = 0;
    boolean setTargetCommand(int targetPosition, int speed);
    boolean nextStep();
    void motorStop();
    int getCurrentPosition();
};

#endif // ROBOT1__POT_MOTOR_RTOS__H
