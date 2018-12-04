//
// Created by graham on 11/24/18.
//
#include "IrRxBase.h"
#include <Arduino.h>
#include <avr/io.h>
#include <pins_arduino.h>
#include "IrInterruptConfig.h"
#include "decode_results.h"
#include "IrParams.h"
#include <IRLibProtocols.h>

void IrRxBase::processSignalsIn(volatile IrParams_t &irParams) {
    volatile uint8_t irdata = (uint8_t) digitalRead(irParams.recvpin);
    
    irParams.timer++; // One more 50us tick
    if (irParams.rawlen >= RAWBUF) {
        // Buffer overflow
        irParams.rcvstate = STATE_STOP;
    }
    switch (irParams.rcvstate) {
        case STATE_IDLE: // In the middle of a gap
            if (irdata == MARK) {
                if (irParams.timer < GAP_TICKS) {
                    // Not big enough to be a gap.
                    irParams.timer = 0;
                } else {
                    // gap just ended, record duration and start recording transmission
                    irParams.rawlen = 0;
                    irParams.rawbuf[irParams.rawlen++] = irParams.timer;
                    irParams.timer = 0;
                    irParams.rcvstate = STATE_MARK;
                }
            }
            break;
        case STATE_MARK: // timing MARK
            if (irdata == SPACE) {   // MARK ended, record time
                irParams.rawbuf[irParams.rawlen++] = irParams.timer;
                irParams.timer = 0;
                irParams.rcvstate = STATE_SPACE;
            }
            break;
        case STATE_SPACE: // timing SPACE
            if (irdata == MARK) { // SPACE just ended, record it
                irParams.rawbuf[irParams.rawlen++] = irParams.timer;
                irParams.timer = 0;
                irParams.rcvstate = STATE_MARK;
            } else { // SPACE
                if (irParams.timer > GAP_TICKS) {
                    // big SPACE, indicates gap between codes
                    // Mark current code as ready for processing
                    // Switch to STOP
                    // Don't reset timer; keep counting space width
                    irParams.rcvstate = STATE_STOP;
                }
            }
            break;
        case STATE_STOP: // waiting, measuring gap
            if (irdata == MARK) { // reset gap timer
                irParams.timer = 0;
            }
            break;
    }
}


//+=============================================================================
// hashdecode - decode an arbitrary IR code.
// Instead of decoding using a standard encoding scheme
// (e.g. Sony, NEC, RC5), the code is hashed to a 32-bit value.
//
// The algorithm: look at the sequence of MARK signals, and see if each one
// is shorter (0), the same length (1), or longer (2) than the previous.
// Do the same with the SPACE signals.  Hash the resulting sequence of 0's,
// 1's, and 2's to a 32-bit value.  This will give a unique value for each
// different code (probably), for most code systems.
//
// http://arcfn.com/2010/01/using-arbitrary-remotes-with-arduino.html
//
// Compare two tick values, returning 0 if newval is shorter,
// 1 if newval is equal, and 2 if newval is longer
// Use a tolerance of 20%
//
int  IrRxBase::compare (unsigned int oldval,  unsigned int newval) {
    if      (newval < oldval * .8)  return 0 ;
    else if (oldval < newval * .8)  return 2 ;
    else                            return 1 ;
}

//+=============================================================================
// Use FNV hash algorithm: http://isthe.com/chongo/tech/comp/fnv/#FNV-param
// Converts the raw code values into a 32-bit hash code.
// Hopefully this code is unique for each button.
// This isn't a "real" decoding, just an arbitrary value.
//
#define FNV_PRIME_32 16777619
#define FNV_BASIS_32 2166136261

long IrRxBase::decodeHash (volatile decode_results *results) {
    long  hash = (long)FNV_BASIS_32;

    // Require at least 6 samples to prevent triggering on noise
    if (results->rawlen < 6)  return false ;

    for (int i = 1;  (i + 2) < results->rawlen;  i++) {
        int value =  compare(results->rawbuf[i], results->rawbuf[i+2]);
        // Add value into the hash
        hash = (hash * FNV_PRIME_32) ^ value;
    }

    results->value       = hash;
    results->bits        = 32;
    results->decode_type = UNKNOWN;

    return true;
}

void IrRxBase::resume(volatile IrParams_t* irParams) {
    irParams->rcvstate = STATE_IDLE;
    irParams->rawlen = 0;
    irParams->timer = 0;
    irParams->recvpin = 0;
}

// Decodes the received IR message
// Returns 0 if no data ready, 1 if data ready.
// Results of decoding are stored in results
int IrRxBase::decode(volatile IrParams_t* irParams, volatile decode_results* results) {
    results->rawbuf = irParams->rawbuf;
    results->rawlen = irParams->rawlen;
    if (irParams->rcvstate != STATE_STOP) {
        return ERR;
    }
    // decodeHash returns a hash on any input.
    // Thus, it needs to be last in the list.
    // If you add any decodes, add them before this.
    return (int)decodeHash(results);
}

