//
// Created by graham on 10/7/18.
//
#include "TraverseController.h"
#include <Arduino.h>
#include <Servo.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Taskr.h>
#include <Indicator.h>
#include <TurretPins.h>
#include <TraverseConfig.h>
#include <TraverseCommand.h>
#include <TraverseState.h>
#include <TurretState.h>

Servo* TraverseController::_traverseServo = nullptr;
TaskHandle_t TraverseController::traverseTaskHandle = nullptr;

void TraverseController::initialize(Servo* traverseServo) {

    TraverseController::_traverseServo = traverseServo;

    TurretState::traverseState = new TraverseState_t();
    TurretState::traverseState->isMoving = false;
    TurretState::traverseState->speed = TraverseSpeed::STOP;
    TurretState::traverseState->currentPositionIntRads = 0;
    TurretState::traverseState->targetPositionIntRads = 0;

    TurretState::traverseCommand = new TraverseCommand_t{};
    TurretState::traverseCommand->targetIntRads = 0;
    TurretState::traverseCommand->commandSpeed = TraverseSpeed::STOP;

    setConditionNeutral();

    BaseType_t trvStatus = xTaskCreate(
            TraverseController::dutyCycle,
            (const portCHAR *) "TraverseControllerTask",
            256,  // Stack size
            NULL,
            2,  // Priority
            &TraverseController::traverseTaskHandle);
}

void TraverseController::functionCheckDemo(void* pvParameters) {

    TraverseController::functionCheckSpeedDemo();
    TurretState::traverseState->speed = TraverseSpeed::FAST;
    TraverseController::functionCheckSpeedDemo();
    TurretState::traverseState->speed = TraverseSpeed::SLOW;
    TraverseController::functionCheckSpeedDemo();

}

bool TraverseController::moveToIntRads(int intRads, int delayMillis) {

    int servoDegs = map(intRads, 
        TRAVERSE_MIN_INTRADS,
        TRAVERSE_MAX_INTRADS,
        TRAVERSE_MIN,
        TRAVERSE_MAX);
        
    bool moveResult = TraverseController::moveTo(servoDegs, delayMillis);
    return moveResult;
}

bool TraverseController::moveToIntRads(int intRads) {
    return TraverseController::moveToIntRads(intRads, 0);
}

void TraverseController::dutyCycle(void* pvParameters) {
    int receivedValue = 0;
    bool isMoving = false;
    int targetIntRads = getTargetIntRads();
    int nextStep = 0;
    bool success = true;
    while (success) {
        receivedValue = ulTaskNotifyTake(pdTRUE, getTakeDelay());
        
        if (receivedValue != 0) {
            setTraverseStateFromCommand();
            targetIntRads = getTargetIntRads();
            receivedValue = 0;
        }
        
        if (targetIntRads > 0 && targetIntRads != TraverseController::getCurrentIntRads()) {
            nextStep = TraverseController::getNextMoveToIntRads(targetIntRads, getStepSize());
                
            isMoving = TraverseController::moveToIntRads(nextStep);
        }
        else {
            isMoving = false;
        }

        updateTurretState(nextStep, isMoving);
    }
}

int TraverseController::getNextMoveToIntRads(int targetIntRads, int stepSize) {
    int nextStepIntRads;
    int currentPosition = TraverseController::getCurrentIntRads();

    if (abs(targetIntRads - currentPosition) < stepSize) {
        stepSize = abs(targetIntRads - currentPosition);
    }

    if (targetIntRads > currentPosition) {
        nextStepIntRads = currentPosition + stepSize;
    }
    else {
        nextStepIntRads = currentPosition - stepSize;
    }

    return nextStepIntRads;
}

bool TraverseController::canMoveTo(int targetIntRads) {
    return (targetIntRads >= TRAVERSE_MIN_INTRADS && targetIntRads <= TRAVERSE_MAX_INTRADS);
}

bool TraverseController::moveTo(int targetPosition, int delayMillis) {

    if (targetPosition < TRAVERSE_MIN) {
        Indicator::turnOnLed(MOVE_LED_RED);
        targetPosition = TRAVERSE_MIN;
    }

    if (targetPosition > TRAVERSE_MAX) {
        Indicator::turnOnLed(MOVE_LED_RED);
        targetPosition = TRAVERSE_MAX;
    }

    TraverseController::_traverseServo->write(targetPosition);
    if (delayMillis > 0) {
      Taskr::delayMs(delayMillis);  
    }

    return true;
}

