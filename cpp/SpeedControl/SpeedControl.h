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

class SpeedControl {
protected:
    bool commandRequiresDirectionChange(SpeedControlCommand& targetCommand);
    bool availableToReceiveCommand();
    bool currentlyInStoppedRange();
    int getServoSignalForSpeedControlSpeed(SpeedControlSpeed speed);
    
    void pushChangeDirectionOperations(int direction);
    void pushHaltMotionOperations();
    void pushMoveForwardOperations(int speed);
    void pushMoveBackwardOperations(int speed);
    

    void accelerateForward(int speed);
    void decelerateForward(int speed);
    void accelerateBackward(int speed);
    void decelerateBackward(int speed);
    void resetOperationCountdown(int stepsToCountDownFrom);
    void calculateOperationSteps();

public:
    void attach(Servo& servo, int millisPerTimeStep);
    
    int commandMove(SpeedControlCommand command);
    int getCurrentControlStatus();
    int getMillisUntilAvailableForCommand();
    bool setDebug(bool debugModeOn);
    int incrementTimeStep();

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
    int _millisPerTimeStep;
};

#endif //SPEEDCONTROL_SPEEDCONTROL_H
