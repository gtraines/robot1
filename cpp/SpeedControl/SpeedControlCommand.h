#ifndef SPEEDCONTROL_SPEEDCONTROLCOMMAND_H
#define SPEEDCONTROL_SPEEDCONTROLCOMMAND_H

#include "SpeedControlSpeed.h"

class SpeedControlCommand {
public:
    SpeedControlCommand();
    ~SpeedControlCommand() = default;
    explicit SpeedControlCommand(int speedControlSpeed);
    SpeedControlCommand(int speedControlSpeed, unsigned long commandIdentifier);
    unsigned long commandIdentifier;
    SpeedControlSpeed speedControlSpeed;
};

 #endif // !SPEEDCONTROL_SPEEDCONTROLCOMMAND_H
