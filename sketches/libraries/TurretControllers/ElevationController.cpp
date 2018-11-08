#include "ElevationController.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Taskr.h>
#include <ElevationConfig.h>
#include <Indicator.h>
#include <PotMotor.h>
#include <TurretPins.h>
#include <TurretState.h>
#include <TurretTasks.h>

PotMotor* ElevationController::_elevationMotor = nullptr;
TaskHandle_t ElevationController::elevationTaskHandle = NULL;

bool ElevationController::initialize() {
    ElevationController::_elevationMotor = new PotMotor(
            (int)ELEVATION_MOTOR_ENABLE,
            (int)ELEVATION_MOTOR_POS,
            (int)ELEVATION_MOTOR_NEG,
            ELEVATION_MOTOR_POSITION,
            (int)ELEVATION_MIN,
            (int)ELEVATION_MAX,
            (int)ELEVATION_RESOLUTION,
            (int)MOTOR_MIN_SPEED,
            (int)MOTOR_MAX_SPEED,
            (int)MOTOR_MED_SPEED,
            (int)MOTOR_JERK_SPEED);
    ElevationController::_elevationMotor->setReadingDelay(MOTOR_UPDATE_INTERVAL);
}

void ElevationController::functionCheckDemo(void* pvParameters) {
    TurretState::tgtElevationIntRads = FUNCTION_CHECK_TGT_INTRADS;
    ElevationController::setConditionNeutral();
    Taskr::delayMs(800);
    ElevationController::moveToIntRads(ELEVATION_MIN_INTRADS);
    Taskr::delayMs(500);
    ElevationController::moveToIntRads(ELEVATION_MAX_INTRADS);
    Taskr::delayMs(500);
    ElevationController::moveToIntRads(ELEVATION_MIN_INTRADS);
    Taskr::delayMs(500);
    ElevationController::moveToIntRads(ELEVATION_MAX_INTRADS);
    Taskr::delayMs(500);
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
    
    ElevationController::_elevationMotor->moveTo(readingValue);
    ElevationController::clearIndicators();
    
    return isGoodCommand;
}


void ElevationController::dutyCycle(void* pvParameters) {
    
}

bool ElevationController::moveToIntRads(int intRads) {
    int potRdg = map(intRads, ELEVATION_MIN_INTRADS, ELEVATION_MAX_INTRADS, ELEVATION_MIN, ELEVATION_MAX);
    
    return ElevationController::moveTo(potRdg);
}

int ElevationController::getNextMoveToIntRads(int targetIntRads, int stepSize) {
}

bool ElevationController::functionCheckSpeedDemo() {
}

bool ElevationController::functionCheckMoveToTarget() {
}

void ElevationController::updateTurretState(int currentIntRads) {
}

TickType_t ElevationController::getTakeDelay()
{
}

int ElevationController::getCurrentDelayMillis()
{
}

int ElevationController::getStepSize()
{
}

bool ElevationController::canMoveTo(int targetIntRads) {
    return (targetIntRads >= ELEVATION_MIN_INTRADS && targetIntRads <= ELEVATION_MAX_INTRADS);
}

bool ElevationController::moveToIntRads(int intRads, int delayMillis)
{
}

int ElevationController::getCurrentIntRads()
{
}

int ElevationController::getTargetIntRads()
{
}
