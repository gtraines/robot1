#include "ElevationController.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Taskr.h>
#include <ElevationConfig.h>
#include <ElevationCommand.h>
#include <Indicator.h>
#include <PotMotorRtos.h>
#include <TurretPins.h>
#include <TurretState.h>
#include <TurretTasks.h>

PotMotorRtos* ElevationController::_elevationMotor = nullptr;
TaskHandle_t ElevationController::elevationTaskHandle = nullptr;

// Run function check?
bool ElevationController::initialize() {
    ElevationController::_elevationMotor = new PotMotorRtos(
            (uint8_t)ELEVATION_MOTOR_ENABLE,
            (uint8_t)ELEVATION_MOTOR_POS,
            (uint8_t)ELEVATION_MOTOR_NEG,
            ELEVATION_MOTOR_POSITION,
            (int)ELEVATION_MIN,
            (int)ELEVATION_MAX,
            (int)ELEVATION_RESOLUTION,
            (int)MOTOR_MIN_SPEED,
            (int)MOTOR_MAX_SPEED,
            (int)MOTOR_MED_SPEED,
            (int)MOTOR_JERK_SPEED);
}

void ElevationController::functionCheckDemo(void* pvParameters) {
    TurretState::tgtElevationIntRads = ELEVATION_NEUTRAL_INTRADS;
    ElevationController::setConditionNeutral();
    boolean hasNextStep = true;
    while (hasNextStep) {
        hasNextStep = ElevationController::_elevationMotor->nextStep();
        Taskr::delayMs(45);
    }

    ElevationController::setConditionNeutral();
    Taskr::delayMs(1000);
    ElevationController::moveToIntRads(TurretState::tgtElevationIntRads);

    TurretState::tgtElevationIntRads = 0;
    Taskr::delayMs(500);
    
    BaseType_t notifyMonitorSuccess = xTaskNotifyGive(TurretTasks::functionCheckMonitorHandle);
    if (notifyMonitorSuccess == pdTRUE) {
        vTaskDelete(ElevationController::elevationTaskHandle);
    }
    else {
        Indicator::turnOnLed(ARD_STATUS_RED);
    }
}

bool ElevationController::setConditionNeutral() {

    bool wasGoodCommand = ElevationController::moveToIntRads(ELEVATION_NEUTRAL_INTRADS);

    if (wasGoodCommand) {
        boolean inProgress = true;

        while (inProgress) {
            inProgress = ElevationController::_elevationMotor->nextStep();
            Taskr::delayMs(30);
        }
    }
    return wasGoodCommand;
}
void ElevationController::clearIndicators() {
    Indicator::turnOffLed(MOVE_LED_GRN);
}

bool ElevationController::moveTo(int readingValue) {
    bool isGoodCommand = true;
    Indicator::turnOnLed(MOVE_LED_GRN);
    
    if (readingValue > ELEVATION_MAX) {
        isGoodCommand = false;
        Indicator::turnOnLed(MOVE_LED_RED);
        readingValue = ELEVATION_MAX;
    }
    
    if (readingValue < ELEVATION_MIN) {
        isGoodCommand = false;
        Indicator::turnOnLed(MOVE_LED_RED);
        readingValue = ELEVATION_MIN;
    }
    
    ElevationController::_elevationMotor->setTargetCommand(readingValue, (int)MotorSpeed::SLOW);
    ElevationController::clearIndicators();
    
    return isGoodCommand;
}


void ElevationController::dutyCycle(void* pvParameters) {
    int receivedValue = 0;
    int targetIntRads = getTargetIntRads();
    int nextStep = 0;
//    for (;;) {
//        receivedValue = ulTaskNotifyTake(pdTRUE, getTakeDelay());
//
//        if (receivedValue != 0) {
//            targetIntRads = getTargetIntRads();
//            receivedValue = 0;
//        }
//
//        if (targetIntRads != ElevationController::getCurrentIntRads()) {
//            nextStep = ElevationController::getNextMoveToIntRads(targetIntRads, getStepSize());
//
//            ElevationController::moveToIntRads(nextStep);
//        }
//    }
    
}

bool ElevationController::moveToIntRads(int intRads) {
    int potRdg = map(intRads, ELEVATION_MIN_INTRADS, ELEVATION_MAX_INTRADS, ELEVATION_MIN, ELEVATION_MAX);
    
    return ElevationController::moveTo(potRdg);
}

int ElevationController::getNextMoveToIntRads(int targetIntRads, int stepSize) {
    return 0;
}

bool ElevationController::functionCheckSpeedDemo() {
    return true;
}

bool ElevationController::functionCheckMoveToTarget() {
    return true;
}

void ElevationController::updateTurretState(int currentIntRads) {
}

TickType_t ElevationController::getTakeDelay() {
    return Taskr::getMillis(45);
}

int ElevationController::getCurrentDelayMillis() {
    return 0;
}

int ElevationController::getStepSize() {
    return 0;
}

bool ElevationController::canMoveTo(int targetIntRads) {
    return (targetIntRads >= ELEVATION_MIN_INTRADS && targetIntRads <= ELEVATION_MAX_INTRADS);
}

int ElevationController::getCurrentIntRads() {
}

int ElevationController::getTargetIntRads() {
    return TurretState::tgtElevationIntRads;
}
