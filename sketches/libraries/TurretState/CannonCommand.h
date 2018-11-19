//
// Created by graham on 11/17/18.
//

#ifndef TURRET_CANNONCOMMAND_H
#define TURRET_CANNONCOMMAND_H

#include <Arduino.h>
#include "CommandStatus.h"
#include "CannonState.h"

typedef struct CANNON_COMMAND_TYPE {
    long commandId;
    CannonSignal signalId;
    uint8_t burstLength;
    CommandStatus status;
} CannonCommand_t;


#endif //TURRET_CANNONCOMMAND_H
