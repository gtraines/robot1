//
// Created by graham on 12/3/18.
//

#include "IrRxInterrupt.h"
#include "IrInterruptConfig.h"
#include <IRLibGlobals.h>

uint8_t IrRxInterrupt::irInterruptFront=0;
uint8_t IrRxInterrupt::irInterruptLeft=0;
uint8_t IrRxInterrupt::irInterruptRight=0;
uint8_t IrRxInterrupt::irInterruptRear=0;
uint8_t IrRxInterrupt::irInterruptHit=0;

void IrRxInterrupt::initialize() {

}

void IrRxInterrupt::initializeReceiverData(recvGlobal_t* rcvrData) {
    //These first two lines would normally be done by the decoder
    //however in rare circumstances there is no decoder.
    rcvrData->decoderWantsData=false; //turned on by enableIRIn.
    rcvrData->decodeBuffer=rcvrData->recvBuffer;//default buffer
    rcvrData->enableAutoResume=false;
    rcvrData->frameTimeout=DEFAULT_FRAME_TIMEOUT;
    rcvrData->frameTimeoutTicks=rcvrData->frameTimeout/USEC_PER_TICK;
    rcvrData->newDataAvailable=false;
    rcvrData->enableBlinkLED=false;
    rcvrData->currentState=STATE_FINISHED;//i.e. Not running.
}

void IrRxInterrupt::resetReceiverData(recvGlobal_t* rcvrData) {
    initializeReceiverData(rcvrData);
    rcvrData->recvLength = 0;
    rcvrData->decoderWantsData = true;
    rcvrData->currentState = STATE_READY_TO_BEGIN;
}

void IrRxInterrupt::setRxComplete(recvGlobal_t *rcvrData, uint8_t reason) {

    // Here we are finished. Let the world know there is new data available.
    rcvrData->newDataAvailable=true;
    rcvrData->currentState=STATE_FINISHED;//this essentially pauses the receiver ISR
    //Now we need to see if we want to auto resume. We can only do that if it is enabled and
    //if the user is finished using the buffer from the previous capture and wants more data.
    //DEBUG_VALUE ("Reason completed", Reason)
    if (rcvrData->enableAutoResume && rcvrData->decoderWantsData) {
        //Here we do the actual auto resume. We will copy the data using memcpy because it
        //should be very quick. Any calculations will be handled by the getResults method but
        //not here.
        memcpy((void *)rcvrData->decodeBuffer, (const void*)rcvrData->recvBuffer, rcvrData->recvLength*sizeof(uint16_t));
        rcvrData->decodeLength=rcvrData->recvLength;
        // We have just copied the data to the decoder so it's not going to want more until
        // it tells us that it is ready for more.
        rcvrData->decoderWantsData=false;
        // Tell getResults that we auto resumed therefore the data has been copied but
        // still needs the math done.
        rcvrData->didAutoResume=true;
        // Now we need to reset the index to the beginning and restart the state machine.
        rcvrData->recvLength=0;
        //While we were doing the copy, the 50 us interrupt continued but the state machine
        //was paused in the STATE_FINISHED. Now we actually turn it back on till you get to
        //actually receive data.
        rcvrData->currentState= STATE_READY_TO_BEGIN;
    }
}

void IrRxInterrupt::handleInterrupt(uint8_t rcvrPin, recvGlobal_t* rcvrData) {
    //cli();
    uint32_t volatile changeTime = micros();
    uint32_t deltaTime = changeTime - rcvrData->timer;

    switch (rcvrData->currentState) {
        case STATE_FINISHED: return;
        case STATE_RUNNING:
            if (!(rcvrData->recvLength & 1)) {
                if (deltaTime > rcvrData->frameTimeout) {
                    IrRxInterrupt::setRxComplete(rcvrData, 1);//all finished, reset and possibly do auto resume
                    return;//don't record final space
                }
            }
            break;
        case STATE_READY_TO_BEGIN:
            if (digitalRead(rcvrPin)) {//pin high means SPACE
                return;//don't start until we get a MARK
            } else {
                rcvrData->currentState=STATE_RUNNING;
            }
            break;
        default: break;
    };

    rcvrData->recvBuffer[rcvrData->recvLength] = deltaTime;
    rcvrData->timer = changeTime;
    if(++rcvrData->recvLength >= RECV_BUF_LENGTH) {//buffer overflows so we quit
        IrRxInterrupt::setRxComplete(rcvrData, 2);
    }
}

void IrRxInterrupt::dumpIrRxData(recvGlobal_t *rcvrData) {
}