bool TraverseController::setConditionNeutral(){
    Indicator::turnOnLed(MOVE_LED_BLUE);
    TraverseController::_traverseServo->write(TRAVERSE_NEUTRAL);
    updateTurretState(TRAVERSE_NEUTRAL_INTRADS, false);
    TraverseController::clearIndicators();

    return true;
}

void TraverseController::clearIndicators() {
    Indicator::turnOffLed(MOVE_LED_BLUE);
}

bool TraverseController::functionCheckSpeedDemo() {

    TurretState::traverseState->targetPositionIntRads = TRAVERSE_MIN_INTRADS;
    functionCheckMoveToTarget();

    TurretState::traverseState->targetPositionIntRads = TRAVERSE_MAX_INTRADS;
    functionCheckMoveToTarget();

    TurretState::traverseState->targetPositionIntRads = FUNCTION_CHECK_TGT_INTRADS_1;
    functionCheckMoveToTarget();

    TurretState::traverseState->targetPositionIntRads = FUNCTION_CHECK_TGT_INTRADS_2;
    functionCheckMoveToTarget();

    TraverseController::setConditionNeutral();

    return true;
}


bool TraverseController::functionCheckMoveToTarget() {
    int tgtPos = getTargetIntRads();
    int delayMillis = getCurrentDelayMillis();

    while (tgtPos != TraverseController::getCurrentIntRads()) {
        int nextMove = getNextMoveToIntRads(tgtPos, getStepSize());
        TraverseController::moveToIntRads(nextMove, delayMillis);
    }
    return true;
}

void TraverseController::updateTurretState(int currentIntRads, bool isMoving) {
    TurretState::traverseState->currentPositionIntRads = currentIntRads;
    if (TurretState::traverseState->isMoving && !isMoving) {
        Indicator::turnOffLed(MOVE_LED_BLUE);
    }
    if (!TurretState::traverseState->isMoving && isMoving) {
        Indicator::turnOnLed(MOVE_LED_BLUE);
    }
    TurretState::traverseState->isMoving = isMoving;
}

int TraverseController::getCurrentIntRads() {
    return TurretState::traverseState->currentPositionIntRads;
}

int TraverseController::getTargetIntRads() {
    return TurretState::traverseState->targetPositionIntRads;
}

TickType_t TraverseController::getTakeDelay() {
    return Taskr::getMillis(getCurrentDelayMillis());
}

int TraverseController::getCurrentDelayMillis() {
    int delayMillis = TRAVERSE_MOVE_DELAY;
    switch (TurretState::traverseState->speed) {
        case TraverseSpeed::MEDIUM:
            delayMillis = TRAVERSE_MOVE_DELAY;
            break;
        case TraverseSpeed::FAST:
            delayMillis = TRAVERSE_MOVE_DELAY_FAST;
            break;
        case TraverseSpeed::SLOW:
            delayMillis = TRAVERSE_MOVE_DELAY_SLOW;
            break;
        default:
            delayMillis = TRAVERSE_MOVE_DELAY;
            break;
    }
    return delayMillis;
}

int TraverseController::getStepSize() {
    int stepSize;
    switch (TurretState::traverseState->speed) {
        case TraverseSpeed::MEDIUM:
            stepSize = INTRADS_STEP_SIZE;
            break;
        case TraverseSpeed::FAST:
            stepSize = INTRADS_STEP_SIZE_FAST;
            break;
        case TraverseSpeed::SLOW:
            stepSize = INTRADS_STEP_SIZE_SLOW;
            break;
        case TraverseSpeed::STOP:
            stepSize = 0;
            break;
        default:
            stepSize = INTRADS_STEP_SIZE;
            break;
    }
    return stepSize;
}

void TraverseController::setTraverseStateFromCommand() {
    TurretState::traverseState->targetPositionIntRads = TurretState::traverseCommand->targetIntRads;
    TurretState::traverseState->speed = TurretState::traverseCommand->commandSpeed;
    TurretState::traverseCommand->status = CommandStatus::IN_PROGRESS;
}


