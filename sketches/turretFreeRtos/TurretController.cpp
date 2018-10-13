//
// Created by graham on 10/6/18.
//
#include "TurretController.h"
#include <TurretPins.h>

#include <Arduino.h>
#include <Servo.h>

#include <Indicator.h>
#include <IrCannonController.h>
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

bool TurretController::functionCheckDemo() {
    
    return false;
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

bool TurretController::indicatorFunctionCheck() {

    Indicator::alertBlinkFast(ACTY_LED_1);
    Indicator::alertBlinkFast(ACTY_LED_2);
    Indicator::alertBlinkFast(ACTY_LED_3);

    Indicator::alertStrobeSlow(MOVE_LED_GRN);
    Indicator::alertStrobeSlow(MOVE_LED_RED);
    Indicator::alertStrobeSlow(MOVE_LED_BLUE);

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

bool TurretController::setConditionNeutral() {

    xTaskCreate(
      TurretController::TaskConditionNeutral,
      , (const portCHAR *) "ConditionNeutral"
      , 128  // Stack size
      , NULL
      , 1  // Priority
      , &xTaskHandleConditionNeutral);
         
    return true;
}

void TurretController::TaskConditionNeutral(void* pvParameters) {
    this->_elevationController->setConditionNeutral();
    this->_traverseController->setConditionNeutral();

    vTaskDelete(xTaskHandleConditionNeutral);
}

