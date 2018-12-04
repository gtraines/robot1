#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <IRLibRecvPCI.h>
//#include <Arduino_FreeRTOS.h>
//#include <task.h>
//#include <semphr.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <TurretController.h>
#include <IrParams.h>
#include <IrRxBase.h>
//#include <Taskr.h>
#include <pins_arduino.h>
#include <IrInterruptConfig.h>
#include <decode_results.h>
#include <IRLibProtocols.h>
#include <IRLibGlobals.h>

#define USEC_PER_TICK 50  // microseconds per clock interrupt tick


#define TURRET_DEBUG true
uint16_t markExcess;

static void setIrRxPins();
static volatile uint8_t rcvrPin;
static volatile bool waitingForSignalFinish;
static volatile bool waitingForIrEnable;
static volatile bool hitFront;

static void setInterruptNumbers();
static void dumpInterruptNumbers();
static void enableIrPinInterrupts( void );
static void disableIrPinInterrupts( void );
static void createIrRcvrForPin();


static IRrecvPCI* rcvr = nullptr; // PCI = PIN CHANGE Interrupt == Pin Changes from Low to High or High to Low
static void dump();

static volatile uint8_t irPinInterruptFront;
void setup() {
    TurretController::setPins();
    TurretController::turnOffAllIndicators();
    Serial.begin(38400);


    setIrRxPins();
    setInterruptNumbers();
    dumpInterruptNumbers();
    enableIrPinInterrupts();
    //createIrRcvrForPin();
    Serial.println("Started");
}

void loop() {

    //Continue looping until you get a complete signal received
    if (rcvr != nullptr && rcvr->getResults()) {

        dump();
        enableIrPinInterrupts();
        //rcvr->enableIRIn();
        delay(1);
    }
    else if (hitFront) {
        createIrRcvrForPin();
    }
    delay(1);
}

static void dump() {
    Serial.print(F("\n#define RAW_DATA_LEN "));
    Serial.println(recvGlobal.recvLength,DEC);
    Serial.print(F("uint16_t rawData[RAW_DATA_LEN]={\n\t"));
    for(bufIndex_t i=1;i<recvGlobal.recvLength;i++) {
        Serial.print(recvGlobal.recvBuffer[i],DEC);
        Serial.print(F(", "));
        if( (i % 8)==0) Serial.print(F("\n\t"));
    }
    Serial.println(F("1000};"));//Add arbitrary trailing space
}

static void createIrRcvrForPin() {

    rcvr = new IRrecvPCI(IR_SXR_FRONT_PIN);
    rcvr->enableIRIn();
    hitFront = false;
}

static void setIrRxPins() {
    //pinMode(IR_SXR_REAR_PIN, INPUT_PULLUP);
    //pinMode(IR_SXR_RIGHT_PIN, INPUT_PULLUP);
    //pinMode(IR_SXR_LEFT_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_FRONT_PIN, INPUT_PULLUP);
}

static void setInterruptNumbers() {
    irPinInterruptFront = digitalPinToInterrupt(IR_SXR_FRONT_PIN);
}

static void dumpInterruptNumbers() {
    Serial.print("Interrupt Front: ");
    Serial.println(irPinInterruptFront);
}

static void enableIrPinInterrupts( void ) {
    //Indicator::turnOffLed(MOVE_LED_RED);
    //pinMode(IR_SXR_HIT, INPUT_PULLUP);
    //attachInterrupt(IR_SXR_HIT, interruptHandlerHit, RISING);
    //setIrRxPins();
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_REAR_PIN), interruptHandlerRear, RISING);
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_RIGHT_PIN), interruptHandlerRight, FALLING);
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_LEFT_PIN), interruptHandlerLeft, FALLING);
    attachInterrupt(irPinInterruptFront, interruptHandlerFront, CHANGE);
}

static void disableIrPinInterrupts( void ) {
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_REAR_PIN));
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_RIGHT_PIN));
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_LEFT_PIN));
    detachInterrupt(irPinInterruptFront);

    //Indicator::turnOnLed(MOVE_LED_RED);
}

static void initializeRcvr() {

//These first two lines would normally be done by the decoder
//however in rare circumstances there is no decoder.
        recvGlobal.decoderWantsData=false; //turned on by enableIRIn.
        recvGlobal.decodeBuffer=recvGlobal.recvBuffer;//default buffer
        recvGlobal.enableAutoResume=false;
        recvGlobal.frameTimeout=DEFAULT_FRAME_TIMEOUT;
        recvGlobal.frameTimeoutTicks=recvGlobal.frameTimeout/USEC_PER_TICK;
        markExcess=DEFAULT_MARK_EXCESS;
        recvGlobal.newDataAvailable=false;
        recvGlobal.enableBlinkLED=false;
        recvGlobal.currentState=STATE_FINISHED;//i.e. Not running.
    }
}

static void interruptHandlerFront( void ) {
    uint32_t volatile changeTime=micros();
    uint32_t deltaTime=changeTime-recvGlobal.timer;
    switch(recvGlobal.currentState) {
        case STATE_FINISHED: return;
        case STATE_RUNNING:
            IRLib_doBlink();
            if( !(recvGlobal.recvLength & 1) ){
                if (deltaTime>recvGlobal.frameTimeout) {
                    IRLib_IRrecvComplete(1);//all finished, reset and possibly do auto resume
                    return;//don't record final space
                }
            }
            break;
        case STATE_READY_TO_BEGIN:
            if(digitalRead(recvGlobal.recvPin)) {//pin high means SPACE
                return;//don't start until we get a MARK
            } else {
                recvGlobal.currentState=STATE_RUNNING;
            }
            break;
    };
    recvGlobal.recvBuffer[recvGlobal.recvLength]=deltaTime;
    recvGlobal.timer=changeTime;
    if(++recvGlobal.recvLength>=RECV_BUF_LENGTH) {//buffer overflows so we quit
        IRLib_IRrecvComplete(2);
    }
}
