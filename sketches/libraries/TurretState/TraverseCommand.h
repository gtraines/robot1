#ifndef TURRET_STATE__TRAVERSE_COMMAND__H
#define TURRET_STATE__TRAVERSE_COMMAND__H

#include "CommandStatus.h"

enum class TraverseSpeed {
    SLOW,
    MEDIUM,
    FAST,
    STOP
};

enum class TraverseDirection {
    RIGHT = -1,
    LEFT = 1,
};

typedef struct TRAVERSE_COMMAND {
    long commandId;
    TraverseSpeed commandSpeed;
    int targetIntRads;
    CommandStatus status;
} TraverseCommand_t;

#endif
