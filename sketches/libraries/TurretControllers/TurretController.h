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
    TraverseController* _traverseController;
    ElevationController* _elevationController;
  public:
    TurretController(Servo* traverseServo) {

        this->setPins();

        this->_traverseController = new TraverseController(traverseServo);
        this->_elevationController = new ElevationController();

        this->turnOffAllIndicators();
    }
    ~TurretController() { }
    void setStatusGood();
    void setStatusError();
    bool setPins();
    bool turnOffAllIndicators();
    bool setConditionNeutral();
    bool setControlMode(int mode);
    bool functionCheckDemo();
    bool indicatorFunctionCheck();
    void cannonFunctionCheck(void* pvParameters);
    void elevationFunctionCheck(void* pvParameters);
    void indicatorFunctionCheck(void* pvParameters);
    void traverseFunctionCheck(void* pvParameters);
};

#endif // !ROBOT1_TURRET_CONTROLLER__H
