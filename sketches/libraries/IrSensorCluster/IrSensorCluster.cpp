#include <Arduino.h>
#include <IrSensorCluster.h>
#include <TurretPins.h>

IrSensorCluster::IrSensorCluster() {
    this->_currentSensorIndex = 0;

    this->_sensorArray[0] = this->_createSensorEntry(IR_SXR_HIT, "HIT");
    this->_sensorArray[1] = this->_createSensorEntry(IR_SXR_DIRECTION_REAR, "REAR");
    this->_sensorArray[2] = this->_createSensorEntry(IR_SXR_DIRECTION_RIGHT, "RIGHT");
    this->_sensorArray[3] = this->_createSensorEntry(IR_SXR_DIRECTION_LEFT, "LEFT");
    this->_sensorArray[4] = this->_createSensorEntry(IR_SXR_DIRECTION_FRONT, "FRONT");
}

bool IrSensorCluster::checkNextSensor() {
    if (this->_currentSensorIndex == 4) {
        this->_currentSensorIndex = 0;
    } else {
        this->_currentSensorIndex++;
    }

    directional_sensor_t* currentSensor = this->_sensorArray[_currentSensorIndex];

    return (currentSensor->irSensor->decode(&currentSensor->sensorResults));
}

IrSensorCluster::~IrSensorCluster() {
}

directional_sensor_t* IrSensorCluster::_createSensorEntry(int pinNumber, String sensorName) {
    
    pinMode(pinNumber, INPUT_PULLUP);

    directional_sensor_t* createdSensor = new directional_sensor_t();
    
    createdSensor->pinNumber = pinNumber;
    createdSensor->sensorName = sensorName;
    createdSensor->irSensor = new IrReceiver(pinNumber);
    createdSensor->irSensor->enableIRIn();

    return createdSensor;
}


