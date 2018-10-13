//
// Created by graham on 10/6/18.
//
#include "TurretController.h"
#include <TurretPins.h>

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <Servo.h>

#include <Indicator.h>
#include <CannonController.h>
#include <ElevationController.h>
#include <TraverseController.h>


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

bool TurretController::setConditionNeutral() {
    return true;
}

void TurretController::functionCheckDemo(void* pvParameters) {
    xTaskCreate(
        TraverseController::functionCheckDemo,
        (const portCHAR *) "TraverseTest",
        512,  // Stack size
        NULL,
        1,  // Priority
        &TurretController::_traverseTaskHandle);

    xTaskCreate(
        TurretController::indicatorFunctionCheck,
        (const portCHAR *) "IndicatorTest",
        128,  // Stack size
        NULL,
        1, // Priority
        &TurretController::_indicatorTaskHandle);

    xTaskCreate(
        ElevationController::functionCheckDemo,
        (const portCHAR *) "ElevationTest",
        512,  // Stack size
        NULL,
        1,  // Priority
        &TurretController::_elevationTaskHandle);

    xTaskCreate(
        CannonController::functionCheckDemo,
        (const portCHAR *) "CannonTest",
        128,  // Stack size
        NULL,
        1,  // Priority
        &TurretController::_cannonTaskHandle);

    vTaskDelete(NULL);
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

void TurretController::indicatorFunctionCheck(void* pvParameters) {

    Indicator::alertBlinkFast(ACTY_LED_1);
    Indicator::alertBlinkFast(ACTY_LED_2);
    Indicator::alertBlinkFast(ACTY_LED_3);

    Indicator::alertStrobeSlow(MOVE_LED_GRN);
    Indicator::alertStrobeSlow(MOVE_LED_RED);
    Indicator::alertStrobeSlow(MOVE_LED_BLUE);

    vTaskDelete(NULL);
    return true;
}

void TurretController::setStatusGood() {
    Indicator::turnOffLed(ARD_STATUS_RED);
    Indicator::turnOnLed(ARD_STATUS_GRN);
}

void TurretController::setStatusError() {
    Indicator::turnOffLed(ARD_STATUS_GRN);
    Indicator::turnOnLed(ARD_STATUS_RED);
}
