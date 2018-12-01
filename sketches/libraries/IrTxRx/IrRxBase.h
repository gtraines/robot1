//
// Created by graham on 11/24/18.
//

#ifndef TURRET_IRRXBASE_H
#define TURRET_IRRXBASE_H

#include <Arduino.h>
#include "IrInterruptConfig.h"
#include "IrParams.h"
#include "decode_results.h"

class IrRxBase {
public:
    IrRxBase()= default;
    ~IrRxBase()= default;
    static void processSignalsIn(IrParams_t &irParams);
    static void resume(IrParams_t &irParams);
    static long decodeHash(decode_results *results);
    static int decode(IrParams_t &irParams, decode_results *results);
    static int compare(unsigned int oldval, unsigned int newval);
};


#endif //TURRET_IRRXBASE_H
