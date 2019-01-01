#ifndef TURRET_CONTROLLERS__IR_SENSOR_MONITOR_H
#define TURRET_CONTROLLERS__IR_SENSOR_MONITOR_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <HardwareSerial.h>
#include <IRLibGlobals.h>

class IrSensorMonitor
{
protected:
    static uint8_t irPinInterruptFront;
    static uint8_t irPinInterruptLeft;
    static uint8_t irPinInterruptRight;
    static uint8_t irPinInterruptRear;
    static uint8_t irPinInterruptHit;
    static void resetRcvrData();
    static void logRcvrData();
public:
    IrSensorMonitor(/* args */) { }
    ~IrSensorMonitor() { }
    static void initialize(HardwareSerial* serial);
    static void initializeRcvrData();
    static void setPins();
    static void dutyCycle(void* pvParameters);

    static void setInterruptNumbers();
    static void dumpInterruptNumbers();
    static void enableIrPinInterrupts();
    static void disableIrPinInterrupts();
    static void dumpRcvrData(uint8_t rcvrDirection, recvGlobal_t* rcvrData);

    static void interruptHandlerHit();
    static void interruptHandlerRear();
    static void interruptHandlerRight();
    static void interruptHandlerLeft();
    static void interruptHandlerBase(uint8_t rcvrPin, recvGlobal_t* rcvrData);
    static void interruptHandlerFront();

    static HardwareSerial* serialConn;
    static TaskHandle_t irTaskHandle;
    static SemaphoreHandle_t irSemaphore;
    static recvGlobal_t rcvrDataFront;
    static recvGlobal_t rcvrDataLeft;
    static recvGlobal_t rcvrDataRight;
    static recvGlobal_t rcvrDataRear;
    static recvGlobal_t rcvrDataHit;
};

#endif // !TURRET_CONTROLLERS__IR_SENSOR_MONITOR_H