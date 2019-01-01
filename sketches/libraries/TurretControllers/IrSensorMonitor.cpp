//
// Created by graham on 11/19/18.
//

#include "IrSensorMonitor.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include <WString.h>
#include <HardwareSerial.h>
#include <Print.h>

#include <Taskr.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <IrRxInterrupt.h>
#include <IRLibGlobals.h>
#include <IrConfig.h>

TaskHandle_t IrSensorMonitor::irTaskHandle = NULL;
SemaphoreHandle_t IrSensorMonitor::irSemaphore = NULL;
HardwareSerial* IrSensorMonitor::serialConn = nullptr;

uint8_t IrSensorMonitor::irPinInterruptFront = 0;
uint8_t IrSensorMonitor::irPinInterruptLeft = 0;
uint8_t IrSensorMonitor::irPinInterruptRight = 0;
uint8_t IrSensorMonitor::irPinInterruptRear = 0;
uint8_t IrSensorMonitor::irPinInterruptHit = 0;

recvGlobal_t IrSensorMonitor::rcvrDataFront;
recvGlobal_t IrSensorMonitor::rcvrDataRear;
recvGlobal_t IrSensorMonitor::rcvrDataLeft;
recvGlobal_t IrSensorMonitor::rcvrDataRight;
recvGlobal_t IrSensorMonitor::rcvrDataHit;

void IrSensorMonitor::initialize(HardwareSerial* serial) {

    serialConn = serial;
    setPins();
    initializeRcvrData();

    irSemaphore = xSemaphoreCreateCounting(1, 0); // maxcount, initial count

    if(irSemaphore != NULL) {
        BaseType_t taskCreationStatus = xTaskCreate(
                IrSensorMonitor::dutyCycle,
                (const portCHAR *) "IrSxrMonitorTask",
                256,  // Stack size
                NULL,
                2,  // Priority
                &IrSensorMonitor::irTaskHandle);
    } else {
        Indicator::turnOnLed(ARD_STATUS_RED);
    }

    setInterruptNumbers();
    enableIrPinInterrupts();
}

void IrSensorMonitor::initializeRcvrData() {
    rcvrDataFront = recvGlobal_t();

    IrRxInterrupt::resetReceiverData(&rcvrDataFront);
}

void IrSensorMonitor::setPins() {
    pinMode(IR_SXR_HIT_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_REAR_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_RIGHT_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_LEFT_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_FRONT_PIN, INPUT_PULLUP);
}


void IrSensorMonitor::dutyCycle(void *pvParameters) {

    boolean success = true;
    BaseType_t semaphoreTaken = pdFALSE;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    while (success) {

        semaphoreTaken = xSemaphoreTakeFromISR(irSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken);

        if (semaphoreTaken == pdTRUE) {
            Indicator::strobeFast(ACTY_LED_2, 2);
            logRcvrData();
            resetRcvrData();
        }
        Taskr::delayMs(60);
    }
}

void IrSensorMonitor::setInterruptNumbers() {
    irPinInterruptFront = digitalPinToInterrupt(IR_SXR_FRONT_PIN);
    irPinInterruptLeft = digitalPinToInterrupt(IR_SXR_LEFT_PIN);
    irPinInterruptRight = digitalPinToInterrupt(IR_SXR_RIGHT_PIN);
    irPinInterruptRear = digitalPinToInterrupt(IR_SXR_REAR_PIN);
    irPinInterruptHit = digitalPinToInterrupt(IR_SXR_HIT_PIN);
}

void IrSensorMonitor::enableIrPinInterrupts() {
    attachInterrupt(irPinInterruptRear, interruptHandlerRear, CHANGE);
    attachInterrupt(irPinInterruptRight, interruptHandlerRight, CHANGE);
    attachInterrupt(irPinInterruptLeft, interruptHandlerLeft, CHANGE);
    attachInterrupt(irPinInterruptFront, interruptHandlerFront, CHANGE);
    attachInterrupt(irPinInterruptHit, interruptHandlerHit, CHANGE);
}

