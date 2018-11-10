#ifndef TURRET_STATE__COMMAND_MESSSAGES__H
#define TURRET_STATE__COMMAND_MESSAGES__H

#include <Arduino.h>

enum class CommandRxStatus {
    ACK,
    NACK
};

enum class CommandStatus {
    IN_PROGRESS,
    UNABLE_TO_COMPLY,
    ON_HOLD,
    CANCELED
};

enum class CommandResult {
    COMPLETED,
    CANCELED_BY_MCU,
    CANCELED_BY_REQUEST,
    ERROR,
};

typedef struct COMMAND_RESULT {
    long commandId;
    CommandResult commandResult;
    String description;
} CommandResultMsg_t;

class AckMessage {
public:
    AckMessage(long cmdId) {
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

#endif //TURRET_STATE__COMMAND_MESSAGES__H