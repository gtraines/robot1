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
#include <TurretState.h>
#include <TurretTasks.h>

Servo* TraverseController::_traverseServo = NULL;
TaskHandle_t TraverseController::traverseTaskHandle;
int TraverseController::currentPositionIntRads(0);

void TraverseController::initialize(Servo* traverseServo) {

    TraverseController::_traverseServo = traverseServo;
    TraverseController::_traverseServo->write(TRAVERSE_LIMIT_STRAIGHT);
    delay(300);
    TraverseController::currentPositionIntRads = TRAVERSE_LIMIT_STRAIGHT_INTRADS;
}

void TraverseController::functionCheckDemo(void* pvParameters) {
    int travPos = 0;
    for (travPos = TRAVERSE_LIMIT_STRAIGHT; travPos < TRAVERSE_LIMIT_MAX; travPos++) {
        TraverseController::moveTo(travPos, TRAVERSE_MOVE_DELAY);
    }

    for (travPos = TRAVERSE_LIMIT_MAX; travPos > TRAVERSE_LIMIT_MIN; travPos--) {
        TraverseController::moveTo(travPos, TRAVERSE_MOVE_DELAY);
    }

    for (travPos = TRAVERSE_LIMIT_MIN; travPos < TRAVERSE_LIMIT_STRAIGHT; travPos++) {
        TraverseController::moveTo(travPos, TRAVERSE_MOVE_DELAY);
    }
    
    int travPosIntRads = 0;
    
    for (travPosIntRads = TRAVERSE_LIMIT_STRAIGHT_INTRADS; 
        travPosIntRads > TRAVERSE_LIMIT_MIN_INTRADS;
        travPosIntRads -= 6) {
            TraverseController::moveToIntRads(travPosIntRads, 45);
        }
        
    for (travPosIntRads = travPosIntRads; 
        travPosIntRads < TRAVERSE_LIMIT_MAX_INTRADS;
        travPosIntRads += 6) {
            TraverseController::moveToIntRads(travPosIntRads, 45);
        }
        
            
    for (travPosIntRads = travPosIntRads; 
        travPosIntRads > TRAVERSE_LIMIT_STRAIGHT_INTRADS;
        travPosIntRads -= 6) {
            TraverseController::moveToIntRads(travPosIntRads, 45);
        }
        
    BaseType_t notifyMonitorSuccess = xTaskNotifyGive(TurretTasks::functionCheckMonitorHandle);
    
    if (notifyMonitorSuccess == pdTRUE) {
        vTaskDelete(TraverseController::traverseTaskHandle);
    }
    else {
        Indicator::turnOnLed(ARD_STATUS_RED);
    }
    
}

bool TraverseController::moveToIntRads(int intRads, int delayMillis) {
    TurretState::tgtTraverseIntRads = intRads;
    int servoDegs = map(intRads, 
        TRAVERSE_LIMIT_MIN_INTRADS, 
        TRAVERSE_LIMIT_MAX_INTRADS, 
        TRAVERSE_LIMIT_MIN, 
        TRAVERSE_LIMIT_MAX);
        
    return TraverseController::moveTo(servoDegs, delayMillis);
}

void TraverseController::dutyCycle(void* pvParameters) {
    int receivedValue = 0;
    int currentTargetIntRads = TraverseController::currentPositionIntRads;
    int stepSize = 6;
    int nextStep = 0;
    for (;;) {
        receivedValue = ulTaskNotifyTake(pdTRUE, Taskr::getMillis(TRAVERSE_MOVE_DELAY));
        
        if (receivedValue != 0) {
            currentTargetIntRads = TurretState::tgtTraverseIntRads;
            receivedValue = 0;
        }
        
        if (currentTargetIntRads != TraverseController::currentPositionIntRads 
            && abs((TraverseController::currentPositionIntRads - currentPositionIntRads)) > stepSize) {
                nextStep = TraverseController::getNextMoveToIntRads(currentTargetIntRads);
                
            TraverseController::moveToIntRads(nextStep, 0);
        }
    }
}

int TraverseController::getNextMoveToIntRads(int currentTargetIntRads) {
    int stepSize = 6;
    if (currentTargetIntRads > TraverseController::currentPositionIntRads) {
        return TraverseController::currentPositionIntRads + stepSize;
    }
    else {
        return TraverseController::currentPositionIntRads - stepSize;
    }
    
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

