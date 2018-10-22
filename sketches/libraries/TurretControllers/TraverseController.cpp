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
int TraverseController::currentPositionIntRads(0);

void TraverseController::initialize(Servo* traverseServo) {

    TraverseController::_traverseServo = traverseServo;
    TraverseController::setConditionNeutral();

    delay(300);
}

void TraverseController::functionCheckDemo(void* pvParameters) {
    TurretState::traverseState = new traverse_state_t();
    TurretState::traverseState->speed = TraverseSpeed::SLOW;

    TraverseController::functionCheckSpeedDemo();
    TraverseController::functionCheckSpeedDemo();
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
    TraverseController::updateTurretState(intRads);

    int servoDegs = map(intRads, 
        TRAVERSE_LIMIT_MIN_INTRADS, 
        TRAVERSE_LIMIT_MAX_INTRADS, 
        TRAVERSE_LIMIT_MIN, 
        TRAVERSE_LIMIT_MAX);
        
    return TraverseController::moveTo(servoDegs, delayMillis);
}

bool TraverseController::moveToIntRads(int intRads) {
    return TraverseController::moveToIntRads(intRads, 0);
}

void TraverseController::dutyCycle(void* pvParameters) {
    int receivedValue = 0;
    int currentTargetIntRads = TurretState::traverseState->targetPositionIntRads;
    int nextStep = 0;
    for (;;) {
        receivedValue = ulTaskNotifyTake(pdTRUE, getTakeDelay());
        
        if (receivedValue != 0) {
            currentTargetIntRads = TurretState::traverseState->targetPositionIntRads;
            receivedValue = 0;
        }
        
        if (currentTargetIntRads != TraverseController::currentPositionIntRads) {
            nextStep = TraverseController::getNextMoveToIntRads(currentTargetIntRads, getStepSize());
                
            TraverseController::moveToIntRads(nextStep);
        }
    }
}

int TraverseController::getNextMoveToIntRads(int currentTargetIntRads, int stepSize) {
    int nextStepIntRads;
    if (currentTargetIntRads > TraverseController::currentPositionIntRads) {
        nextStepIntRads = TraverseController::currentPositionIntRads + stepSize;
    }
    else {
        nextStepIntRads = TraverseController::currentPositionIntRads - stepSize;
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
    TraverseController::currentPositionIntRads = TRAVERSE_LIMIT_STRAIGHT_INTRADS;
    TraverseController::clearIndicators();

    return true;
}

void TraverseController::clearIndicators() {
    Indicator::turnOffLed(MOVE_LED_BLUE);
}

bool TraverseController::functionCheckSpeedDemo() {

    int delayMillis = getCurrentDelayMillis();
    int stepSize = getStepSize();
    int travPosIntRads;

    for (travPosIntRads = TRAVERSE_LIMIT_STRAIGHT_INTRADS;
         travPosIntRads < TRAVERSE_LIMIT_MAX_INTRADS;
         travPosIntRads += stepSize) {
        TraverseController::moveToIntRads(travPosIntRads, delayMillis);
    }

    for (;
        travPosIntRads > TRAVERSE_LIMIT_MIN_INTRADS;
        travPosIntRads -= stepSize) {
        TraverseController::moveToIntRads(travPosIntRads, delayMillis);
    }

    for (;
        travPosIntRads < TRAVERSE_LIMIT_STRAIGHT_INTRADS;
        travPosIntRads += stepSize) {
        TraverseController::moveToIntRads(travPosIntRads, delayMillis);
    }

    TurretState::traverseState->targetPositionIntRads = FUNCTION_CHECK_TGT_INTRADS_1;
    for (;
        travPosIntRads > getTargetIntRads();
        travPosIntRads -= stepSize) {
        TraverseController::moveToIntRads(travPosIntRads, delayMillis);
    }

    TurretState::traverseState->targetPositionIntRads = FUNCTION_CHECK_TGT_INTRADS_2;
    for (;
        travPosIntRads > getTargetIntRads();
        travPosIntRads += stepSize) {
        TraverseController::moveToIntRads(travPosIntRads, delayMillis);
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
        case TraverseSpeed::FAST:
            delayMillis = TRAVERSE_MOVE_DELAY_FAST;
        case TraverseSpeed::SLOW:
            delayMillis = TRAVERSE_MOVE_DELAY_SLOW;
    }
    return delayMillis;
}

int TraverseController::getStepSize() {
    int stepSize;
    switch (TurretState::traverseState->speed) {
        case TraverseSpeed::MED:
            stepSize = INTRADS_STEP_SIZE;
        case TraverseSpeed::FAST:
            stepSize = INTRADS_STEP_SIZE_FAST;
        case TraverseSpeed::SLOW:
            stepSize = INTRADS_STEP_SIZE_SLOW;
    }
    return stepSize;
}


