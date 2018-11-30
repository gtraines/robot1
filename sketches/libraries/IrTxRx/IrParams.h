//
// Created by graham on 11/30/18.
//

#ifndef TURRET_IRPARAMS_H
#define TURRET_IRPARAMS_H

#include <Arduino.h>
#include "IrInterruptConfig.h"

// information for the interrupt handler
typedef struct {
    uint8_t recvpin;           // pin for IR data from detector
    uint8_t rcvstate;          // state machine
    uint8_t blinkflag;         // TRUE to enable blinking of pin 13 on IR processing
    unsigned int timer;     // state timer, counts 50uS ticks.
    unsigned int rawbuf[RAWBUF]; // raw data
    uint8_t rawlen;         // counter of entries in rawbuf
}
IrParams_t;

#endif //TURRET_IRPARAMS_H
