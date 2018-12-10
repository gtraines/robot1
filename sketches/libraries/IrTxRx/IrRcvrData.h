//
// Created by graham on 12/9/18.
//

#ifndef TURRET_IRRCVRDATA_H
#define TURRET_IRRCVRDATA_H

#include <Arduino.h>
#include <IRLibRecvBase.h>

typedef struct {
    uint8_t pinNumber;
    uint8_t interruptNumber;
    String sensorName;
    recvGlobal_t sxrData;
} IrRcvrData_t;

#endif //TURRET_IRRCVRDATA_H
