#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <CannonController.h>
#include <TraverseController.h>
#include <ElevationController.h>
#include <TurretController.h>
#include <HardwareSerial.h>

Servo* traverseServo = new Servo();


// Set configUSE_TASK_NOTIFICATIONS 1

/*
 * When configUSE_TASK_NOTIFICATIONS is set to 1, each task has a Notification State
 * Notification State = Pending | Not-Pending (uint32)
 * When a task receives a notification, its notification state is set to Pending
 * When a task READS its notification, its notification state is set to Not-Pending
 *
 * A task can wait in the Blocked state (with an optional time out) for its notification state
 * to become pending
 */

void setup() {
    Serial.begin(38400);

    traverseServo->attach(TRAVERSE_SERVO);

    TurretController::initialize(traverseServo, &Serial);
}

void loop() {

}
