#ifndef IR_SENSOR_CLUSTER__H
#define IR_SENSOR_CLUSTER__H

#include <Arduino.h>
<<<<<<< HEAD
#include <IrClusterStructs.h>
=======
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
>>>>>>> 0d3320b3bb459e5f6f9b451a3088230569589b66

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
