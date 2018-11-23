#ifndef TURRET_CONTROLLERS__IR_SENSOR_MONITOR_H
#define TURRET_CONTROLLERS__IR_SENSOR_MONITOR_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Arduino_FreeRTOS.h>
#include <IrSensorCluster.h>

class IrSensorMonitor
{
protected:
    static IrSensorCluster* sxrCluster;
    static TickType_t getDelay();
    static String getSerialMessage(sensor_reading_t* sensorReading);
public:
    IrSensorMonitor(/* args */) { }
    ~IrSensorMonitor() { }
    static void initialize();
    static void dutyCycle(void* pvParameters);
    static TaskHandle_t irTaskHandle;
    static HardwareSerial* serialConn;
};

#endif // !TURRET_CONTROLLERS__IR_SENSOR_MONITOR_H