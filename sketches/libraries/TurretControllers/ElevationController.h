
#ifndef TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H
#define TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <ElevationConfig.h>
#include <Indicator.h>
#include <PotMotor.h>
#include <TurretPins.h>


class ElevationController
{
protected:
    static PotMotor* _elevationMotor;
public:
    ElevationController(/* args */) {
    }
    ~ElevationController() {
    }
    static bool initialize();
    static void functionCheckDemo(void* pvParameters);
    static bool setConditionNeutral();
};

#endif // TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H
