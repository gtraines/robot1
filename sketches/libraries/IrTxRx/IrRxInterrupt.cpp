//
// Created by graham on 12/3/18.
//

#include "IrRxInterrupt.h"
#include <IRLibGlobals.h>

uint8_t IrRxInterrupt::irInterruptFront=0;
uint8_t IrRxInterrupt::irInterruptLeft=0;
uint8_t IrRxInterrupt::irInterruptRight=0;
uint8_t IrRxInterrupt::irInterruptRear=0;
uint8_t IrRxInterrupt::irInterruptHit=0;

void IrRxInterrupt::initialize() {

}

void IrRxInterrupt::setInterruptNumbers() {

}

void IrRxInterrupt::dumpInterruptNumbers() {

}

void IrRxInterrupt::enableIrPinInterrupts() {

}

void IrRxInterrupt::disableIrPinInterrupts() {

}

void IrRxInterrupt::initializeReceiverData(recvGlobal_t rcvrData) {

}

void IrRxInterrupt::resetReceiverData(recvGlobal_t rcvrData) {
    //These first two lines would normally be done by the decoder
    //however in rare circumstances there is no decoder.
    recvGlobal.decoderWantsData=false; //turned on by enableIRIn.
    recvGlobal.decodeBuffer=recvGlobal.recvBuffer;//default buffer
    recvGlobal.enableAutoResume=false;
    recvGlobal.frameTimeout=DEFAULT_FRAME_TIMEOUT;
    recvGlobal.frameTimeoutTicks=recvGlobal.frameTimeout/USEC_PER_TICK;
    markExcess=DEFAULT_MARK_EXCESS;
    recvGlobal.newDataAvailable=false;
    recvGlobal.enableBlinkLED=false;
    recvGlobal.currentState=STATE_FINISHED;//i.e. Not running.
}
