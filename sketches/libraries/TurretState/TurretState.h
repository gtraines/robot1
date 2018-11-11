#ifndef TURRETSTATE_H
#define TURRETSTATE_H

#include "ElevationCommand.h"
#include "ElevationState.h"
#include "TraverseState.h"
#include "TraverseCommand.h"

class TurretState
{
public:
    static volatile bool allFunctionChecksCompleted;
    static volatile int tgtElevationIntRads;
    static TraverseState_t* traverseState;
    static TraverseCommand_t* traverseCommand;
    static ElevationState_t* elevationState;
    static ElevationCommand_t* elevationCommand;
};

#endif // TURRETSTATE_H
