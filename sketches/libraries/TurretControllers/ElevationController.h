
#ifndef TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H
#define TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H

#include <Arduino.h>
#include <PotMotor.h>
#include <TurretPins.h>
#include <ElevationConfig.h>

class ElevationController
{
private:
    PotMotor* _elevationMotor;
public:
    ElevationController(/* args */) {
        _elevationMotor = new PotMotor(
            (int)ELEVATION_MOTOR_ENABLE, 
            (int)ELEVATION_MOTOR_POS, 
            (int)ELEVATION_MOTOR_NEG, 
            ELEVATION_MOTOR_POSITION, 
            (int)ELEVATION_MIN, 
            (int)ELEVATION_MAX, 
            (int)ELEVATION_RESOLUTION, 
            (int)MOTOR_MIN_SPEED, 
            (int)MOTOR_MAX_SPEED, 
            (int)MOTOR_MED_SPEED, 
            (int)MOTOR_JERK_SPEED);
        _elevationMotor->setReadingDelay(MOTOR_UPDATE_INTERVAL);

     }
    ~ElevationController() {

     }
};

#endif // TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H

