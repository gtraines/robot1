//
// Created by graham on 11/18/17.
//
#include <Arduino.h>
#include <Servo.h>
#include <QueueList.h>
#include "InternalOperation.h"
#include "SpeedControlSpeed.h"
#include "SpeedControlCommand.h"
#include "SpeedControl.h"

#define GEAR_FORWARD 1
#define GEAR_REVERSE (-1)

#define OP_ACCELERATE_MIN_MILLIS_BETWEEN_STEPS 100
#define OP_DECELERATE_MIN_MILLIS_BETWEEN_STEPS 200
#define OP_DECELERATE_TO_STOP_MIN_MILLIS 300
#define OP_GEARCHANGE_MIN_MILLIS_BETWEEN_STEPS 200

#define SERVO_HALT 95
#define SERVO_FORWARD_MAX 100
#define SERVO_FORWARD_SURGE 99
#define SERVO_FORWARD_NORMAL 98
#define SERVO_REVERSE_MAX 79
#define SERVO_REVERSE_SURGE 80
#define SERVO_REVERSE_NORMAL 89

SpeedControl::SpeedControl() {}
SpeedControl::~SpeedControl() {}

/* Begin PUBLIC method definitions */
void SpeedControl::attach(Servo& servo, int millisPerTimeStep) {
    _servo = servo;
    _millisPerTimeStep = millisPerTimeStep;
    calculateOperationSteps();
    _currentCommand = SpeedControlCommand(0, 0);
    _targetCommand = SpeedControlCommand(0, 0);
    _operationsQueue = QueueList<InternalOperation*>();
    _debugModeOn = false;
    _currentGear = GEAR_FORWARD;
    _operationStepsCountdown = 0;
}

int SpeedControl::commandMove(SpeedControlCommand command) {
    if (availableToReceiveCommand()) {

        _targetCommand = command;

        // SET OPERATION
        if (commandRequiresDirectionChange(_targetCommand)) {
            pushChangeDirectionOperations(_currentGear * -1);
            if ((int)_targetCommand.speedControlSpeed > 0) {
                pushMoveForwardOperations(SpeedControlSpeed::Stop, _targetCommand.speedControlSpeed);
            }
            if ((int)_targetCommand.speedControlSpeed < 0) {
                pushMoveBackwardOperations(SpeedControlSpeed::Stop, _targetCommand.speedControlSpeed);
            }
        }
        
        else if ((int)_targetCommand.speedControlSpeed > 0) {
            pushMoveForwardOperations(_currentCommand.speedControlSpeed, _targetCommand.speedControlSpeed);
        }
        else if ((int)_targetCommand.speedControlSpeed < 0) {
            pushMoveBackwardOperations(_currentCommand.speedControlSpeed,  _targetCommand.speedControlSpeed);
        }
        else {
            pushHaltMotionOperations();
        }

        _currentCommand = _targetCommand;
    }

    return 1;
}

int SpeedControl::getCurrentControlStatus() {
    return 1;
}

int SpeedControl::getMillisUntilAvailableForCommand() {
    return _operationStepsCountdown * SpeedControl::_millisPerTimeStep;
}

bool SpeedControl::setDebug(bool debugModeOn) {
    _debugModeOn = debugModeOn;
    return _debugModeOn;
}

int SpeedControl::incrementTimeStep() {
    if (_operationStepsCountdown > 0) {
        _operationStepsCountdown--;
    }
    else {
        if (!_operationsQueue.isEmpty()) {
            auto* operationToExecute = _operationsQueue.pop();
            executeOperation(*operationToExecute);
        }
    }
    return getMillisUntilAvailableForCommand();
}
/* End PUBLIC method definitions */

/* Begin PROTECTED method definitions */
bool SpeedControl::availableToReceiveCommand() {
    return _operationStepsCountdown <= 0;
}

