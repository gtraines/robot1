//
// Created by graham on 11/24/18.
//

#ifndef TURRET_IRRXBASE_H
#define TURRET_IRRXBASE_H

#include <Arduino.h>
#include "IRremoteInt.h"

class IrRxBase {
public:
    IrRxBase()= default;
    ~IrRxBase()= default;
    static bool addReceiverInterrupt(uint16_t interrupt, String name);
    static uint16_t* processSignalsIn(uint8_t interrupt);
    static void processSignalsIn(irparams_t &irParams);
    static void processFallingInterrupt(irparams_t &irParams);
    static void processRisingInterrupt(irparams_t &irParams);
};


#endif //TURRET_IRRXBASE_H
