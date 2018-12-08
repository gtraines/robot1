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

void interruptHandlerFront(){
    uint32_t volatile changeTime=micros();
    uint32_t deltaTime=changeTime-recvGlobal.timer;
    switch(recvGlobal.currentState) {
        case STATE_FINISHED: return;
        case STATE_RUNNING:
            if( !(recvGlobal.recvLength & 1) ){
                if (deltaTime>recvGlobal.frameTimeout) {
                    IRLib_IRrecvComplete(1);//all finished, reset and possibly do auto resume
                    return;//don't record final space
                }
            }
            break;
        case STATE_READY_TO_BEGIN:
            if(digitalRead(recvGlobal.recvPin)) {//pin high means SPACE
                return;//don't start until we get a MARK
            } else {
                recvGlobal.currentState=STATE_RUNNING;
            }
            break;
    };
    recvGlobal.recvBuffer[recvGlobal.recvLength]=deltaTime;
    recvGlobal.timer=changeTime;
    if(++recvGlobal.recvLength>=RECV_BUF_LENGTH) {//buffer overflows so we quit
        IRLib_IRrecvComplete(2);
    }
}

/*
 * This function is called by both the 50us and PCI ISR in one of two circumstances:
 * 1) The SPACE was long enough that we are sure the frame is over and ready to process.
 * 2) The buffer overflowed we have to quit. The parameter is for debugging purposes only.
 */
void IRLib_IRrecvComplete(uint8_t Reason) {
    // Here we are finished. Let the world know there is new data available.
    recvGlobal.newDataAvailable=true;
    recvGlobal.currentState=STATE_FINISHED;//this essentially pauses the receiver ISR
    //Now we need to see if we want to auto resume. We can only do that if it is enabled and
    //if the user is finished using the buffer from the previous capture and wants more data.
    //DEBUG_VALUE ("Reason completed", Reason)
    if (recvGlobal.enableAutoResume && recvGlobal.decoderWantsData) {
        //Here we do the actual auto resume. We will copy the data using memcpy because it
        //should be very quick. Any calculations will be handled by the getResults method but
        //not here.
        memcpy((void *)recvGlobal.decodeBuffer, (const void*)recvGlobal.recvBuffer,recvGlobal.recvLength*sizeof(uint16_t));
        recvGlobal.decodeLength=recvGlobal.recvLength;
        // We have just copied the data to the decoder so it's not going to want more until
        // it tells us that it is ready for more.
        recvGlobal.decoderWantsData=false;
        // Tell getResults that we auto resumed therefore the data has been copied but
        // still needs the math done.
        recvGlobal.didAutoResume=true;
        // Now we need to reset the index to the beginning and restart the state machine.
        recvGlobal.recvLength=0;
        //While we were doing the copy, the 50 us interrupt continued but the state machine
        //was paused in the STATE_FINISHED. Now we actually turn it back on till you get to
        //actually receive data.
        recvGlobal.currentState= STATE_READY_TO_BEGIN;
    }
}