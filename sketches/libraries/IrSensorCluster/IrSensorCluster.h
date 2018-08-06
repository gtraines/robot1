#ifndef IR_SENSOR_CLUSTER__H
#define IR_SENSOR_CLUSTER__H

#include <Arduino.h>
#include <CppList/CppList.h>
#include <IrReceiver.h>

struct directional_sensor_t {
    int PinNumber;
    String Name;
    IrReceiver* HitSensor;
};

struct sensor_reading_t {
    String SensorName;
    long ReadingValue;
};

class IrSensorCluster {
public:
    IrSensorCluster();
    ~IrSensorCluster();
    bool checkNextSensor();
    sensor_reading_t* getSensorReading();
private:
    /* data members */
    int _currentSensorIndex;
    directional_sensor_t* _sensorArray[5];

};

#endif // IR_SENSOR_CLUSTER__H