void SpeedControl::pushChangeDirectionOperations(int direction) {
    pushHaltMotionOperations();

    if (direction < 0) {
        pushAccelerateBackwardOperations(SpeedControlSpeed::Stop, SpeedControlSpeed::BackwardNormal);
        pushDecelerateBackwardOperations(SpeedControlSpeed::BackwardNormal, SpeedControlSpeed::Stop);
    }
    if (direction > 0) {
        pushAccelerateForwardOperations(SpeedControlSpeed::Stop, SpeedControlSpeed::ForwardNormal);
        pushDecelerateForwardOperations(SpeedControlSpeed::ForwardNormal, SpeedControlSpeed::Stop);
    }

    auto* finalChangeDirectionOperation = new InternalOperation();
    finalChangeDirectionOperation->incrementsToWaitBeforeNextOperation = _timeStepsBetweenGearChangeOperation;
    finalChangeDirectionOperation->operationServoSignal = SERVO_HALT;
    _operationsQueue.push(finalChangeDirectionOperation);

    _currentGear = _currentGear * (-1);
}

void SpeedControl::pushAccelerateBackwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed) {

    // DecrementOverRange
    int fromSignal = getServoSignalForSpeedControlSpeed(fromSpeed);
    int toSignal = getServoSignalForSpeedControlSpeed(toSpeed);

    pushDecrementingSignalOverRangeOperations(fromSignal, toSignal, _timeStepsBetweenAccelerateOperation);
}

void SpeedControl::pushDecelerateBackwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed) {
    // IncrementOverRange
    int fromSignal = getServoSignalForSpeedControlSpeed(fromSpeed);
    int toSignal = getServoSignalForSpeedControlSpeed(toSpeed);

    pushIncrementingSignalOverRangeOperations(fromSignal, toSignal, _timeStepsBetweenDecelerateOperation);
}

void SpeedControl::pushAccelerateForwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed) {
    // Increment Over Range
    int fromSignal = getServoSignalForSpeedControlSpeed(fromSpeed);
    int toSignal = getServoSignalForSpeedControlSpeed(toSpeed);

    pushIncrementingSignalOverRangeOperations(fromSignal, toSignal, _timeStepsBetweenAccelerateOperation);
}

void SpeedControl::pushDecelerateForwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed) {
    // Decrement Over Range
    int fromSignal = getServoSignalForSpeedControlSpeed(fromSpeed);
    int toSignal = getServoSignalForSpeedControlSpeed(toSpeed);

    pushDecrementingSignalOverRangeOperations(fromSignal, toSignal, _timeStepsBetweenDecelerateOperation);
}


void SpeedControl::pushHaltMotionOperations() {
    int currentSignal = getServoSignalForSpeedControlSpeed(_currentCommand.speedControlSpeed);
    int waitTime = _timeStepsBetweenSlowToHaltOperation;

    if ((int)_currentCommand.speedControlSpeed > 0) {
        pushDecrementingSignalOverRangeOperations(currentSignal, SERVO_HALT, waitTime);
    }

    if ((int)_currentCommand.speedControlSpeed < 0) {
        pushIncrementingSignalOverRangeOperations(currentSignal, SERVO_HALT, waitTime);
    }
    
}

void SpeedControl::pushIncrementingSignalOverRangeOperations(int fromSignal, int toSignal, int waitStepsAfterExecutingOperation) {
    for (int signalIncrement = fromSignal; signalIncrement <= toSignal; signalIncrement++) {

        auto* operationToAdd = new InternalOperation();
        operationToAdd->operationServoSignal = signalIncrement;
        operationToAdd->incrementsToWaitBeforeNextOperation = waitStepsAfterExecutingOperation;

        _operationsQueue.push(operationToAdd);
    }
}

