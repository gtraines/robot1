#include <Arduino.h>
#include <HardwareSerial.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <TurretPins.h>
#include <Indicator.h>
#include <TurretController.h>
#include <IrSensorMonitor.h>
#include <Taskr.h>

#include <pins_arduino.h>
#include <IrInterruptConfig.h>
#include <IRLibProtocols.h>
#include <IRLibGlobals.h>
#include <IrRxInterrupt.h>

#define USEC_PER_TICK 50  // microseconds per clock interrupt tick


#define TURRET_DEBUG true

recvGlobal_t frontRxData;
volatile uint8_t irPinInterruptFront;
volatile bool hitFront;

void dump(recvGlobal_t* rcvrData);


void setup() {
    TurretController::setPins();
    TurretController::turnOffAllIndicators();
    IrSensorMonitor::initialize();

    Serial.begin(38400);
    Serial.println("Started");
}

void loop() {

}

void dump(recvGlobal_t* rcvrData) {
    Serial.print(F("\n#define RAW_DATA_LEN "));
    Serial.println(rcvrData->recvLength, DEC);
    Serial.print(F("uint16_t rawData[RAW_DATA_LEN]={\n\t"));

    for(bufIndex_t i = 1; i < rcvrData->recvLength; i++) {
        Serial.print(rcvrData->recvBuffer[i], DEC);
        Serial.print(F(", "));
        if( (i % 8)==0) Serial.print(F("\n\t"));
    }
    Serial.println(F("1000};"));//Add arbitrary trailing space
}

void dumpInterruptNumbers() {
    Serial.print("Interrupt Front: ");
    Serial.println(irPinInterruptFront);
}

