//
// Created by graham on 11/17/18.
//

#ifndef TURRET_CANNONSTATE_H
#define TURRET_CANNONSTATE_H


#include <Arduino.h>

typedef struct CANNON_STATE_TYPE {
    bool isFiring;
    uint8_t signalId;
    uint8_t burstIndex;
    uint8_t burstLength;
} CannonState_t;


#endif //TURRET_CANNONSTATE_H
