//
// Created by graham on 11/19/18.
//

#include "IrSensorMonitor.h"
#include <Arduino.h>
#include <Taskr.h>
#include <TurretPins.h>
#include <Indicator.h>

TaskHandle_t IrSensorMonitor::irTaskHandle = nullptr;
IrSensorCluster* IrSensorMonitor::sxrCluster = nullptr;
HardwareSerial* IrSensorMonitor::serialConn = nullptr;

void IrSensorMonitor::initialize() {
    IrSensorMonitor::sxrCluster = new IrSensorCluster();

    BaseType_t taskCreationStatus = xTaskCreate(
            IrSensorMonitor::dutyCycle,
            (const portCHAR *) "IrSxrMonitorTask",
            256,  // Stack size
            NULL,
            2,  // Priority
            &IrSensorMonitor::irTaskHandle);
}

void IrSensorMonitor::dutyCycle(void *pvParameters) {

    boolean success = true;

    while (success) {
        if (IrSensorMonitor::sxrCluster->checkNextSensor()) {
            Indicator::strobeFast(ACTY_LED_3, 6);
        }
        Taskr::delayMs(90);
    }
}

TickType_t IrSensorMonitor::getDelay() {
    return Taskr::getMillis(60);
}

String IrSensorMonitor::getSerialMessage(sensor_reading_t* sensorReading) {
    String message = "HIT:" + sensorReading->sensorName + "|VAL:" + sensorReading->readingValue;
    return message;
}
