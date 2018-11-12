#include "CannonController.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>

#include <IndicatorConfig.h>
#include <Taskr.h>
#include <IrConfig.h>
#include <Indicator.h>
#include <TurretPins.h>
#include <TurretTasks.h>


TaskHandle_t CannonController::cannonTaskHandle = NULL;

void CannonController::functionCheckDemo(void* pvParameters) {

    for (int idx = 0; idx < 6; idx++) {
        Indicator::alertStrobeFast(CANNON_LED);
        vTaskDelay(600/portTICK_PERIOD_MS);
    }
    BaseType_t notifyMonitorSuccess = xTaskNotifyGive(TurretTasks::functionCheckMonitorHandle);
    
    if (notifyMonitorSuccess == pdTRUE) {
        vTaskDelete(CannonController::cannonTaskHandle);
    }
    else {
        Indicator::turnOnLed(ARD_STATUS_RED);
    }
    
}

bool CannonController::initialize() {
    Indicator::turnOffLed(CANNON_LED);

    BaseType_t cannonStatus = xTaskCreate(
            CannonController::dutyCycle,
            (const portCHAR *) "CannonControllerTask",
            128,  // Stack size
            NULL,
            1,  // Priority
            &CannonController::cannonTaskHandle);

    return true;
}

void CannonController::dutyCycle(void *pvParameters) {

    bool success = true;
    uint32_t receivedValue = 0;

    while (success) {
        receivedValue = ulTaskNotifyTake(pdTRUE, getTakeDelay());

        if (receivedValue != 0) {
            receivedValue = 0;
            Indicator::alertStrobeFast(CANNON_LED);
        }

    }

}

TickType_t CannonController::getTakeDelay() {
    return Taskr::getMillis(90);
}
