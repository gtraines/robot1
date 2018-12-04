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
    static void processSignalsIn(volatile IrParams_t &irParams);
    static void resume(volatile IrParams_t* irParams);
    static long decodeHash(volatile decode_results *results);
    static int decode(volatile IrParams_t* irParams, volatile decode_results* results);
    static int compare(unsigned int oldval, unsigned int newval);

};


#endif //TURRET_IRRXBASE_H
