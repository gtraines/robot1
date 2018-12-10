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

void setIrRxPins();
void setInterruptNumbers();
void dumpInterruptNumbers();
void interruptHandlerFront( void );
void enableIrPinInterrupts( void );
void disableIrPinInterrupts( void );

void dump(recvGlobal_t* rcvrData);


void setup() {
    TurretController::setPins();
    TurretController::turnOffAllIndicators();
    Serial.begin(38400);

    setIrRxPins();
    setInterruptNumbers();
    dumpInterruptNumbers();
    IrRxInterrupt::resetReceiverData(&frontRxData);
    enableIrPinInterrupts();
    Serial.println("Started");
}

void loop() {

    //Continue looping until you get a complete signal received
    if (frontRxData.currentState==STATE_FINISHED) {
        IR_RX_LED_ON();
        dump(&frontRxData);
        IrRxInterrupt::resetReceiverData(&frontRxData);
        enableIrPinInterrupts();
        IR_RX_LED_OFF();
        delay(10);
    }
    delay(10);
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

void setIrRxPins() {
    //pinMode(IR_SXR_REAR_PIN, INPUT_PULLUP);
    //pinMode(IR_SXR_RIGHT_PIN, INPUT_PULLUP);
    //pinMode(IR_SXR_LEFT_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_FRONT_PIN, INPUT_PULLUP);
}

void setInterruptNumbers() {
    irPinInterruptFront = digitalPinToInterrupt(IR_SXR_FRONT_PIN);
}

void dumpInterruptNumbers() {
    Serial.print("Interrupt Front: ");
    Serial.println(irPinInterruptFront);
}

void enableIrPinInterrupts( void ) {
    //Indicator::turnOffLed(MOVE_LED_RED);
    //pinMode(IR_SXR_HIT, INPUT_PULLUP);
    //attachInterrupt(IR_SXR_HIT, interruptHandlerHit, RISING);
    //setIrRxPins();
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_REAR_PIN), interruptHandlerRear, RISING);
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_RIGHT_PIN), interruptHandlerRight, FALLING);
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_LEFT_PIN), interruptHandlerLeft, FALLING);
    attachInterrupt(irPinInterruptFront, interruptHandlerFront, CHANGE);
}

void disableIrPinInterrupts( void ) {
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_REAR_PIN));
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_RIGHT_PIN));
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_LEFT_PIN));
    detachInterrupt(irPinInterruptFront);

    //Indicator::turnOnLed(MOVE_LED_RED);
}

void interruptHandlerFront( void ) {
    cli();
    IrRxInterrupt::handleInterrupt(IR_SXR_FRONT_PIN, &frontRxData);
}
