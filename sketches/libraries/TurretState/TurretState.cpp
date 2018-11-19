#include "TurretState.h"
#include "TraverseState.h"
#include "ElevationCommand.h"
#include "CannonState.h"
#include "CannonCommand.h"

volatile bool TurretState::allFunctionChecksCompleted = false;
CannonState_t* TurretState::cannonState = nullptr;
CannonCommand_t* TurretState::cannonCommand = nullptr;
ElevationState_t* TurretState::elevationState = nullptr;
ElevationCommand_t* TurretState::elevationCommand = nullptr;
TraverseState_t* TurretState::traverseState = nullptr;
TraverseCommand_t* TurretState::traverseCommand = nullptr;
