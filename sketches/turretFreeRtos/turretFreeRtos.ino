#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <TraverseController.h>
#include <ElevationController.h>
#include <TurretController.h>

Servo* traverseServo;
TaskHandle_t turretControllerTaskHandle = NULL;
TurretController* turretCtrl;
void setup() {

    traverseServo = new Servo();
    turretCtrl = new TurretController(traverseServo);
    
    xTaskCreate(
        turretCtrl->turretCtrl,
        (const portCHAR *) "TurretFunctionCheck",
        1024,  // Stack size
        NULL,
        3,  // Priority
        &turretControllerTaskHandle);
}

void loop() {

}





