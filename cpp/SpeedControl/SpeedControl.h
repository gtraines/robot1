//
// Created by graham on 11/18/17.
//

#ifndef SPEEDCONTROL_SPEEDCONTROL_H
#define SPEEDCONTROL_SPEEDCONTROL_H

#include <Arduino.h>
#include <Servo.h>
#include <QueueList.h>
#include "SpeedControlOperation.h"
#include "InternalOperation.h"
#include "SpeedControlCommand.h"
#include "SpeedControlSpeed.h"

class SpeedControl {

public:
    SpeedControl();
    ~SpeedControl();
    void attach(Servo& servo, int millisPerTimeStep);
    bool availableToReceiveCommand();
    int commandMove(SpeedControlCommand command);
    int getCurrentControlStatus();
    int getMillisUntilAvailableForCommand();
    bool setDebug(bool debugModeOn);
    int incrementTimeStep();

protected:
    bool commandRequiresDirectionChange(SpeedControlCommand& targetCommand);
    
    void executeOperation(InternalOperation& operationToExecute);
    int getServoSignalForSpeedControlSpeed(SpeedControlSpeed speed);

    void pushChangeDirectionOperations(int direction);
    void pushIncrementingSignalOverRangeOperations(int fromSignal, int toSignal, int waitStepsAfterExecutingOperation);
    void pushDecrementingSignalOverRangeOperations(int fromSignal, int toSignal, int waitStepsAfterExecutingOperation);
    void pushHaltMotionOperations();
    void pushMoveForwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed);
    void pushMoveBackwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed);

    void pushAccelerateForwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed);
    void pushDecelerateForwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed);
    void pushAccelerateBackwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed);
    void pushDecelerateBackwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed);
    void resetOperationCountdown(int stepsToCountDownFrom);
    void calculateOperationSteps();

private:
    QueueList<InternalOperation*> _operationsQueue;
    Servo _servo;
    SpeedControlCommand _targetCommand;
    SpeedControlCommand _currentCommand;
    int _currentGear;
    bool _debugModeOn;
    int _timeStepsBetweenAccelerateOperation;
    int _timeStepsBetweenDecelerateOperation;
    int _timeStepsBetweenSlowToHaltOperation;
    int _timeStepsBetweenGearChangeOperation;
    int _operationStepsCountdown;
    int _millisPerTimeStep;
};

#endif //SPEEDCONTROL_SPEEDCONTROL_H
