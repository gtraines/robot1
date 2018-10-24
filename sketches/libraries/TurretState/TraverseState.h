//
// Created by graham on 10/21/18.
//

#ifndef TURRET_TRAVERSESPEED_H
#define TURRET_TRAVERSESPEED_H

enum class TraverseSpeed {
    SLOW,
    MED,
    FAST
};

typedef struct TRAVERSE_STATE_TYPE {
    bool isMoving;
    TraverseSpeed speed;
    int targetPositionIntRads;
    int currentPositionIntRads;
} traverse_state_t;

#endif //TURRET_TRAVERSESPEED_H
