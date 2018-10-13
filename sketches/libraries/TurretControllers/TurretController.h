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
protected:
    TaskHandle_t _traverseTaskHandle;
    TaskHandle_t _elevationTaskHandle;
    TaskHandle_t _indicatorTaskHandle;
    TaskHandle_t _cannonTaskHandle;
    TraverseController* _traverseCtrl;
    ElevationController* _elevationCtrl;
  public:
    TurretController(Servo* traverseServo) {

        this->setPins();

        this->_traverseCtrl = new TraverseController(traverseServo);
        this->_elevationCtrl = new ElevationController();

        TurretController::turnOffAllIndicators();
        
        TurretController::_cannonTaskHandle = NULL;
        TurretController::_elevationTaskHandle = NULL;
        TurretController::_indicatorTaskHandle = NULL;
        TurretController::_traverseTaskHandle = NULL;
    }
    ~TurretController() { }
    void setStatusGood();
    void setStatusError();
    bool setPins();
    bool turnOffAllIndicators();
    bool setConditionNeutral();
    bool setControlMode(int mode);
    void functionCheckDemo(void* pvParameters);
    void indicatorFunctionCheck(void* pvParameters);
};

#endif // !ROBOT1_TURRET_CONTROLLER__H
