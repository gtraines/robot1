#include "SpeedControlCommand.h"
#include "InternalOperation.h"

typedef struct {
    unsigned long targetCommandIdentifier;
    unsigned long currentCommandIdentifier;
    int targetCommandSpeed;
    int currentCommandSpeed;
    int currentServoSignal;
    int operationStepsClockValue;
} SpeedControlStatus;