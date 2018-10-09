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


TraverseController::TraverseController() {

    this->servoMaxPosition = TRAVERSE_LIMIT_MAX;
    this->servoMinPosition = TRAVERSE_LIMIT_MIN;
    this->servoStraightPosition = TRAVERSE_LIMIT_STRAIGHT;
    Indicator::turnOnLed(ACTY_LED_1);
}

TraverseController::TraverseController(Servo *traverseServo) : TraverseController::TraverseController() {
    this->traverseServo = traverseServo;

    Indicator::turnOnLed(ACTY_LED_3);

    delay(15);

    this->setNeutralCondition();
    Indicator::turnOnLed(ACTY_LED_2);
}

TraverseController::~TraverseController() {

}

void TraverseController::functionCheckDemo() {
    int travPos = 0;
    for(travPos = this->servoStraightPosition; travPos < this->servoMaxPosition; travPos++) {
        this->moveTo(travPos, TRAVERSE_MOVE_DELAY);
    }

    for(travPos = this->servoMaxPosition; travPos > this->servoMinPosition; travPos--) {
        this->moveTo(travPos, TRAVERSE_MOVE_DELAY);
    }

    for(travPos = this->servoMinPosition; travPos < this->servoStraightPosition; travPos++) {
        this->moveTo(travPos, TRAVERSE_MOVE_DELAY);
    }
}

bool TraverseController::canMoveTo(int targetPosition) {
    return false;
}

bool TraverseController::moveTo(int targetPosition, int delayMillis) {
    Indicator::turnOffLed(ARD_STATUS_RED);
    Indicator::turnOffLed(MOVE_LED_BLUE);
    Indicator::turnOffLed(MOVE_LED_GRN);
    if (targetPosition < this->servoMinPosition) {
        Indicator::turnOnLed(ARD_STATUS_RED);
        targetPosition = this->servoMinPosition;
    }

    if (targetPosition > this->servoMaxPosition) {
        Indicator::turnOnLed(MOVE_LED_BLUE);
        targetPosition = this->servoMaxPosition;
    }

    this->traverseServo->write(targetPosition);

    Indicator::turnOnLed(MOVE_LED_GRN);
    vTaskDelay(delayMillis/portTICK_PERIOD_MS);

    return false;
}

bool TraverseController::setConditionNeutral(){
    this->traverseServo->write(TRAVERSE_LIMIT_STRAIGHT);
    delay(30);
    return true;
}

