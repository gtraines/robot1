#include "TurretState.h"


volatile bool TurretState::allFunctionChecksCompleted = false;
volatile int TurretState::tgtElevationIntRads = 0;
volatile int TurretState::tgtTraverseIntRads = 0;