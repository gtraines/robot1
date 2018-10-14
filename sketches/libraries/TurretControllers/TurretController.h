#ifndef ROBOT1__TURRET_CONTROLLER__H
#define ROBOT1__TURRET_CONTROLLER__H

#include <Servo.h>
#include <Indicator.h>
#include <TurretPins.h>
#include <CannonController.h>
#include <ElevationController.h>
#include <TraverseController.h>

class TurretController
{
  public:
    static void initialize(Servo* traverseServo) {

        TurretController::setPins();
        TraverseController::initialize(traverseServo);

        TurretController::turnOffAllIndicators();
    }
    ~TurretController() { }
    static void setStatusGood();
    static void setStatusError();
    static bool setPins();
    static bool turnOffAllIndicators();
    static bool setConditionNeutral();
    static bool setControlMode(int mode);
    static void functionCheckDemo(void* pvParameters);
    static void indicatorFunctionCheck(void* pvParameters);
    static TaskHandle_t _traverseTaskHandle;
    static TaskHandle_t _elevationTaskHandle;
    static TaskHandle_t _indicatorTaskHandle;
    static TaskHandle_t _cannonTaskHandle;
};

#endif // !ROBOT1_TURRET_CONTROLLER__H
