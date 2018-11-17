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

    TurretState::elevationState = new ElevationState_t {};
    TurretState::elevationState->isMoving = false;
    TurretState::elevationState->speed = ElevationSpeed::STOP;
    TurretState::elevationState->targetPositionIntRads = ELEVATION_NEUTRAL_INTRADS;
    TurretState::elevationState->currentPositionIntRads = getCurrentIntRads();

    TurretState::elevationCommand = new ElevationCommand_t {};
    TurretState::elevationCommand->commandSpeed = ElevationSpeed::STOP;
    TurretState::elevationCommand->targetIntRads = ELEVATION_NEUTRAL_INTRADS;

    BaseType_t elevationStatus = xTaskCreate(
            ElevationController::dutyCycle,
            (const portCHAR *) "ElevationControllerTask",
            128,  // Stack size
            NULL,
            2,  // Priority
            &ElevationController::elevationTaskHandle);

    return elevationStatus == pdTRUE;
}

void ElevationController::functionCheckDemo(void* pvParameters) {

    ElevationController::setConditionNeutral();
    TurretState::elevationCommand->targetIntRads = ELEVATION_MAX_INTRADS;
    TurretState::elevationCommand->commandSpeed = ElevationSpeed::FAST;
    functionCheckMoveToTarget();

    TurretState::elevationCommand->targetIntRads = ELEVATION_MIN_INTRADS;
    TurretState::elevationCommand->commandSpeed = ElevationSpeed::MEDIUM;
    functionCheckMoveToTarget();
    // Update CommandState??

    TurretState::elevationCommand->targetIntRads = ELEVATION_MAX_INTRADS;
    TurretState::elevationCommand->commandSpeed = ElevationSpeed::FAST;
    functionCheckMoveToTarget();

    ElevationController::setConditionNeutral();

}

bool ElevationController::setConditionNeutral() {

    TurretState::elevationState->targetPositionIntRads = ELEVATION_NEUTRAL_INTRADS;
    TurretState::elevationState->speed = ElevationSpeed::MEDIUM;
    bool wasGoodCommand = ElevationController::moveToIntRads(ELEVATION_NEUTRAL_INTRADS, ElevationSpeed::MEDIUM);

    if (wasGoodCommand) {
        boolean isMoving = true;

        while (isMoving) {
            isMoving = ElevationController::_elevationMotor->nextStep();
            Taskr::delayMs(getCurrentDelayMillis());
            updateTurretState(isMoving);
        }
    }
    return wasGoodCommand;
}
void ElevationController::clearIndicators() {
    Indicator::turnOffLed(MOVE_LED_GRN);
}

bool ElevationController::moveTo(int readingValue, ElevationSpeed speed) {
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
    
    bool setTargetSuccess = ElevationController::_elevationMotor->setTargetCommand(readingValue, (int)speed);

    return isGoodCommand && setTargetSuccess;
}


void ElevationController::dutyCycle(void* pvParameters) {
    ElevationController::setConditionNeutral();
    uint32_t receivedValue = 0;
    int targetIntRads = getTargetIntRads();
    int nextStep = 0;
    boolean success = true;
    boolean isMoving = false;
    while (success) {
        receivedValue = ulTaskNotifyTake(pdTRUE, getTakeDelay());
        isMoving = false;

        if (receivedValue != 0) {
            setElevationStateFromCommand();
            targetIntRads = getTargetIntRads();
            receivedValue = 0;
            moveToIntRads(targetIntRads, TurretState::elevationState->speed);
        }

        if (targetIntRads > 0 && targetIntRads != ElevationController::getCurrentIntRads()) {
            isMoving = ElevationController::_elevationMotor->nextStep();
        }

        ElevationController::updateTurretState(isMoving);
    }

    ElevationController::setConditionNeutral();
    Indicator::strobeFast(ARD_STATUS_RED, 100);
    vTaskDelete(ElevationController::elevationTaskHandle);
}

void ElevationController::updateTurretState(boolean isMoving) {

    if (TurretState::elevationState->isMoving && !isMoving) {
        clearIndicators();
        TurretState::elevationState->speed = ElevationSpeed::STOP;
    }
    if (!TurretState::elevationState->isMoving && isMoving) {
        Indicator::turnOnLed(MOVE_LED_GRN);
    }

    TurretState::elevationState->isMoving = isMoving;
    TurretState::elevationState->currentPositionIntRads = getCurrentIntRads();
}

bool ElevationController::moveToIntRads(int intRads, ElevationSpeed speed) {
    int potRdg = map(intRads, ELEVATION_MIN_INTRADS, ELEVATION_MAX_INTRADS, ELEVATION_MIN, ELEVATION_MAX);
    
    return ElevationController::moveTo(potRdg, speed);
}

int ElevationController::getNextMoveToIntRads(int targetIntRads, int stepSize) {
    int currentIntRads = getCurrentIntRads();
    if (abs(targetIntRads - currentIntRads) < stepSize) {
        return targetIntRads;
    }

    if (targetIntRads < currentIntRads) {
        return currentIntRads - stepSize;
    }
    if (targetIntRads > currentIntRads) {
        return currentIntRads + stepSize;
    }
    return targetIntRads;
}

bool ElevationController::functionCheckMoveToTarget() {
    setElevationStateFromCommand();
    ElevationController::moveToIntRads(getTargetIntRads(), TurretState::elevationState->speed);
    boolean hasNextStep = true;
    while (hasNextStep) {
        hasNextStep = ElevationController::_elevationMotor->nextStep();
        Taskr::delayMs(getCurrentDelayMillis());
        updateTurretState(hasNextStep);
    }
    return true;
}

TickType_t ElevationController::getTakeDelay() {
    return Taskr::getMillis(ElevationController::getCurrentDelayMillis());
}

int ElevationController::getCurrentDelayMillis() {

    int delayMillis = MOTOR_UPDATE_INTERVAL;

    switch (TurretState::elevationState->speed) {
        case ElevationSpeed::SLOW:
            delayMillis = 90;
            break;
        case ElevationSpeed::MEDIUM:
            delayMillis = 60;
            break;
        case ElevationSpeed::FAST:
            delayMillis = 45;
            break;
        case ElevationSpeed::JERK:
            delayMillis = 30;
            break;
        default:
            delayMillis = MOTOR_UPDATE_INTERVAL;
    }

    return delayMillis;
}

int ElevationController::getStepSize() {
    return 0;
}

bool ElevationController::canMoveTo(int targetIntRads) {
    return (targetIntRads >= ELEVATION_MIN_INTRADS && targetIntRads <= ELEVATION_MAX_INTRADS);
}

int ElevationController::getCurrentIntRads() {
    long potMotorReading = ElevationController::_elevationMotor->getCurrentPosition();

    int intRads = map(potMotorReading, ELEVATION_MIN, ELEVATION_MAX, ELEVATION_MIN_INTRADS, ELEVATION_MAX_INTRADS);

    return intRads;
}

int ElevationController::getTargetIntRads() {
    if (TurretState::elevationState != nullptr && TurretState::elevationState->targetPositionIntRads != 0) {
        return TurretState::elevationState->targetPositionIntRads;
    }
    return -1;
}

void ElevationController::setElevationStateFromCommand() {
    TurretState::elevationState->speed = TurretState::elevationCommand->commandSpeed;
    TurretState::elevationState->targetPositionIntRads = TurretState::elevationCommand->targetIntRads;
}

