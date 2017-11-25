#ifndef SPEEDCONTROL_SPEEDCONTROLCOMMAND_H
#define SPEEDCONTROL_SPEEDCONTROLCOMMAND_H

#include "SpeedControlSpeed.h"

class SpeedControlCommand {
public:
    SpeedControlCommand();
    ~SpeedControlCommand();
    SpeedControlCommand(int speedControlSpeed, long commandIdentifier=0);
    unsigned long commandIdentifier;
    SpeedControlSpeed speedControlSpeed;
};

 #endif // !SPEEDCONTROL_SPEEDCONTROLCOMMAND_H
