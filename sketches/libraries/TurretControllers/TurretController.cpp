//
// Created by graham on 10/6/18.
//
#include "TurretController.h"
#include <TurretPins.h>

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <HardwareSerial.h>
#include <Print.h>

#include <Servo.h>
#include <Taskr.h>
#include <Indicator.h>

#include <CannonState.h>
#include <CannonCommand.h>
#include <CannonController.h>

#include <ElevationCommand.h>
#include <ElevationController.h>

#include <TraverseController.h>
#include <TraverseConfig.h>

#include <IrSensorMonitor.h>
#include <TurretState.h>

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

void TurretController::initialize(Servo *traverseServo, HardwareSerial *serial) {
    initialize(traverseServo);
    serial->println("Cat and also cat");
    IrSensorMonitor::initialize(serial);
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
    bool neutralReached1 = slewToWaitForCompletion(
            TRAVERSE_NEUTRAL_INTRADS, TraverseSpeed::MEDIUM, ELEVATION_NEUTRAL_INTRADS, ElevationSpeed::MEDIUM);

//    bool elevationIncrement1 = incrementElevation(ElevationDirection::UP, 150, ElevationSpeed::MEDIUM);
//    Taskr::delayMs(135);
//    while (TurretState::traverseState->isMoving || TurretState::elevationState->isMoving) {
//        Taskr::delayMs(135);
//    }


    bool areaTargetTestComplete = fireCannon(CannonSignal::RED, (uint8_t)5);
    Taskr::delayMs(135);
    while (TurretState::cannonState->isFiring) {
        Taskr::delayMs(135);
    }

    TurretState::allFunctionChecksCompleted = areaTargetTestComplete //&& elevationIncrement1
            && neutralReached1;
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

bool TurretController::incrementTraverse(TraverseDirection direction, int intRads, TraverseSpeed speed) {
    int newTarget = TurretState::traverseState->currentPositionIntRads + ((int)direction * intRads);
    bool tgtSuccess = TurretController::setTraverseTargetIntRads(newTarget, speed);
    return tgtSuccess;
}

bool TurretController::incrementElevation(ElevationDirection direction, int intRads, ElevationSpeed speed) {
    int newTarget = TurretState::elevationState->currentPositionIntRads + ((int)direction * intRads);
    bool tgtSuccess = TurretController::setElevationTargetIntRads(newTarget, speed);
    return tgtSuccess;
}

bool TurretController::fireCannon(CannonSignal signal, uint8_t burstLength) {
    TurretState::cannonCommand->signalId = signal;
    TurretState::cannonCommand->burstLength = burstLength;

    BaseType_t ackSuccess = xTaskNotifyGive(CannonController::cannonTaskHandle);
    return ackSuccess == pdTRUE;
}

bool TurretController::slewToTraverseAndElevation(int traverseTgtIntRads, TraverseSpeed traverseSpeed,
                                                  int elevationTgtIntRads, ElevationSpeed elevationSpeed) {
    bool traverseSet = setTraverseTargetIntRads(traverseTgtIntRads, traverseSpeed);
    bool elevationSet = setElevationTargetIntRads(elevationTgtIntRads, elevationSpeed);
    return traverseSet && elevationSet;
}

bool TurretController::slewToWaitForCompletion(int traverseTgtIntRads, TraverseSpeed traverseSpeed,
                                          int elevationTgtIntRads, ElevationSpeed elevationSpeed) {
    bool tgtSet = slewToTraverseAndElevation(
            traverseTgtIntRads, traverseSpeed, elevationTgtIntRads, elevationSpeed);

    if (tgtSet) {
        Taskr::delayMs(90);
        while (TurretState::traverseState->isMoving || TurretState::elevationState->isMoving) {
            Taskr::delayMs(90);
        }
    }

    return tgtSet;
}

bool TurretController::fireCannonAreaTarget(int burstLength, CannonSignal signal) {
    int startingTraverseIntRads = TurretState::traverseState->currentPositionIntRads;
    int startingElevationIntRads = TurretState::elevationState->currentPositionIntRads;

    int jitterTraverse = 0;
    int jitterElevation = 0;
    bool iterationSuccess = false;
    for (int burstIter = 0; burstIter < burstLength; burstIter++) {
        if (fireCannon(signal, 1)) {
            jitterTraverse = getJitterPositionIntRads(startingTraverseIntRads, TRAVERSE_JITTER_INTRADS);
            jitterElevation = getJitterPositionIntRads(startingElevationIntRads, ELEVATION_JITTER_INTRADS);

            iterationSuccess = slewToTraverseAndElevation(jitterTraverse, TraverseSpeed::FAST,
                    jitterElevation, ElevationSpeed::FAST);
            Taskr::delayMs(90);
        }
    }

    while (TurretState::traverseState->isMoving || TurretState::elevationState->isMoving) {
        Taskr::delayMs(105);
    }
    bool returnToStart = slewToWaitForCompletion(startingTraverseIntRads, TraverseSpeed::MEDIUM,
            startingElevationIntRads, ElevationSpeed::MEDIUM);

    return iterationSuccess && returnToStart;
}

int TurretController::getJitterPositionIntRads(int originalPositionIntRads, int jitterIntRads) {
    int directionChoice = random(0, 100) % 2;
    int directionMultiplier = directionChoice == 0 ? -1 : 1;
    int jitterResult = originalPositionIntRads + (directionMultiplier * jitterIntRads);
    return jitterResult;
}

