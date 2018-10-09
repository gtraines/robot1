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
  private:
    ElevationController* _elevationController;
    TraverseController* _traverseController;
  public:
    explicit TurretController(Servo* traverseServo) {

        this->setPins();

        _traverseController = new TraverseController(traverseServo);
        _elevationController = new ElevationController();

        turnOffAllIndicators();
    }
    ~TurretController() {
        delete _elevationController;
        delete _traverseController;
    }
    void setStatusGood();
    void setStatusError();
    bool setPins();
    bool turnOffAllIndicators();
    bool setConditionNeutral();
    bool setControlMode(int mode);
    bool functionCheckDemo();
    bool indicatorFunctionCheck();
    static void cannonFunctionCheck(void* pvParameters);
    static void elevationFunctionCheck(void* pvParameters);
    static void indicatorFunctionCheck(void* pvParameters);
    static void traverseFunctionCheck(void* pvParameters);
};

#endif // !ROBOT1_TURRET_CONTROLLER__H