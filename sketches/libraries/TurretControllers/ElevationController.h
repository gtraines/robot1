#ifndef TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H
#define TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <ElevationConfig.h>
#include <ElevationCommand.h>
#include <Indicator.h>
#include <PotMotorRtos.h>
#include <TurretPins.h>


class ElevationController
{
protected:
    static void clearIndicators();
    static int getNextMoveToIntRads(int targetIntRads, int stepSize);
    static bool functionCheckMoveToTarget();
    static void updateTurretState(boolean isMoving);
    static void setElevationStateFromCommand();
    static TickType_t getTakeDelay();
    static int getCurrentDelayMillis();
    static int getStepSize();
    static PotMotorRtos* _elevationMotor;
public:
    ElevationController(/* args */) {
    }
    ~ElevationController() {
    }
    static bool initialize();
    static bool canMoveTo(int targetIntRads);
    static bool moveTo(int readingValue, ElevationSpeed speed);
    static void functionCheckDemo(void* pvParameters);
    static bool moveToIntRads(int intRads, ElevationSpeed speed);
    static bool setConditionNeutral();
    static void dutyCycle(void* pvParameters);
    static int getCurrentIntRads();
    static int getTargetIntRads();
    static TaskHandle_t elevationTaskHandle;
};

#endif // TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H
