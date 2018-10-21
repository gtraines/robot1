#ifndef TURRETSTATE_H
#define TURRETSTATE_H

class TurretState
{
public:
    static volatile bool allFunctionChecksCompleted;
    static volatile int tgtElevationIntRads;
    static volatile int tgtTraverseIntRads;
};

#endif // TURRETSTATE_H
