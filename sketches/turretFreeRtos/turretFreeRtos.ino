#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <CannonController.h>
#include <TraverseController.h>
#include <ElevationController.h>
#include <TurretController.h>

Servo* traverseServo = new Servo();

void setup() {
    traverseServo->attach(TRAVERSE_SERVO);

    TurretController::initialize(traverseServo);

    TurretController::functionCheckDemo(NULL);
}

void loop() {

}
