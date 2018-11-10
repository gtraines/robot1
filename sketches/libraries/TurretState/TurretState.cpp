#include "TurretState.h"
#include "TraverseState.h"

volatile bool TurretState::allFunctionChecksCompleted = false;
volatile int TurretState::tgtElevationIntRads = 0;
TraverseState_t* TurretState::traverseState = nullptr;