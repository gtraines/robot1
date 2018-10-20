//
// Created by graham on 10/7/18.
//
#include "TraverseController.h"
#include <Arduino.h>
#include <Servo.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Indicator.h>
#include <TurretPins.h>
#include <TraverseConfig.h>
#include <TurretTasks.h>

Servo* TraverseController::_traverseServo = NULL;
TaskHandle_t TraverseController::traverseTaskHandle;

void TraverseController::initialize(Servo* traverseServo) {

    TraverseController::_traverseServo = traverseServo;

    delay(15);

    if (TraverseController::setConditionNeutral()) {
        Indicator::turnOnLed(ACTY_LED_2);
        delay(200);
    }
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
    
    BaseType_t notifyExecutiveSuccess = xTaskNotifyGive(TurretTasks::functionCheckMonitorHandle);
    vTaskDelete(TraverseController::traverseTaskHandle);
}

bool TraverseController::canMoveTo(int targetPosition) {
    return false;
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
    vTaskDelay(delayMillis/portTICK_PERIOD_MS);

    TraverseController::clearIndicators();
    return true;
}

bool TraverseController::setConditionNeutral(){
    TraverseController::_traverseServo->write(TRAVERSE_LIMIT_STRAIGHT);
    TraverseController::clearIndicators();
    delay(30);
    
    return true;
}
void TraverseController::clearIndicators() {
    
    Indicator::turnOffLed(MOVE_LED_RED);
    Indicator::turnOffLed(MOVE_LED_BLUE);
}
