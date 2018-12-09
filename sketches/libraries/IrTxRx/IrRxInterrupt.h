//
// Created by graham on 12/3/18.
//

#ifndef TURRET_IRRXINTERRUPT_H
#define TURRET_IRRXINTERRUPT_H

#include <Arduino.h>
#include <IRLibGlobals.h>
#include <IRLibHardware.h>

#ifndef DEFAULT_BLINK_PIN
#define DEFAULT_BLINK_PIN LED_BUILTIN  //NOTE: LED_BUILTIN is an Arduino constant
#endif

#ifndef DEFAULT_BLINK_ENABLED
#define DEFAULT_BLINK_ENABLED false
#endif

#ifndef DEFAULT_MARK_EXCESS
#define DEFAULT_MARK_EXCESS 50
#endif

#ifndef DEFAULT_FRAME_TIMEOUT
#define DEFAULT_FRAME_TIMEOUT 7800 //maximum length of SPACE Sbefore we assume frame ended
#endif
//DEFAULT_TIMEOUT should be 1.25*the_largest_space_any_valid_IR_protocol_might_have.
//In IRremote library ir_Dish.cpp space they use DISH_RPT_SPACE 6200 while referenced says
//about 6000. If we take 6200*1.25= 7750 rounded up we will use 7800. Previous IRLib
//value was 10000 was probably too large. Thanks to Gabriel Staples for this note.


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
