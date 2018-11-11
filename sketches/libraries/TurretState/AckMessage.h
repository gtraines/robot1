//
// Created by graham on 11/10/18.
//

#ifndef TURRET_STATE__ACKMESSAGE__H
#define TURRET_STATE__ACKMESSAGE__H

#include "CommandResult.h"
#include "CommandStatus.h"
#include "CommandRxStatus.h"
#include <Arduino.h>

class AckMessage {
private:
public:
    explicit AckMessage(long cmdId) {
        this->commandId = cmdId;
        this->commandRxStatus = CommandRxStatus::ACK;
        this->commandStatus = CommandStatus::IN_PROGRESS;
        this->description = "OK";
    }
    AckMessage(long cmdId, CommandRxStatus rxStatus, CommandStatus cmdStatus) {
        this->commandId = cmdId;
        this->commandRxStatus = rxStatus;
        this->commandStatus = cmdStatus;
        this->description = "OK";
    }
    AckMessage(long cmdId, CommandRxStatus rxStatus, CommandStatus cmdStatus, String desc) {
        this->commandId = cmdId;
        this->commandRxStatus = rxStatus;
        this->commandStatus = cmdStatus;
        this->description = desc;
    }
    ~AckMessage() {

    }
    long commandId;
    CommandRxStatus commandRxStatus;
    CommandStatus commandStatus;
    String description;
};

typedef struct COMMAND_RESULT_MSG {
    long commandId;
    CommandResult commandResult;
    String description;
} CommandResultMsg_t;

#endif //TURRET_ACKMESSAGE_H
