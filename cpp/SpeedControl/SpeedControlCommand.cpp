#include "SpeedControlCommand.h"
#include "SpeedControlSpeed.h"
SpeedControlCommand::SpeedControlCommand() {}
SpeedControlCommand::~SpeedControlCommand() {}
SpeedControlCommand::SpeedControlCommand(int speedControlSpeed, long commandIdentifier=0) {
    commandIdentifier = commandIdentifier;
    speedControlSpeed = static_cast<SpeedControlSpeed>(speedControlSpeed);
}
