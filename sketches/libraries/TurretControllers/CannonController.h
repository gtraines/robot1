#ifndef ROBOT1__TURRET_CONTROLLERS__IR_CANNON_CONTROLLER__H
#define ROBOT1__TURRET_CONTROLLERS__IR_CANNON_CONTROLLER__H

#include <Arduino.h>
#include <IndicatorConfig.h>
#include <IrConfig.h>
#include <Indicator.h>
#include <TurretPins.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

class CannonController {
public:
    CannonController() {
    }
    ~CannonController() {
        
    }
    void functionCheckDemo(void* pvParameters) {
        
        for (int idx = 0; idx < 2; idx++) {
            Indicator::alertStrobeSlow(CANNON_LED);
            vTaskDelay(500/portTICK_PERIOD_MS);
            Indicator::alertStrobeFast(CANNON_LED);
            vTaskDelay(500/portTICK_PERIOD_MS);
        }
        vTaskDelete(NULL);
    }
};

#endif //ROBOT1__TURRET_CONTROLLERS__IR_CANNON_CONTROLLER__H