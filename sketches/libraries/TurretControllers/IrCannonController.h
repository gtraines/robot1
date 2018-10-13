#ifndef ROBOT1__TURRET_CONTROLLERS__IR_CANNON_CONTROLLER__H
#define ROBOT1__TURRET_CONTROLLERS__IR_CANNON_CONTROLLER__H

#include <Arduino.h>
#include <IndicatorConfig.h>
#include <IrConfig.h>
#include <Indicator.h>
#include <TurretPins.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

class IrCannonController {
public:
    IrCannonController() {
    }
    ~IrCannonController() {
        
    }
    void demoFunctionCheck() {
        Indicator::strobeFast(CANNON_LED, 10);
        vTaskDelay(1500 / portTICK_PERIOD_MS);
    }
};

#endif //ROBOT1__TURRET_CONTROLLERS__IR_CANNON_CONTROLLER__H