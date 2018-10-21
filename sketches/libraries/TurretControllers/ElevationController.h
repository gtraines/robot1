
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
    static void clearIndicators();
    static PotMotor* _elevationMotor;
public:
    ElevationController(/* args */) {
    }
    ~ElevationController() {
    }
    static bool initialize();
    static bool moveTo(int readingValue);
    static bool moveToIntRads(int intRads);
    static void functionCheckDemo(void* pvParameters);
    static void dutyCycle(void* pvParameters);
    static bool setConditionNeutral();
    static TaskHandle_t elevationTaskHandle;
};

#endif // TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H
