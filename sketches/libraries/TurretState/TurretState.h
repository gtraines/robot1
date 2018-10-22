#ifndef TURRETSTATE_H
#define TURRETSTATE_H

#include "TraverseState.h"

class TurretState
{
public:
    static volatile bool allFunctionChecksCompleted;
    static volatile int tgtElevationIntRads;
    static traverse_state_t* traverseState;
};

#endif // TURRETSTATE_H
