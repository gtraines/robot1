//
// Created by graham on 10/21/18.
//

#ifndef TURRET_TRAVERSESTATE_H
#define TURRET_TRAVERSESTATE_H

#include "TraverseCommand.h"

typedef struct TRAVERSE_STATE {
    bool isMoving;
    TraverseSpeed speed;
    int targetPositionIntRads;
    int currentPositionIntRads;
} TraverseState_t;

#endif //TURRET_TRAVERSE_STATE_H
