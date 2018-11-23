#ifndef ROBOT1__TURRET_CONTROLLERS__CANNON_CONTROLLER__H
#define ROBOT1__TURRET_CONTROLLERS__CANNON_CONTROLLER__H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <IRLibSendBase.h>
#include <IRLib_HashRaw.h>

#include <TurretPins.h>
#include <IndicatorConfig.h>
#include <IrConfig.h>
#include <Indicator.h>

#include <CannonState.h>
#include <CannonCommand.h>

class CannonController {
protected:
    static TickType_t getTakeDelay();
    static void updateTurretState();
    static void setElevationStateFromCommand();
    static bool shouldFire();
    const static uint8_t signalDataLength = 18;
    static uint16_t blueSignal[18];
    static uint16_t redSignal[18];
    static uint16_t purpleSignal[18];
public:
    CannonController() {
    }
    ~CannonController() {
        
    }
    static bool initialize();
    static void functionCheckDemo(void* pvParameters);
    static void dutyCycle(void* pvParameters);
    static bool fireCannon(CannonSignal signal);
    static bool transmitSignal(CannonSignal signal);
    static IRsendRaw* cannon;
    static TaskHandle_t cannonTaskHandle;
};

#endif //ROBOT1__TURRET_CONTROLLERS__IR_CANNON_CONTROLLER__H