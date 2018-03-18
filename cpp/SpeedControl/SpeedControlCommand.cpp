#include "SpeedControlCommand.h"
#include "SpeedControlSpeed.h"

SpeedControlCommand::SpeedControlCommand() {
    this->commandIdentifier = commandIdentifier;
    this->speedControlSpeed = SpeedControlSpeed::Stop;
}

SpeedControlCommand::SpeedControlCommand(int speedControlSpeed, unsigned long commandIdentifier) {
    this->commandIdentifier = commandIdentifier;
    this->speedControlSpeed = static_cast<SpeedControlSpeed>(speedControlSpeed);
}

SpeedControlCommand::SpeedControlCommand(int speedControlSpeed) {
    this->commandIdentifier = 0;
    this->speedControlSpeed = static_cast<SpeedControlSpeed>(speedControlSpeed);
}