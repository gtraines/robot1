//
// Created by graham on 12/3/18.
//

#ifndef TURRET_IRRXINTERRUPT_H
#define TURRET_IRRXINTERRUPT_H


#include <Arduino.h>
#include <IRLibGlobals.h>

volatile recvGlobal_t frontRcvrData;
volatile recvGlobal_t leftRcvrData;
volatile recvGlobal_t rightRcvrData;
volatile recvGlobal_t rearRcvrData;
volatile recvGlobal_t hitRcvrData;

void interruptHandlerHit();
void interruptHandlerRear();
void interruptHandlerRight();
void interruptHandlerBase();
void interruptHandlerFront();

void IRLib_IRrecvComplete(uint8_t Reason);


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


#endif //TURRET_IRRXINTERRUPT_H
