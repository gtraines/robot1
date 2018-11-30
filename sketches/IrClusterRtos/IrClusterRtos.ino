#include <Arduino.h>
#include <Indicator.h>
#include <TurretController.h>
#include <IrSensorCluster.h>

IrSensorCluster* sensorCluster = nullptr;
sensor_reading_t* currentReading = nullptr;
String msg = "";

void setup() {
    TurretController::setPins();
    TurretController::turnOffAllIndicators();
    sensorCluster = new IrSensorCluster();

    Serial.begin(115200);
    Serial.println("Started");
}

void loop() {

    if (sensorCluster->checkNextSensor() > 0) {
        Indicator::turnOnLed(ACTY_LED_1);
        currentReading = sensorCluster->getSensorReading();
        Indicator::turnOnLed(ACTY_LED_2);
        msg += currentReading->sensorName;
        msg += ": ";

        Serial.print(msg);
        Serial.println(currentReading->readingValue);
        msg = "";
        Indicator::turnOffLed(ACTY_LED_1);
        Indicator::turnOffLed(ACTY_LED_2);
    }
}