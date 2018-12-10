//
// Created by graham on 12/3/18.
//

#ifndef TURRET_IRRXINTERRUPT_H
#define TURRET_IRRXINTERRUPT_H

#include <Arduino.h>
#include <IRLibGlobals.h>
#include <IRLibHardware.h>

// PIN 27 low
#define IR_RX_LED_ON()   (PORTA &= B11011111)
// PIN 27 high
#define IR_RX_LED_OFF()  (PORTA |= B00100000)


class IrRxInterrupt {
public:
    static uint8_t irInterruptFront;
    static uint8_t irInterruptLeft;
    static uint8_t irInterruptRight;
    static uint8_t irInterruptRear;
    static uint8_t irInterruptHit;
    static uint16_t markExcess;
    static void initialize();
    static void dumpIrRxData(recvGlobal_t* rcvrData);
    static void initializeReceiverData(recvGlobal_t* rcvrData);
    static void resetReceiverData(recvGlobal_t* rcvrData);
    static void setRxComplete(recvGlobal_t* rcvrData, uint8_t reason);
    static void handleInterrupt(uint8_t rcvrPin, recvGlobal_t* rcvrData);

};


#endif //TURRET_IRRXINTERRUPT_H
