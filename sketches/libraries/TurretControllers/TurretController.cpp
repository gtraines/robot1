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
#include <Indicator.h>

#include <TurretState.h>

#include <CannonController.h>

#include <ElevationCommand.h>
#include <ElevationController.h>

#include <TraverseController.h>
#include <TraverseConfig.h>

TaskHandle_t TurretController::functionCheckWorkerTaskHandle = nullptr;
TaskHandle_t TurretController::dutyCycleMonitorTaskHandle = nullptr;
TickType_t TurretController::dutyCycleMonitorDelay = Taskr::getMillis(1000);

void TurretController::initialize(Servo* traverseServo) {
    TurretController::setPins();
    TurretController::turnOffAllIndicators();

    TraverseController::initialize(traverseServo);
    ElevationController::initialize();
    CannonController::initialize();
        
    BaseType_t dutyCycleCreated = xTaskCreate(
        TurretController::dutyCycleMonitor,
        (const portCHAR *) "DutyCycleMonitor",
        128,  // Stack size
        NULL,
        1, // Priority
        &TurretController::dutyCycleMonitorTaskHandle);

    if (dutyCycleCreated == pdTRUE) {

        BaseType_t functionCheckWorkerCreated = xTaskCreate(
                TurretController::functionCheckWorker,
                (const portCHAR *) "FunctionCheckWorker",
                128,  // Stack size
                NULL,
                1, // Priority
                &TurretController::functionCheckWorkerTaskHandle);
    }
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
    ElevationController::setConditionNeutral();
    TraverseController::setConditionNeutral();
    while (TurretState::traverseState->isMoving) {
        Taskr::delayMs(90);
    }
    return true;
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

void TurretController::functionCheckWorker(void* pvParameters) {

    bool traverseSet = setTraverseTargetIntRads(TRAVERSE_LIMIT_MIN_INTRADS, TraverseSpeed::MEDIUM);
    bool elevationSet = setElevationTargetIntRads(ELEVATION_MIN_INTRADS, ElevationSpeed::MEDIUM);

    if (elevationSet && traverseSet) {
        fireCannon();
    }
    Taskr::delayMs(90);

    while (TurretState::traverseState->isMoving) {

        Taskr::delayMs(90);
    }

    traverseSet = setTraverseTargetIntRads(TRAVERSE_LIMIT_MAX_INTRADS, TraverseSpeed::MEDIUM);
    elevationSet = setElevationTargetIntRads(ELEVATION_MAX_INTRADS, ElevationSpeed::MEDIUM);

    if (elevationSet && traverseSet) {
        fireCannon();
    }
    Taskr::delayMs(90);
    while (TurretState::traverseState->isMoving) {

        Taskr::delayMs(90);
    }

    traverseSet = setTraverseTargetIntRads(TRAVERSE_LIMIT_STRAIGHT_INTRADS, TraverseSpeed::MEDIUM);
    elevationSet = setElevationTargetIntRads(ELEVATION_NEUTRAL_INTRADS, ElevationSpeed::MEDIUM);
    if (elevationSet && traverseSet) {
        fireCannon();
    }
    while (TurretState::traverseState->isMoving) {

        Taskr::delayMs(90);
    }

    if (elevationSet && traverseSet) {
        fireCannon();
    }

    TurretState::allFunctionChecksCompleted = true;
    BaseType_t monitorNotified = xTaskNotifyGive(TurretController::dutyCycleMonitorTaskHandle);

    if (monitorNotified == pdTRUE) {
        vTaskDelete(TurretController::functionCheckWorkerTaskHandle);
    }
    else {
        TurretController::setStatusError();
    }
}

void TurretController::dutyCycleMonitor(void* pvParameters) {
    uint32_t receivedValue = 0;

    while (!receivedValue > 0) {
        receivedValue = ulTaskNotifyTake(pdTRUE, TurretController::dutyCycleMonitorDelay);
    }
    if (!TurretState::allFunctionChecksCompleted) {
        setStatusError();
    }

    while (true) {

        Indicator::turnOnLed(ARD_STATUS_GRN);
        Taskr::delayMs(800);
        Indicator::turnOffLed(ARD_STATUS_GRN);
        Taskr::delayMs(300);
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

bool TurretController::setTraverseTargetIntRads(int tgtIntRads, TraverseSpeed speed) {
    TurretState::traverseCommand->targetIntRads = tgtIntRads;
    TurretState::traverseCommand->commandSpeed = speed;

    BaseType_t ackSuccess = xTaskNotifyGive(TraverseController::traverseTaskHandle);
    return ackSuccess == pdTRUE;
}

bool TurretController::setElevationTargetIntRads(int tgtIntRads, ElevationSpeed speed) {
    TurretState::elevationCommand->targetIntRads = tgtIntRads;
    TurretState::elevationCommand->commandSpeed = speed;

    BaseType_t ackSuccess = xTaskNotifyGive(ElevationController::elevationTaskHandle);
    return ackSuccess == pdTRUE;
}

bool TurretController::incrementTraverse(int direction, int intRads, TraverseSpeed speed) {
    return false;
}

bool TurretController::incrementElevation(int direction, int intRads, ElevationSpeed speed) {
    return false;
}

bool TurretController::fireCannon() {
    BaseType_t ackSuccess = xTaskNotifyGive(CannonController::cannonTaskHandle);
    return ackSuccess == pdTRUE;
}
