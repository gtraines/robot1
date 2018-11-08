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
#include <TraverseState.h>
#include <TurretState.h>
#include <TurretTasks.h>

Servo* TraverseController::_traverseServo = nullptr;
TaskHandle_t TraverseController::traverseTaskHandle;

void TraverseController::initialize(Servo* traverseServo) {

    TraverseController::_traverseServo = traverseServo;

    TurretState::traverseState = new traverse_state_t();
    TurretState::traverseState->speed = TraverseSpeed::MED;
    TurretState::traverseState->currentPositionIntRads = 0;
    TurretState::traverseState->targetPositionIntRads = 0;

    TraverseController::setConditionNeutral();

    delay(300);
}

void TraverseController::functionCheckDemo(void* pvParameters) {

    TraverseController::functionCheckSpeedDemo();
    TurretState::traverseState->speed = TraverseSpeed::FAST;
    TraverseController::functionCheckSpeedDemo();
    TurretState::traverseState->speed = TraverseSpeed::SLOW;
    TraverseController::functionCheckSpeedDemo();

    BaseType_t notifyMonitorSuccess = xTaskNotifyGive(TurretTasks::functionCheckMonitorHandle);
    
    if (notifyMonitorSuccess == pdTRUE) {
        vTaskDelete(TraverseController::traverseTaskHandle);
    }
    else {
        Indicator::turnOnLed(ARD_STATUS_RED);
    }
}

bool TraverseController::moveToIntRads(int intRads, int delayMillis) {

    int servoDegs = map(intRads, 
        TRAVERSE_LIMIT_MIN_INTRADS, 
        TRAVERSE_LIMIT_MAX_INTRADS, 
        TRAVERSE_LIMIT_MIN, 
        TRAVERSE_LIMIT_MAX);
        
    bool moveResult = TraverseController::moveTo(servoDegs, delayMillis);
    if (moveResult) {
        updateTurretState(intRads);
    }
}

bool TraverseController::moveToIntRads(int intRads) {
    return TraverseController::moveToIntRads(intRads, 0);
}

void TraverseController::dutyCycle(void* pvParameters) {
    int receivedValue = 0;
    int targetIntRads = getTargetIntRads();
    int nextStep = 0;
    for (;;) {
        receivedValue = ulTaskNotifyTake(pdTRUE, getTakeDelay());
        
        if (receivedValue != 0) {
            targetIntRads = getTargetIntRads();
            receivedValue = 0;
        }
        
        if (targetIntRads != TraverseController::getCurrentIntRads()) {
            nextStep = TraverseController::getNextMoveToIntRads(targetIntRads, getStepSize());
                
            TraverseController::moveToIntRads(nextStep);
        }
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
    return (targetIntRads >= TRAVERSE_LIMIT_MIN_INTRADS && targetIntRads <= TRAVERSE_LIMIT_MAX_INTRADS);
}

bool TraverseController::moveTo(int targetPosition, int delayMillis) {

    if (targetPosition < TRAVERSE_LIMIT_MIN) {
        Indicator::turnOnLed(MOVE_LED_RED);
        targetPosition = TRAVERSE_LIMIT_MIN;
    }

    if (targetPosition > TRAVERSE_LIMIT_MAX) {
        Indicator::turnOnLed(MOVE_LED_RED);
        targetPosition = TRAVERSE_LIMIT_MAX;
    }
    
    Indicator::turnOnLed(MOVE_LED_BLUE);
    
    TraverseController::_traverseServo->write(targetPosition);
    if (delayMillis > 0) {
      Taskr::delayMs(delayMillis);  
    }
    TraverseController::clearIndicators();
    return true;
}

bool TraverseController::setConditionNeutral(){
    Indicator::turnOnLed(MOVE_LED_BLUE);
    TraverseController::_traverseServo->write(TRAVERSE_LIMIT_STRAIGHT);
    updateTurretState(TRAVERSE_LIMIT_STRAIGHT_INTRADS);
    TraverseController::clearIndicators();

    return true;
}

void TraverseController::clearIndicators() {
    Indicator::turnOffLed(MOVE_LED_BLUE);
}

bool TraverseController::functionCheckSpeedDemo() {

    TurretState::traverseState->targetPositionIntRads = TRAVERSE_LIMIT_MIN_INTRADS;
    functionCheckMoveToTarget();

    TurretState::traverseState->targetPositionIntRads = TRAVERSE_LIMIT_MAX_INTRADS;
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

void TraverseController::updateTurretState(int currentIntRads) {
    TurretState::traverseState->currentPositionIntRads = currentIntRads;
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
    int delayMillis;
    switch (TurretState::traverseState->speed) {
        case TraverseSpeed::MED:
            delayMillis = TRAVERSE_MOVE_DELAY;
            break;
        case TraverseSpeed::FAST:
            delayMillis = TRAVERSE_MOVE_DELAY_FAST;
            break;
        case TraverseSpeed::SLOW:
            delayMillis = TRAVERSE_MOVE_DELAY_SLOW;
            break;
    }
    return delayMillis;
}

int TraverseController::getStepSize() {
    int stepSize;
    switch (TurretState::traverseState->speed) {
        case TraverseSpeed::MED:
            stepSize = INTRADS_STEP_SIZE;
            break;
        case TraverseSpeed::FAST:
            stepSize = INTRADS_STEP_SIZE_FAST;
            break;
        case TraverseSpeed::SLOW:
            stepSize = INTRADS_STEP_SIZE_SLOW;
            break;
    }
    return stepSize;
}


