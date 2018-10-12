#ifndef ROBOT1__TURRET_CONTROLLER__H
#define ROBOT1__TURRET_CONTROLLER__H

#include <Servo.h>
#include <Indicator.h>
#include <TurretPins.h>
#include <IrCannonController.h>
#include <ElevationController.h>
#include <TraverseController.h>

class TurretController
{
  public:
    static void initialize(Servo* traverseServo) {

        TurretController::setPins();

        TraverseController::initialize(traverseServo);
        ElevationController::initialize();

        TurretController::turnOffAllIndicators();
    }
    static void setStatusGood();
    static void setStatusError();
    static bool setPins();
    static bool turnOffAllIndicators();
    static bool setConditionNeutral();
    static bool setControlMode(int mode);
    static bool functionCheckDemo();
    static bool indicatorFunctionCheck();
    static void cannonFunctionCheck(void* pvParameters);
    static void elevationFunctionCheck(void* pvParameters);
    static void indicatorFunctionCheck(void* pvParameters);
    static void traverseFunctionCheck(void* pvParameters);
};

#endif // !ROBOT1_TURRET_CONTROLLER__H
