#include "TurretState.h"
#include "TraverseState.h"
#include "ElevationCommand.h"

volatile bool TurretState::allFunctionChecksCompleted = false;
TraverseState_t* TurretState::traverseState = nullptr;
TraverseCommand_t* TurretState::traverseCommand = nullptr;
ElevationState_t* TurretState::elevationState = nullptr;
ElevationCommand_t* TurretState::elevationCommand = nullptr;