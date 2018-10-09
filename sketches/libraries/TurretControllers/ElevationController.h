
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
    PotMotor* _elevationMotor;
public:
    ElevationController(/* args */) {
        this->_elevationMotor = new PotMotor(
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
        this->_elevationMotor->setReadingDelay(MOTOR_UPDATE_INTERVAL);

     }
    ~ElevationController() {

     }
     bool functionCheckDemo() {
         vTaskDelay(100/portTICK_PERIOD_MS);
        this->_elevationMotor->moveTo(ELEVATION_MIN);
        this->_elevationMotor->moveTo(ELEVATION_MAX);
        this->_elevationMotor->moveTo(ELEVATION_MIN);
        this->_elevationMotor->moveTo(ELEVATION_MAX);
        this->_elevationMotor->moveTo(600);
        return true;
     }
     bool setConditionNeutral();
};

bool ElevationController::setConditionNeutral() {
    this->_elevationMotor->moveTo(600);
    return true;
}

#endif // TURRET_CONTROLLERS__ELEVATION_CONTROLLER__H
