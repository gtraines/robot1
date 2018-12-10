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
public:
    IrSensorMonitor(/* args */) { }
    ~IrSensorMonitor() { }
    static void initialize();
    static void dutyCycle(void* pvParameters);
    static TaskHandle_t irTaskHandle;
    static SemaphoreHandle_t irSemaphore;
    static void setInterruptNumbers();
    static void dumpInterruptNumbers();
    static void enableIrPinInterrupts();
    static void disableIrPinInterrupts();
    static HardwareSerial* serialConn;

    static void interruptHandlerHit();
    static void interruptHandlerRear();
    static void interruptHandlerRight();
    static void interruptHandlerBase();
    static void interruptHandlerFront();

    static recvGlobal_t frontRcvrData;
    static recvGlobal_t leftRcvrData;
    static recvGlobal_t rightRcvrData;
    static recvGlobal_t rearRcvrData;
    static recvGlobal_t hitRcvrData;
};

#endif // !TURRET_CONTROLLERS__IR_SENSOR_MONITOR_H