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

    pinMode(IR_SXR_HIT, INPUT_PULLUP);
    pinMode(IR_SXR_DIRECTION_REAR, INPUT_PULLUP);
    pinMode(IR_SXR_DIRECTION_RIGHT, INPUT_PULLUP);
    pinMode(IR_SXR_DIRECTION_LEFT, INPUT_PULLUP);
    pinMode(IR_SXR_DIRECTION_FRONT, INPUT_PULLUP);
    IrSensorMonitor::sxrCluster = new IrSensorCluster();
    Indicator::turnOnLed(ACTY_LED_1);
    delay(1500);
    Indicator::turnOffLed(ACTY_LED_1);

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
            sensor_reading_t* thisResult = IrSensorMonitor::sxrCluster->getSensorReading();
            Indicator::strobeFast(ACTY_LED_3, 6);
        }
        Taskr::delayMs(60);
    }
}

TickType_t IrSensorMonitor::getDelay() {
    return Taskr::getMillis(60);
}

String IrSensorMonitor::getSerialMessage(sensor_reading_t* sensorReading) {
    String message = "HIT:" + sensorReading->sensorName + "|VAL:" + sensorReading->readingValue;
    return message;
}
