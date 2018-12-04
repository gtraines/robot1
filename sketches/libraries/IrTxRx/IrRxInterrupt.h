//
// Created by graham on 12/3/18.
//

#ifndef TURRET_IRRXINTERRUPT_H
#define TURRET_IRRXINTERRUPT_H


#include <Arduino.h>
#include <IRLibGlobals.h>

recvGlobal_t frontRcvrData;
recvGlobal_t leftRcvrData;
recvGlobal_t rightRcvrData;
recvGlobal_t rearRcvrData;
recvGlobal_t hitRcvrData;

void interruptHandlerHit();
void interruptHandlerRear();
void interruptHandlerRight();
void interruptHandlerBase();
void interruptHandlerFront();

class IrRxInterrupt {
public:
    static uint8_t irInterruptFront;
    static uint8_t irInterruptLeft;
    static uint8_t irInterruptRight;
    static uint8_t irInterruptRear;
    static uint8_t irInterruptHit;
    static uint16_t markExcess;
    static void initialize();
    static void setInterruptNumbers();
    static void dumpInterruptNumbers();
    static void enableIrPinInterrupts();
    static void disableIrPinInterrupts();
    static void initializeReceiverData(recvGlobal_t rcvrData);
    static void resetReceiverData(recvGlobal_t rcvrData);

};

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
#endif //TURRET_IRRXINTERRUPT_H