void SpeedControl::pushDecrementingSignalOverRangeOperations(int fromSignal, int toSignal, int waitStepsAfterExecutingOperation) {
    for (int signalDecrement = fromSignal; signalDecrement >= toSignal; signalDecrement--) {

        auto* operationToAdd = new InternalOperation();
        operationToAdd->operationServoSignal = signalDecrement;
        operationToAdd->incrementsToWaitBeforeNextOperation = waitStepsAfterExecutingOperation;

        _operationsQueue.push(operationToAdd);
    }
}

int SpeedControl::getServoSignalForSpeedControlSpeed(SpeedControlSpeed speed) {
    switch (speed) {
        case SpeedControlSpeed::Stop:
            return SERVO_HALT;
        case SpeedControlSpeed::BackwardFast:
            return SERVO_REVERSE_MAX;
        case SpeedControlSpeed::BackwardNormal:
            return SERVO_REVERSE_SURGE;
        case SpeedControlSpeed::BackwardSlow:
            return SERVO_REVERSE_NORMAL;
        case SpeedControlSpeed::ForwardSlow:
            return SERVO_FORWARD_NORMAL;
        case SpeedControlSpeed::ForwardNormal:
            return SERVO_FORWARD_SURGE;
        case SpeedControlSpeed::ForwardFast:
            return SERVO_FORWARD_MAX;
        default:
            return SERVO_HALT;
    }
}

void SpeedControl::pushMoveForwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed) {
    if (fromSpeed == SpeedControlSpeed::Stop) {
        pushAccelerateForwardOperations(fromSpeed, SpeedControlSpeed::ForwardFast);
        pushMoveForwardOperations(SpeedControlSpeed::ForwardFast, toSpeed);
    }

    if ((int)fromSpeed > (int)toSpeed) {
        pushDecelerateForwardOperations(fromSpeed, toSpeed);
    }
    if ((int)fromSpeed < (int)toSpeed) {
        pushAccelerateForwardOperations(fromSpeed, toSpeed);
    }
}

void SpeedControl::pushMoveBackwardOperations(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed) {
    if (fromSpeed == SpeedControlSpeed::Stop) {
        pushAccelerateBackwardOperations(fromSpeed, SpeedControlSpeed::BackwardFast);
        pushMoveForwardOperations(SpeedControlSpeed::BackwardFast, toSpeed);
    }

    if ((int)fromSpeed < (int)toSpeed) {
        pushAccelerateBackwardOperations(fromSpeed, toSpeed);
    }
    if ((int)fromSpeed > (int)toSpeed) {
        pushDecelerateForwardOperations(fromSpeed, toSpeed);
    }
}

void SpeedControl::executeOperation(InternalOperation& operationToExecute) {
    _servo.write(operationToExecute.operationServoSignal);
    resetOperationCountdown(operationToExecute.incrementsToWaitBeforeNextOperation);
}

void SpeedControl::resetOperationCountdown(int stepsToCountDownFrom) {
    _operationStepsCountdown = stepsToCountDownFrom;
}

void SpeedControl::calculateOperationSteps() {
    _timeStepsBetweenAccelerateOperation = OP_ACCELERATE_MIN_MILLIS_BETWEEN_STEPS / _millisPerTimeStep;
    _timeStepsBetweenDecelerateOperation = OP_DECELERATE_MIN_MILLIS_BETWEEN_STEPS / _millisPerTimeStep;
    _timeStepsBetweenSlowToHaltOperation = OP_DECELERATE_TO_STOP_MIN_MILLIS / _millisPerTimeStep;
    _timeStepsBetweenGearChangeOperation = OP_GEARCHANGE_MIN_MILLIS_BETWEEN_STEPS / _millisPerTimeStep;
}

bool SpeedControl::commandRequiresDirectionChange(SpeedControlCommand& targetCommand) {
    if (targetCommand.speedControlSpeed > 0 && _currentGear < 0) {
        return true;
    }

    if (targetCommand.speedControlSpeed < 0 && _currentGear > 0) {
        return true;
    }

    return false;
}

/* End PROTECTED method definitions */
