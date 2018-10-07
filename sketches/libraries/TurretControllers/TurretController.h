#ifndef ROBOT1__TURRET_CONTROLLER__H
#define ROBOT1__TURRET_CONTROLLER__H

#include <Indicator.h>
#include <TurretPins.h>
#include <IrCannonController.h>
#include <ElevationController.h>
#include <TraverseController.h>

class TurretController
{
  private:
    /* data */
  public:
    TurretController(/* args */) {

    }
    ~TurretController() {}
    bool setPins();
    bool setConditionNeutral();
    bool setControlMode(int mode);
    bool functionCheckDemo();
};

#endif // !ROBOT1_TURRET_CONTROLLER__H