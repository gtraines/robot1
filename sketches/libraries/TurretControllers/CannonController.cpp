#include "CannonController.h"
#include <Arduino.h>
#include <IndicatorConfig.h>
#include <IrConfig.h>
#include <Indicator.h>
#include <TurretPins.h>
#include <TurretTasks.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

TaskHandle_t CannonController::cannonTaskHandle = NULL;

void CannonController::functionCheckDemo(void* pvParameters) {

    for (int idx = 0; idx < 6; idx++) {
        Indicator::alertStrobeFast(CANNON_LED);
        vTaskDelay(600/portTICK_PERIOD_MS);
    }
    BaseType_t notifyExecutiveSuccess = xTaskNotifyGive(TurretTasks::functionCheckMonitorHandle);
    vTaskDelete(CannonController::cannonTaskHandle);
}

bool CannonController::initialize() {
    Indicator::turnOffLed(CANNON_LED);
}
