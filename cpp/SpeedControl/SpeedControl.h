//
// Created by graham on 11/18/17.
//

#ifndef SPEEDCONTROL_SPEEDCONTROL_H
#define SPEEDCONTROL_SPEEDCONTROL_H

#include <Arduino.h>
#include <Servo.h>

class SpeedControl {
protected:
    void changeGearDirection(int direction);
    bool commandRequiresDirectionChange(int commandVector);
    bool availableToReceiveCommand();
    bool currentlyInStoppedRange();
    void moveForward(int speed);
    void moveBackward(int speed);
    void haltMotion();

    void accelerateForward(int speed);
    void decelerateForward(int speed);
    void accelerateBackward(int speed);
    void decelerateBackward(int speed);
    void resetOperationClock();
    void calculateOperationSteps();

public:
    void attach(Servo servo, int updateStepSize);

    int commandMove(int directionPower);
    int getCurrentControlStatus();
    int getMillisUntilAvailableForCommand();
    bool setDebug(bool debugModeOn);
    void incrementStep();

};


#endif //SPEEDCONTROL_SPEEDCONTROL_H
