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

TaskHandle_t IrSensorMonitor::irTaskHandle = NULL;
SemaphoreHandle_t IrSensorMonitor::irSemaphore = NULL;
HardwareSerial* IrSensorMonitor::serialConn = nullptr;

uint8_t IrSensorMonitor::irPinInterruptFront = 0;
uint8_t IrSensorMonitor::irPinInterruptLeft = 0;
uint8_t IrSensorMonitor::irPinInterruptRight = 0;
uint8_t IrSensorMonitor::irPinInterruptRear = 0;
uint8_t IrSensorMonitor::irPinInterruptHit = 0;

void IrSensorMonitor::initialize() {

    pinMode(IR_SXR_HIT, INPUT_PULLUP);
    pinMode(IR_SXR_REAR_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_RIGHT_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_LEFT_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_FRONT_PIN, INPUT_PULLUP);

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

void IrSensorMonitor::dutyCycle(void *pvParameters) {

    boolean success = true;
    BaseType_t semaphoreTaken = pdFALSE;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    while (success) {

        semaphoreTaken = xSemaphoreTakeFromISR(irSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken);

        if (semaphoreTaken == pdTRUE) {

        }
        Taskr::delayMs(60);
    }
}

void IrSensorMonitor::setInterruptNumbers() {
    irPinInterruptFront = digitalPinToInterrupt(IR_SXR_FRONT_PIN);
    irPinInterruptLeft = digitalPinToInterrupt(IR_SXR_LEFT_PIN);
    irPinInterruptRight = digitalPinToInterrupt(IR_SXR_RIGHT_PIN);
    irPinInterruptRear = digitalPinToInterrupt(IR_SXR_REAR_PIN);
}

void IrSensorMonitor::enableIrPinInterrupts() {
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_REAR_PIN), interruptHandlerRear, RISING);
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_RIGHT_PIN), interruptHandlerRight, FALLING);
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_LEFT_PIN), interruptHandlerLeft, FALLING);
    attachInterrupt(irPinInterruptFront, interruptHandlerFront, CHANGE);
}

void IrSensorMonitor::interruptHandlerFront() {
    cli();
    IrRxInterrupt::handleInterrupt(IR_SXR_FRONT_PIN, &frontRcvrData);
}

void IrSensorMonitor::disableIrPinInterrupts() {
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_REAR_PIN));
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_RIGHT_PIN));
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_LEFT_PIN));
    detachInterrupt(irPinInterruptFront);
}


