//
// Created by graham on 11/17/18.
//

#ifndef TURRET_CANNONSTATE_H
#define TURRET_CANNONSTATE_H


#include <Arduino.h>

enum class CannonSignal {
    BLUE,
    RED,
    PURPLE
};

typedef struct CANNON_STATE_TYPE {
    bool isFiring;
    CannonSignal signalId = CannonSignal::PURPLE;
    uint8_t burstIndex;
    uint8_t burstLength;
} CannonState_t;


#endif //TURRET_CANNONSTATE_H
