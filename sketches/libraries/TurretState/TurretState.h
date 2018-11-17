#ifndef TURRETSTATE_H
#define TURRETSTATE_H

#include "CannonState.h"
#include "CannonCommand.h"
#include "ElevationCommand.h"
#include "ElevationState.h"
#include "TraverseState.h"
#include "TraverseCommand.h"

class TurretState
{
public:
    static volatile bool allFunctionChecksCompleted;
    static CannonState_t* cannonState;
    static CannonCommand_t* cannonCommand;
    static ElevationCommand_t* elevationCommand;
    static ElevationState_t* elevationState;
    static TraverseCommand_t* traverseCommand;
    static TraverseState_t* traverseState;
};

#endif // TURRETSTATE_H
