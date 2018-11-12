//
// Created by graham on 10/6/18.
//
#include "TurretController.h"
#include <TurretPins.h>

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Servo.h>
#include <Taskr.h>

#include <TurretTasks.h>
#include <TurretState.h>

#include <Indicator.h>

#include <CannonController.h>

#include <ElevationCommand.h>
#include <ElevationController.h>

#include <TraverseController.h>
#include <TraverseConfig.h>

TaskHandle_t TurretController::indicatorTaskHandle = nullptr;

void TurretController::initialize(Servo* traverseServo) {
    TurretController::setPins();
    TurretController::turnOffAllIndicators();

    TraverseController::initialize(traverseServo);
    ElevationController::initialize();
    CannonController::initialize();
    
    BaseType_t execCreated = xTaskCreate(
        TurretTasks::executive,
        (const portCHAR *) "Executive",
        128,  // Stack size
        NULL,
        2,  // Priority
        &TurretTasks::executiveHandle);
        
    BaseType_t dutyCycleCreated = xTaskCreate(
        TurretTasks::dutyCycleMonitor,
        (const portCHAR *) "DutyCycleMonitor",
        128,  // Stack size
        NULL,
        1, // Priority
        &TurretTasks::dutyCycleMonitorHandle);
}

bool TurretController::setPins() {
    pinMode(ELEVATION_MOTOR_ENABLE, OUTPUT);
    pinMode(ELEVATION_MOTOR_POS, OUTPUT);
    pinMode(ELEVATION_MOTOR_NEG, OUTPUT);

    pinMode(ARD_STATUS_GRN, OUTPUT);
    pinMode(ARD_STATUS_RED, OUTPUT);

    pinMode(ACTY_LED_1, OUTPUT);
    pinMode(ACTY_LED_2, OUTPUT);
    pinMode(ACTY_LED_3, OUTPUT);

    pinMode(MOVE_LED_GRN, OUTPUT);
    pinMode(MOVE_LED_RED, OUTPUT);
    pinMode(MOVE_LED_BLUE, OUTPUT);

    pinMode(CANNON_LED, OUTPUT);

    return true;
}

bool TurretController::setControlMode(int mode) {
    return false;
}

bool TurretController::setConditionNeutral() {
    return true;
}

void TurretController::functionCheckDemo(void* pvParameters) {

    BaseType_t indicatorStatus = xTaskCreate(
        TurretController::indicatorFunctionCheck,
        (const portCHAR *) "IndicatorTest",
        128,  // Stack size
        NULL,
        1, // Priority
        &TurretController::indicatorTaskHandle);


    BaseType_t functionCheckMonitorStatus = xTaskCreate(
        TurretTasks::functionCheckMonitor,
        (const portCHAR *) "FunctionCheckMonitor",
        256,  // Stack size
        NULL,
        2,  // Priority
        &TurretTasks::functionCheckMonitorHandle);

    if (indicatorStatus != pdPASS
        || functionCheckMonitorStatus != pdPASS
        )
    {
        TurretController::setStatusError();
    }

}

bool TurretController::turnOffAllIndicators() {
    Indicator::turnOffLed(ARD_STATUS_GRN);
    Indicator::turnOffLed(ARD_STATUS_RED);

    Indicator::turnOffLed(ACTY_LED_1);
    Indicator::turnOffLed(ACTY_LED_2);
    Indicator::turnOffLed(ACTY_LED_3);

    Indicator::turnOffLed(MOVE_LED_GRN);
    Indicator::turnOffLed(MOVE_LED_RED);
    Indicator::turnOffLed(MOVE_LED_BLUE);

    Indicator::turnOffLed(CANNON_LED);

    return true;
}

void TurretController::indicatorFunctionCheck(void* pvParameters) {

    TurretState::elevationCommand->targetIntRads = ELEVATION_MAX_INTRADS;
    TurretState::elevationCommand->commandSpeed = ElevationSpeed::FAST;

    TurretState::traverseCommand->commandSpeed = TraverseSpeed::MEDIUM;
    TurretState::traverseCommand->targetIntRads = TRAVERSE_LIMIT_MAX_INTRADS;

    BaseType_t ackSuccess = xTaskNotifyGive(ElevationController::elevationTaskHandle);
    ackSuccess = xTaskNotifyGive(TraverseController::traverseTaskHandle);

    Taskr::delayMs(90);
    while (TurretState::traverseState->isMoving) {
        Taskr::delayMs(90);
    }

    TurretState::elevationCommand->targetIntRads = ELEVATION_MIN_INTRADS;
    TurretState::elevationCommand->commandSpeed = ElevationSpeed::MEDIUM;

    TurretState::traverseCommand->commandSpeed = TraverseSpeed::MEDIUM;
    TurretState::traverseCommand->targetIntRads = TRAVERSE_LIMIT_MIN_INTRADS;

    ackSuccess = xTaskNotifyGive(ElevationController::elevationTaskHandle);
    ackSuccess = xTaskNotifyGive(TraverseController::traverseTaskHandle);

    Taskr::delayMs(90);
    while (TurretState::traverseState->isMoving) {
        Taskr::delayMs(90);
    }

    // Update CommandState??

    TurretState::elevationCommand->targetIntRads = ELEVATION_MAX_INTRADS;
    TurretState::elevationCommand->commandSpeed = ElevationSpeed::FAST;

    TurretState::traverseCommand->commandSpeed = TraverseSpeed::FAST;
    TurretState::traverseCommand->targetIntRads = TRAVERSE_LIMIT_STRAIGHT_INTRADS;

    ackSuccess = xTaskNotifyGive(ElevationController::elevationTaskHandle);
    ackSuccess = xTaskNotifyGive(TraverseController::traverseTaskHandle);

    Taskr::delayMs(90);
    while (TurretState::traverseState->isMoving) {
        Taskr::delayMs(90);
    }

    ElevationController::setConditionNeutral();

    Indicator::alertBlinkFast(ACTY_LED_1);
    Indicator::alertBlinkFast(ACTY_LED_2);
    Indicator::alertBlinkFast(ACTY_LED_3);

    int successfulNotifications = 0;
    BaseType_t notifyMonitorSuccess = xTaskNotifyGive(TurretTasks::functionCheckMonitorHandle);
    if (notifyMonitorSuccess == pdTRUE) {
        successfulNotifications++;
    }
    notifyMonitorSuccess = xTaskNotifyGive(TurretTasks::functionCheckMonitorHandle);
    if (notifyMonitorSuccess == pdTRUE) {
        successfulNotifications++;
    }
    notifyMonitorSuccess = xTaskNotifyGive(TurretTasks::functionCheckMonitorHandle);
    if (notifyMonitorSuccess == pdTRUE) {
        successfulNotifications++;
    }
    if (successfulNotifications == 3) {
        vTaskDelete(TurretController::indicatorTaskHandle);
    }
    else {
        TurretController::setStatusError();
    }
}

void TurretController::setStatusGood() {
    Indicator::turnOffLed(ARD_STATUS_RED);
    Indicator::turnOnLed(ARD_STATUS_GRN);
}

void TurretController::setStatusError() {

    Indicator::turnOffLed(ARD_STATUS_GRN);
    Indicator::turnOnLed(ARD_STATUS_RED);
}
