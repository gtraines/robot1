#ifndef SPEEDCONTROL_SPEEDCONTROLCOMMAND_H
#define SPEEDCONTROL_SPEEDCONTROLCOMMAND_H

#include "SpeedControlSpeed.h"

class SpeedControlCommand {
public:
    SpeedControlCommand(int speedControlSpeed, long commandIdentifier=0);
    unsigned long commandIdentifier;
    SpeedControlSpeed speedControlSpeed;
};

SpeedControlCommand::SpeedControlCommand(int speedControlSpeed, long commandIdentifier=0) {
    commandIdentifier = commandIdentifier;
    speedControlSpeed = static_cast<SpeedControlSpeed>(speedControlSpeed);
}

 #endif // !SPEEDCONTROL_SPEEDCONTROLCOMMAND_H
