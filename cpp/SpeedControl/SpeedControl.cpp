//
// Created by graham on 11/18/17.
//
#include "SpeedControlSpeed.h"
#include "SpeedControlCommand.h"
#include "InternalOperation.h"
#include "SpeedControl.h"
#include "StackArray.h"

#define GEAR_FORWARD 1
#define GEAR_REVERSE -1

#define OP_ACCELERATE_MIN_MILLIS_BETWEEN_STEPS 300
#define OP_DECELERATE_MIN_MILLIS_BETWEEN_STEPS 300
#define OP_DECELERATE_TO_STOP_MIN_MILLIS 300
#define OP_GEARCHANGE_MIN_MILLIS_BETWEEN_STEPS 500

#define STATUS_AVAILABLE_FOR_ORDERS 100
#define STATUS_SUCCESS_COMMAND_RECEIVED 200
#define STATUS_UNAVAILABLE_EXECUTING_DIRECTION_CHANGE 400
#define STATUS_UNAVAILABLE_COMPLYING_LAST 401
#define STATUS_ERROR 500

#define SERVO_SINGLE_STEP_CHANGE_MAX 3

#define SERVO_HALT 95
#define SERVO_FORWARD_STOP 95
#define SERVO_REVERSE_STOP 94

#define SERVO_FORWARD_MAX 100
#define SERVO_FORWARD_SURGE 99
#define SERVO_FORWARD_NORMAL 98
#define SERVO_FORWARD_COAST 97
#define SERVO_FORWARD_PREP 96

#define SERVO_REVERSE_MAX 79
#define SERVO_REVERSE_SURGE 80
#define SERVO_REVERSE_NORMAL 89
#define SERVO_REVERSE_COAST 90
#define SERVO_REVERSE_PREP 94


static int _operation_STEPS_accelerateMinBetweenSteps;
static int _operation_STEPS_decelerateMinBetweenSteps;
static int _operation_STEPS_slowToStopMinBetweenSteps;
static int _operation_STEPS_gearChangeMinBetweenSteps;

/* Begin PUBLIC method definitions */
void SpeedControl::attach(Servo& servo, int millisPerTimeStep) {
    _servo = servo;
    _millisPerTimeStep = millisPerTimeStep;
    
    _operationsStack = new StackArray<InternalOperation>(); 
}

int SpeedControl::commandMove(SpeedControlCommand command) {
    if (availableToReceiveCommand()) {

        _targetCommand = command;
        resetOperationClock();

        // SET OPERATION
        if (commandRequiresDirectionChange(_targetCommand)) {
            pushChangeDirectionOperations(_currentGear * -1);
        }
        
        if (_targetCommand.speedControlSpeed > (SpeedControlSpeed)0) {
            pushMoveForwardOperations(_targetCommand.speedControlSpeed);
        }
        else if (_targetCommand.speedControlSpeed < (SpeedControlSpeed)0) {
            pushMoveBackwardOperations(_targetCommand.speedControlSpeed);
        }
        else {
            pushHaltMotionOperations();
        }
    }

    return 1;
}

int SpeedControl::getCurrentControlStatus() {
    return 1;
}

int SpeedControl::getMillisUntilAvailableForCommand() {
    return _operationStepsCountdown * _incrementMillisPerLoop;
}

bool SpeedControl::setDebug(bool debugModeOn) {
    _debugModeOn = debugModeOn;
    return _debugModeOn;
}

int SpeedControl::incrementStep() {



    if (_operationStepsCountdown > 0) {
        _operationStepsCountdown--;
    }
    else {
        
    }
    return getMillisUntilAvailableForCommand();
}
/* End PUBLIC method definitions */

/* Begin PROTECTED method definitions */
bool SpeedControl::availableToReceiveCommand() {
    return _operationStepsCountdown <= 0;
}

bool SpeedControl::currentlyInStoppedRange() {
    return _current
}

void SpeedControl::pushChangeDirectionOperations(int direction) {
    _operationsQueue.push()

    if (_operationStepsClock == 0 || _operationStepsClock >= _operation_STEPS_gearChangeMinBetweenSteps) {
        if (!_gearChange_STEP1_STOP_COMPLETE) {
            haltMotion();
            _gearChange_STEP1_STOP_COMPLETE = true;
        }
        else if (!_gearChange_STEP2_PREP_COMPLETE) {
            if (direction == GEAR_FORWARD) {
                _servo.write(SERVO_FORWARD_PREP);
            }
            else {
                _servo.write(SERVO_REVERSE_PREP);
            }
            _gearChange_STEP2_PREP_COMPLETE = true;
        }
        else if (!_gearChange_STEP3_SURGE_COMPLETE) {
            if (direction == GEAR_FORWARD) {
                _servo.write(SERVO_FORWARD_SURGE);
            }
            else {
                _servo.write(SERVO_REVERSE_SURGE);
            }
            _gearChange_STEP3_SURGE_COMPLETE = true;
        }
        else if (!_gearChange_STEP4_CLUTCH_COMPLETE) {
            haltMotion();
            _gearChange_STEP4_CLUTCH_COMPLETE = true;
        }
        else {
            _currentGear = direction * -1;
        }
        resetOperationClock();
        return;
    }
}

void SpeedControl::pushHaltMotionOperations() {
    if ((int)_currentCommand.currentCommandSpeed > 0) {

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

void SpeedControl::pushMoveForwardOperations(SpeedControlSpeed speed) {

}

void SpeedControl::pushMoveBackwardOperations(SpeedControlSpeed speed) {
    
}

void SpeedControl::decelerateBackward(SpeedControlSpeed fromSpeed, SpeedControlSpeed toSpeed) {
    for (int spdIncr = _)
}

void SpeedControl::executeOperation(InternalOperation& operationToExecute) {
    _servo.write(operationToExecute.operationServoSignal);
    resetOperationClock(operationToExecute.stepsToCountDownFrom);
}

void SpeedControl::resetOperationCountdown(int stepsToCountDownFrom) {
    _operationStepsCountdown = stepsToCountDownFrom;
}

void SpeedControl::calculateOperationSteps() {
    _operation_STEPS_accelerateMinBetweenSteps = OP_ACCELERATE_MIN_MILLIS_BETWEEN_STEPS / _millisPerTimeStep;
    _operation_STEPS_decelerateMinBetweenSteps = OP_DECELERATE_MIN_MILLIS_BETWEEN_STEPS / _millisPerTimeStep;
    _operation_STEPS_slowToStopMinBetweenSteps = OP_DECELERATE_TO_STOP_MIN_MILLIS / _millisPerTimeStep;
    _operation_STEPS_gearChangeMinBetweenSteps = OP_GEARCHANGE_MIN_MILLIS_BETWEEN_STEPS / _millisPerTimeStep;
}

bool SpeedControl::commandRequiresDirectionChange(SpeedControlCommand& targetCommand) {
    if (targetCommand.speedControlSpeed > 0 && _currentCommand.speedControlSpeed <= 0) {
        return true;
    }

    if (targetCommand.speedControlSpeed < 0 && _currentCommand.speedControlSpeed >= 0) {
        return true;
    }

    return false;
}
/* End PROTECTED method definitions */
