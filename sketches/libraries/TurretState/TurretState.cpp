#include "TurretState.h"
#include "TraverseState.h"

volatile bool TurretState::allFunctionChecksCompleted = false;
volatile int TurretState::tgtElevationIntRads = 0;
traverse_state_t* TurretState::traverseState = nullptr;