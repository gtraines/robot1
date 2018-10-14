#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <TraverseController.h>
#include <ElevationController.h>
#include <TurretController.h>

Servo* traverseServo = new Servo();
TurretController* turretCtrl = new TurretController();
TraverseController* traverseCtrl = new TraverseController();
ElevationController* elevCtrl = new ElevationController();

TaskHandle_t turretControllerTaskHandle = NULL;

void setup() {
    traverseServo->attach(TRAVERSE_SERVO);
    
    TurretController::initialize(traverseServo);
    TraverseController::initialize(traverseServo);
    ElevationController::initialize();
    
    TurretController::functionCheckDemo(NULL);
}

void loop() {

}

BaseType_t vFunctionCheckDemo() {
    if (xTaskCreate(
        TraverseController::functionCheckDemo,
        (const portCHAR *) "TraverseFunctionCheck",
        128, //Stack size
        NULL,
        3,  // Priority
        &turretControllerTaskHandle) != pdPASS) {
            TurretController::setStatusError();
        }
}
  

