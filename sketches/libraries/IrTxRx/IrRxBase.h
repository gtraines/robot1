//
// Created by graham on 11/24/18.
//

#ifndef TURRET_IRRXBASE_H
#define TURRET_IRRXBASE_H

#include <Arduino.h>
#include "IrInterruptConfig.h"
#include "IrParams.h"

class IrRxBase {
public:
    IrRxBase()= default;
    ~IrRxBase()= default;
    static bool addReceiverInterrupt(uint16_t interrupt, String name);
    static uint16_t* processSignalsIn(uint8_t interrupt);
    static void processSignalsIn(IrParams_t &irParams);
    static void resume(IrParams_t &irParams);
    static void processFallingInterrupt(IrParams_t &irParams);
    static void processRisingInterrupt(IrParams_t &irParams);
};


#endif //TURRET_IRRXBASE_H
