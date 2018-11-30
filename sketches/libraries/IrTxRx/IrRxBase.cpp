//
// Created by graham on 11/24/18.
//

#include "IrRxBase.h"
#include "IrInterruptConfig.h"
#include <Arduino.h>
#include <avr/io.h>
#include <pins_arduino.h>

bool IrRxBase::addReceiverInterrupt(uint16_t interrupt, String name) {
    return false;
}

uint16_t *IrRxBase::processSignalsIn(uint8_t interrupt) {
    return nullptr;
}

void IrRxBase::processSignalsIn(IrParams_t &irParams) {
    uint8_t irdata = (uint8_t) digitalRead(irParams.recvpin);

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

// SPACE
void IrRxBase::processRisingInterrupt(IrParams_t &irParams) {
    irParams.timer++; // One more 50us tick
    if (irParams.rawlen >= RAWBUF) {
        // Buffer overflow
        irParams.rcvstate = STATE_STOP;
    }
    switch (irParams.rcvstate) {
        case STATE_IDLE: // In the middle of a gap

            break;
        case STATE_MARK: // timing MARK
            // MARK ended, record time
            irParams.rawbuf[irParams.rawlen++] = irParams.timer;
            irParams.timer = 0;
            irParams.rcvstate = STATE_SPACE;
            break;
        case STATE_SPACE: // timing SPACE
            if (irParams.timer > GAP_TICKS) {
                // big SPACE, indicates gap between codes
                // Mark current code as ready for processing
                // Switch to STOP
                // Don't reset timer; keep counting space width
                irParams.rcvstate = STATE_STOP;
            }
            break;
        case STATE_STOP: // waiting, measuring gap
            break;
        default:break;
    }
}

// MARK
void IrRxBase::processFallingInterrupt(IrParams_t &irParams) {
    irParams.timer++; // One more 50us tick
    if (irParams.rawlen >= RAWBUF) {
        // Buffer overflow
        irParams.rcvstate = STATE_STOP;
    }
    switch (irParams.rcvstate) {
        case STATE_IDLE: // In the middle of a gap
            if (irParams.timer < GAP_TICKS) {
                // Not big enough to be a gap.
                irParams.timer = 0;
            }
            break;
        case STATE_MARK: // timing MARK
            break;
        case STATE_SPACE: // timing SPACE
            // SPACE just ended, record it
            irParams.rawbuf[irParams.rawlen++] = irParams.timer;
            irParams.timer = 0;
            irParams.rcvstate = STATE_MARK;
            break;
        case STATE_STOP: // waiting, measuring gap
            // reset gap timer
            irParams.timer = 0;
            break;
        default:break;
    }
}

void IrRxBase::resume(IrParams_t &irParams) {
    irParams.rcvstate = STATE_IDLE;
    irParams.rawlen = 0;
}

