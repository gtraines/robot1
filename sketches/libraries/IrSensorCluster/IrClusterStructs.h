#ifndef IR_CLUSTER_STRUCTS__H
#define IR_CLUSTER_STRUCTS__H

#include <IrReceiver.h>

struct directional_sensor_t {
    int pinNumber;
    String sensorName;
    IrReceiver* irSensor;
    decode_results sensorResults;
};

struct sensor_reading_t {
    String sensorName;
    long readingValue;
};

#endif
