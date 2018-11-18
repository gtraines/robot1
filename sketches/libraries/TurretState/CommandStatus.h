//
// Created by graham on 11/10/18.
//

#ifndef TURRET_COMMANDSTATUS_H
#define TURRET_COMMANDSTATUS_H

enum class CommandStatus {
    IN_PROGRESS,
    COMPLETE,
    UNABLE_TO_COMPLY,
    ON_HOLD,
    CANCELED
};
#endif //TURRET_COMMANDSTATUS_H
