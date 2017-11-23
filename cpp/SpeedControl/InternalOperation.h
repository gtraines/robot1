#ifndef SPEEDCONTROL_INTERNALOPERATION_H
#define SPEEDCONTROL_INTERNALOPERATION_H

#include "SpeedControlOperation.h"
class InternalOperation    
{
public:
    InternalOperation();
    ~InternalOperation();
    SpeedControlOperation speedControlOperation;
    int operationServoSignal;
    int incrementsToWaitBeforeNextOperation;
private:

};

InternalOperation::InternalOperation()
{
}

InternalOperation::~InternalOperation()
{
}

#endif // !SPEEDCONTROL_INTERNALOPERATION_H

