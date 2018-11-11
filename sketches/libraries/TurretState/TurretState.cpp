#include "TurretState.h"
#include "TraverseState.h"
#include "ElevationCommand.h"

volatile bool TurretState::allFunctionChecksCompleted = false;
volatile int TurretState::tgtElevationIntRads = 0;
TraverseState_t* TurretState::traverseState = nullptr;
TraverseCommand_t* TurretState::traverseCommand = nullptr;
ElevationCommand_t* TurretState::elevationCommand = nullptr;