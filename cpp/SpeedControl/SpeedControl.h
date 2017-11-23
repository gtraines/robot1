//
// Created by graham on 11/18/17.
//

#ifndef SPEEDCONTROL_SPEEDCONTROL_H
#define SPEEDCONTROL_SPEEDCONTROL_H

#include <Arduino.h>
#include <Servo.h>
#include "SpeedControlOperation.h"
#include "InternalOperation.h"
#include "SpeedControlCommand.h"
#include "SpeedControlSpeed.h"
#include "StackArray.h"

class SpeedControl {
protected:
    void changeGearDirection(int direction);
    bool commandRequiresDirectionChange(SpeedControlCommand& targetCommand);
    void pushChangeDirectionOperations(int direction);
    bool availableToReceiveCommand();
    bool currentlyInStoppedRange();
    void moveForward(int speed);
    void moveBackward(int speed);
    void haltMotion();

    void accelerateForward(int speed);
    void decelerateForward(int speed);
    void accelerateBackward(int speed);
    void decelerateBackward(int speed);
    void resetOperationCountdown(int stepsToCountDownFrom);
    void calculateOperationSteps();

public:
    void attach(Servo& servo, int updateStepSize);
    
    int commandMove(SpeedControlCommand command);
    int getCurrentControlStatus();
    int getMillisUntilAvailableForCommand();
    bool setDebug(bool debugModeOn);
    int incrementStep();

private:
    StackArray<InternalOperation> _operationsStack;
    Servo _servo;
    SpeedControlCommand _targetCommand;
    SpeedControlCommand _currentCommand;
    int _currentServoSignal;
    int _currentGear;
    bool _availableForCommand;
    bool _debugModeOn;
    
    int _operationStepsCountdown;
    int _incrementMillisPerLoop;
};

#endif //SPEEDCONTROL_SPEEDCONTROL_H
