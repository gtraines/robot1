#ifndef IR_SENSOR_CLUSTER__H
#define IR_SENSOR_CLUSTER__H

#include <Arduino.h>
#include <CppList/CppList.h>
#include <IrReceiver.h>

typedef struct {
    int PinNumber;
    String Name;
    IrReceiver* HitSensor;
} directional_sensor_t;

typedef struct {
    String SensorName;
    long ReadingValue;
} sensor_reading_t;

class IrSensorCluster {
public:
    IrSensorCluster();
    ~IrSensorCluster();
    bool checkNextSensor();
    sensor_reading_t* getSensorReading();
private:
    /* data members */
    int _currentSensorIndex;
    
}

#endif // IR_SENSOR_CLUSTER__H
