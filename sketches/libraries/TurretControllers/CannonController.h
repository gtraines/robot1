#ifndef ROBOT1__TURRET_CONTROLLERS__CANNON_CONTROLLER__H
#define ROBOT1__TURRET_CONTROLLERS__CANNON_CONTROLLER__H

#include <Arduino.h>
#include <IndicatorConfig.h>
#include <IrConfig.h>
#include <Indicator.h>
#include <TurretPins.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

class CannonController {
protected:
    static TickType_t getTakeDelay();
public:
    CannonController() {
    }
    ~CannonController() {
        
    }
    static bool initialize();
    static void functionCheckDemo(void* pvParameters);
    static void dutyCycle(void* pvParameters);
    static void fireCannon(int signalId, int burstLength);
    static TaskHandle_t cannonTaskHandle;
};

#endif //ROBOT1__TURRET_CONTROLLERS__IR_CANNON_CONTROLLER__H