#ifndef IR_SENSOR_CLUSTER__H
#define IR_SENSOR_CLUSTER__H

#include <Arduino.h>
#include <CppList/CppList.h>
#include <IrReceiver.h>

struct directional_sensor_t {
    int pinNumber;
    String sensorName;
    IrReceiver* irSensor;
    decode_results* sensorResults;
};

struct sensor_reading_t {
    String sensorName;
    long readingValue;
};

class IrSensorCluster {
public:
    IrSensorCluster();
    ~IrSensorCluster();
    bool checkNextSensor();
    sensor_reading_t* getSensorReading();
private:
    /* data members */
    directional_sensor_t* _createSensorEntry(int pinNumber, String sensorName);
    int _currentSensorIndex;
    directional_sensor_t* _sensorArray[5];
};

#endif // IR_SENSOR_CLUSTER__H
