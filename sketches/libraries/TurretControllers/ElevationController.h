
#ifndef TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H
#define TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H

#include <Arduino.h>
#include <ElevationConfig.h>
#include <Indicator.h>
#include <PotMotor.h>
#include <TurretPins.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

class ElevationController
{
private:
    static PotMotor* _elevationMotor;
public:
    static void initialize(/* args */) {
        ElevationController::_elevationMotor = new PotMotor(
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
        ElevationController::_elevationMotor->setReadingDelay(MOTOR_UPDATE_INTERVAL);

     }
     static bool functionCheckDemo() {
         vTaskDelay(100/portTICK_PERIOD_MS);
        ElevationController::_elevationMotor->moveTo(ELEVATION_MIN);
        ElevationController::_elevationMotor->moveTo(ELEVATION_MAX);
        ElevationController::_elevationMotor->moveTo(ELEVATION_MIN);
        ElevationController::_elevationMotor->moveTo(ELEVATION_MAX);
        ElevationController::_elevationMotor->moveTo(600);
        return true;
     }
     static bool setConditionNeutral();
};

bool ElevationController::setConditionNeutral() {
    ElevationController::_elevationMotor->moveTo(600);
    return true;
}

#endif // TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H
