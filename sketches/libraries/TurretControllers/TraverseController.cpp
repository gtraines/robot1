//
// Created by graham on 10/7/18.
//
#include "TraverseController.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Indicator.h>
#include <TurretPins.h>
#include <TraverseConfig.h>
#include <Servo.h>


void TraverseController::initialize(Servo *traverseServo) {

    TraverseController::servoMaxPosition = TRAVERSE_LIMIT_MAX;
    TraverseController::servoMinPosition = TRAVERSE_LIMIT_MIN;
    TraverseController::servoStraightPosition = TRAVERSE_LIMIT_STRAIGHT;
    Indicator::turnOnLed(ACTY_LED_1);
    TraverseController::traverseServo = traverseServo;

    Indicator::turnOnLed(ACTY_LED_3);

    delay(15);

    TraverseController::setConditionNeutral();
    Indicator::turnOnLed(ACTY_LED_2);
}

void TraverseController::functionCheckDemo() {
    int travPos = 0;
    for (travPos = TraverseController::servoStraightPosition; travPos < TraverseController::servoMaxPosition; travPos++) {
        TraverseController::moveTo(travPos, TRAVERSE_MOVE_DELAY);
    }

    for (travPos = TraverseController::servoMaxPosition; travPos > TraverseController::servoMinPosition; travPos--) {
        TraverseController::moveTo(travPos, TRAVERSE_MOVE_DELAY);
    }

    for (travPos = TraverseController::servoMinPosition; travPos < TraverseController::servoStraightPosition; travPos++) {
        TraverseController::moveTo(travPos, TRAVERSE_MOVE_DELAY);
    }
}

bool TraverseController::canMoveTo(int targetPosition) {
    return false;
}

bool TraverseController::moveTo(int targetPosition, int delayMillis) {
    Indicator::turnOffLed(ARD_STATUS_RED);
    Indicator::turnOffLed(MOVE_LED_BLUE);
    Indicator::turnOffLed(MOVE_LED_GRN);

    if (targetPosition < TraverseController::servoMinPosition) {
        Indicator::turnOnLed(ARD_STATUS_RED);
        targetPosition = TraverseController::servoMinPosition;
    }

    if (targetPosition > TraverseController::servoMaxPosition) {
        Indicator::turnOnLed(MOVE_LED_BLUE);
        targetPosition = TraverseController::servoMaxPosition;
    }

    TraverseController::traverseServo->write(targetPosition);

    Indicator::turnOnLed(MOVE_LED_GRN);
    vTaskDelay(delayMillis/portTICK_PERIOD_MS);

    return false;
}

bool TraverseController::setConditionNeutral(){
    TraverseController::traverseServo->write(TRAVERSE_LIMIT_STRAIGHT);
    delay(30);
    return true;
}