void IrSensorMonitor::disableIrPinInterrupts() {
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_REAR_PIN));
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_RIGHT_PIN));
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_LEFT_PIN));
    detachInterrupt(irPinInterruptFront);
}

void IrSensorMonitor::interruptHandlerFront() {
    //cli();
    interruptHandlerBase(IR_SXR_FRONT_PIN, &rcvrDataFront);
}

void IrSensorMonitor::interruptHandlerRear() {
    interruptHandlerBase(IR_SXR_REAR_PIN, &rcvrDataRear);
}

void IrSensorMonitor::interruptHandlerLeft() {
    interruptHandlerBase(IR_SXR_LEFT_PIN, &rcvrDataLeft);
}

void IrSensorMonitor::interruptHandlerRight() {
    interruptHandlerBase(IR_SXR_RIGHT_PIN, &rcvrDataRight);
}

void IrSensorMonitor::interruptHandlerHit() {
    interruptHandlerBase(IR_SXR_HIT_PIN, &rcvrDataHit);
}

void IrSensorMonitor::interruptHandlerBase(uint8_t rcvrPin, recvGlobal_t* rcvrData) {
    cli();
    IrRxInterrupt::handleInterrupt(rcvrPin, rcvrData);

    if (rcvrData->currentState == STATE_FINISHED) {
        static portBASE_TYPE xHigherPriorityTaskWoken;

        xHigherPriorityTaskWoken = pdFALSE;

        xSemaphoreGiveFromISR(irSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken);

        if (xHigherPriorityTaskWoken == pdTRUE) {
            // portSWITCH_CONTEXT();
            vPortYield();
        }
    }
    interrupts();
}

void IrSensorMonitor::dumpRcvrData(uint8_t rcvrDirection, recvGlobal_t *rcvrData) {
    if (rcvrData->recvLength >= MIN_SIGNAL_PULSE_LENGTH
        && rcvrData->recvLength <= MAX_SIGNAL_PULSE_LENGTH) {

        serialConn->print("\nDIRECTION: ");
        serialConn->println(rcvrDirection, DEC);
        serialConn->print(F("RAW_DATA_LEN "));
        serialConn->println(rcvrData->recvLength, DEC);
        serialConn->print(F("[\n\t"));

        for(bufIndex_t i = 1; i < rcvrData->recvLength; i++) {
            serialConn->print(rcvrData->recvBuffer[i], DEC);
            serialConn->print(F(", "));

            if( (i % 8)==0) serialConn->print(F("\n\t"));
        }

        serialConn->println(F("1000 \n]"));//Add arbitrary trailing space
    }
}

void IrSensorMonitor::logRcvrData() {
    if (rcvrDataFront.currentState == STATE_FINISHED) {
        dumpRcvrData(IR_SXR_FRONT_PIN, &rcvrDataFront);
    }

    if (rcvrDataRear.currentState == STATE_FINISHED) {
        dumpRcvrData(IR_SXR_REAR_PIN, &rcvrDataRear);
    }

    if (rcvrDataLeft.currentState == STATE_FINISHED) {
        dumpRcvrData(IR_SXR_LEFT_PIN, &rcvrDataLeft);
    }

    if (rcvrDataRight.currentState == STATE_FINISHED) {
        dumpRcvrData(IR_SXR_RIGHT_PIN, &rcvrDataRight);
    }

    if (rcvrDataHit.currentState == STATE_FINISHED) {
        dumpRcvrData(IR_SXR_HIT_PIN, &rcvrDataHit);
    }
}

void IrSensorMonitor::resetRcvrData() {
    IrRxInterrupt::resetReceiverData(&rcvrDataFront);
    IrRxInterrupt::resetReceiverData(&rcvrDataRear);
    IrRxInterrupt::resetReceiverData(&rcvrDataLeft);
    IrRxInterrupt::resetReceiverData(&rcvrDataRight);
    IrRxInterrupt::resetReceiverData(&rcvrDataHit);
}



