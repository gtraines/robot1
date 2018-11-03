#ifndef ROBOT1__TURRET_CONTROLLER__H
#define ROBOT1__TURRET_CONTROLLER__H

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Servo.h>
#include <Indicator.h>
#include <TurretPins.h>
#include <CannonController.h>
#include <ElevationController.h>
#include <TraverseController.h>

class TurretController
{
  public:
    static void initialize(Servo* traverseServo);
    ~TurretController() { }
    static void setStatusGood();
    static void setStatusError();
    static bool setTraverseTargetIntRads(int tgtIntRads);
    static bool setElevationTargetIntRads(int tgtIntRads);
    static bool incrementTraverse(int direction, int intRads, int speed);
    static bool incrementElevation(int direction, int intRads, int speed);
    static bool setPins();
    static bool turnOffAllIndicators();
    static bool setConditionNeutral();
    static bool setControlMode(int mode);
    static void functionCheckDemo(void* pvParameters);
    static void indicatorFunctionCheck(void* pvParameters);
    static TaskHandle_t indicatorTaskHandle;
};

#endif // !ROBOT1_TURRET_CONTROLLER__H
