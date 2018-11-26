#ifndef IR_SENSOR_CLUSTER__H
#define IR_SENSOR_CLUSTER__H

#include <Arduino.h>
#include <CppList.h>
#include <IrReceiver.h>

typedef struct {
    int pinNumber;
    String sensorName;
    IrReceiver* irSensor;
    decode_results* sensorResults;
} directional_sensor_t;

typedef struct {
    String sensorName;
    long readingValue;
} sensor_reading_t;

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
