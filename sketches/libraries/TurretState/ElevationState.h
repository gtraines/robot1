//
// Created by graham on 11/10/18.
//

#ifndef TURRET_ELEVATIONSTATE_H
#define TURRET_ELEVATIONSTATE_H

#include "ElevationCommand.h"

typedef struct ELEVATION_STATE_TYPE {
    bool isMoving;
    ElevationSpeed speed;
    int targetPositionIntRads;
    int currentPositionIntRads;
} ElevationState_t;

#endif //TURRET_ELEVATIONSTATE_H
