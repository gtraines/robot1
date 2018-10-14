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
TurretController* turretCtrl = new TurretController();
TraverseController* traverseCtrl = new TraverseController();
ElevationController* elevCtrl = new ElevationController();
CannonController* cannonController = new CannonController();

TaskHandle_t turretControllerTaskHandle = NULL;

void setup() {
    traverseServo->attach(TRAVERSE_SERVO);
    TraverseController::initialize(traverseServo);
    ElevationController::initialize();
    CannonController::initialize();

    TurretController::initialize(traverseServo);
    
    
    TurretController::functionCheckDemo(NULL);
}

void loop() {

}
