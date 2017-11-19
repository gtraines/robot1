//
// Created by graham on 11/18/17.
//

#include "SpeedControl.h"

#define GEAR_FORWARD 1
#define GEAR_REVERSE -1

#define CMD_STOP 0
#define CMD_FORWARD_SLOW 1
#define CMD_FORWARD_NORMAL 2
#define CMD_FORWARD_FAST 3
#define CMD_REVERSE_SLOW -1
#define CMD_REVERSE_NORMAL -2
#define CMD_REVERSE_FAST -3

#define OP_TIME_MIN_DECELERATE_TO_STOP 1000
#define OP_TIME_MIN_GEAR_CHANGE_TOTAL 2000


#define OP_NO_OP 0
#define OP_ACCELERATE_FORWARD 51
#define OP_ACCELERATE_REVERSE 52
#define OP_DECELERATE_FORWARD 101
#define OP_DECELERATE_REVERSE 102
#define OP_HALT_MOTION 200
#define OP_CHANGE_DIRECTION 400

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


Servo _servo;

int _targetCommandVector;
int _currentCommandVector;
int _currentServoSignal;
int _currentGear;
bool _availableForCommand;

static int _operationStepsClock;
static int _updateStepSize;
static int _currentOperation;

static int STEPS_accelerateMinBetweenServoSteps;
static int STEPS_decelerateMinBetweenServoSteps;
static int STEPS_slowToStopMinBetweenServoSteps;
static int STEPS_gearChangeMinBetweenSteps;

int _gearChange_STEP1_STOP_COMPLETE;
int _gearChange_STEP2_PREP_COMPLETE;
int _gearChange_STEP3_SURGE_COMPLETE;
int _gearChange_STEP4_CLUTCH_COMPLETE;

int _statusVector = 0x0;

/* Begin PUBLIC method definitions */
void SpeedControl::attach(Servo servo, int updateStepSize) {
    _servo = servo;
    _updateStepSize = updateStepSize;
    _currentCommandVector = 0;

}

int SpeedControl::commandMove(int commandVector) {
    if (availableToReceiveCommand() && commandVector != _currentCommandVector) {

        _targetCommandVector = constrain(commandVector, CMD_REVERSE_FAST, CMD_FORWARD_FAST);
        _operationStepsClock = 0;

        // SET OPERATION
        if (commandRequiresDirectionChange(_targetCommandVector)) {
            _currentOperation = OP_CHANGE_DIRECTION;
        }
        else if (_targetCommandVector > _currentCommandVector && _currentCommandVector > 0) {
            _currentOperation = OP_ACCELERATE_FORWARD;
        }
        else if (_targetCommandVector < _currentCommandVector && _targetCommandVector > 0) {
            _currentOperation = OP_DECELERATE_FORWARD;
        }
        else if (_targetCommandVector < _currentCommandVector && _currentCommandVector < 0) {
            _currentOperation = OP_ACCELERATE_REVERSE;
        }
        else if (_targetCommandVector > _currentCommandVector && _targetCommandVector < 0) {
            _currentOperation = OP_DECELERATE_REVERSE;
        }
        else {
            _currentOperation = OP_HALT_MOTION;
        }
    }

    return _currentOperation;
}

int SpeedControl::getCurrentControlStatus() {
    if (_currentOperation == OP_CHANGE_DIRECTION) {
        return STATUS_UNAVAILABLE_EXECUTING_DIRECTION_CHANGE;
    }

    if (_currentOperation == OP_DECELERATE || _currentOperation == OP_HALT_MOTION) {
        return STATUS_UNAVAILABLE_COMPLYING_LAST;
    }

    return STATUS_AVAILABLE_FOR_ORDERS;

}

int SpeedControl::getMillisUntilAvailableForCommand() {

}

bool SpeedControl::setDebug(bool debugModeOn) {

}
void SpeedControl::incrementStep() {

}
/* End PUBLIC method definitions */

/* Begin PROTECTED method definitions */
bool SpeedControl::availableToReceiveCommand() {
    if (_currentOperation == OP_NO_OP) {
        return true;
    }

    return false;
}
bool SpeedControl::currentlyInStoppedRange() {

}

void SpeedControl::changeGearDirection(int direction) {
    if (_operationStepsClock == 0 || _operationStepsClock >= STEPS_gearChangeMinBetweenSteps) {
        if (!_gearChange_STEP1_STOP_COMPLETE) {
            return;
        }
        if (!_gearChange_STEP2_PREP_COMPLETE) {

            return;
        }
        if (!_gearChange_STEP3_SURGE_COMPLETE) {

            return;
        }
        if (!_gearChange_STEP4_CLUTCH_COMPLETE) {

            return;
        }
    }
}

void SpeedControl::moveForward(int speed) {

}

void SpeedControl::accelerateForward(int speed) {

}

void SpeedControl::decelerateForward(int speed) {

}

void SpeedControl::resetOperationClock() {

}

void SpeedControl::calculateOperationSteps() {

}

bool SpeedControl::commandRequiresDirectionChange(int commandVector) {
    if (commandVector > 0 && _currentTargetVector <= 0) {
        return true;
    }

    if (commandVector < 0 && _currentTargetVector >= 0) {
        return true;
    }

    return false;
}
/* End PROTECTED method definitions */