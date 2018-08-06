#include <Arduino.h>
#include <IrSensorCluster.h>
#include <TurretPins.h>

IrSensorCluster::IrSensorCluster() {
    this->_currentSensorIndex = 0;
    this->_sensorArray[0] = NULL;
}

IrSensorCluster::~IrSensorCluster() {
}


