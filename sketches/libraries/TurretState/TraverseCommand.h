#ifndef TURRET_STATE__TRAVERSE_COMMAND__H
#define TURRET_STATE__TRAVERSE_COMMAND__H

enum class TraverseSpeed {
    SLOW,
    MED,
    FAST
};

typedef struct TRAVERSE_COMMAND {
    long commandId;
    TraverseSpeed commandSpeed;
    int commandTargetIntRads;
} TraverseCommand_t;

#endif
