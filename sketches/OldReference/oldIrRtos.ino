#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
//#include <Arduino_FreeRTOS.h>
//#include <task.h>
//#include <semphr.h>
#include <TurretPins.h>
#include <Indicator.h>
//#include <TurretController.h>
#include <IrParams.h>
#include <IrRxBase.h>
//#include <Taskr.h>
#include <pins_arduino.h>
#include <IrInterruptConfig.h>
#include <decode_results.h>
#include <IRLibProtocols.h>
#define TURRET_DEBUG true


//Servo* traverseServo = new Servo();

//static void vHandlerTask( void *pvParameters );
static void dump(volatile decode_results* hashedResults);
static void resetDecodeResults();
static void processSignalsIn(volatile IrParams_t* irParams);
static void configureTimer();
static void enableTimerInterrupt( void );
static void disableTimerInterrupt( void );

static void setIrRxPins();
static void enableIrPinInterrupts( void );
static void disableIrPinInterrupts( void );

static void interruptHandlerHit( void );
static void interruptHandlerRear( void );
static void interruptHandlerRight( void );
static void interruptHandlerBase( void );
static void interruptHandlerFront( void );

//static SemaphoreHandle_t xCountingSemaphore = NULL;
static volatile IrParams_t* testIrParams = new IrParams_t();
static volatile uint16_t signalCount = 0;
static String lastHit = "INITIAL";
static volatile decode_results* decodeResults = new decode_results();
//static portBASE_TYPE xHigherPriorityTaskWoken;


void setup() {
    setIrRxPins();
    configureTimer();
    IrRxBase::resume(testIrParams);

    //xCountingSemaphore = xSemaphoreCreateCounting( 1, 0 ); // maxcount, initial count

    disableTimerInterrupt();
    enableIrPinInterrupts();

    Serial.begin(38400);
    Serial.println("Started");
    Serial.println("Configuration:");
    Serial.print("Gap size (50us tics): ");
    Serial.println(GAP_TICKS);

    //traverseServo->attach(TRAVERSE_SERVO);
    //TurretController::initialize(traverseServo);

//    if( xCountingSemaphore != NULL ) {
//        /* Create the 'handler' task.  This is the task that will be synchronized
//        with the interrupt.  The handler task is created with a high priority to
//        ensure it runs immediately after the interrupt exits.  In this case a
//        priority of 3 is chosen. */
//        xTaskCreate(vHandlerTask, "Handler", 512, NULL, 2, NULL);
//    } else {
//        Indicator::turnOnLed(ARD_STATUS_RED);
//    }

}

void loop() {

}

// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
//void dump(void *v) {
//  decode_results *results = (decode_results *)v
static void dump(volatile decode_results* results) {

    if (TURRET_DEBUG) {
        Serial.println(lastHit);
        Serial.print("Signals: ");
        Serial.println(testIrParams->rawlen);
        for (int i = 0; i < testIrParams->rawlen; ++i) {
            Serial.print(testIrParams->rawbuf[i]);
            Serial.print(",");
        }
        Serial.println();
        Serial.print("State:");
        Serial.println(testIrParams->rcvstate);
        Serial.print("End timer value: ");
        Serial.println(testIrParams->timer);

        if (IrRxBase::decode(testIrParams, results) > 0) {
            //Serial.println(hashedSignal->value);
            Serial.print(" Value: ");
            Serial.print(results->value, HEX);
            Serial.print(" (");
            Serial.print(results->bits, DEC);
            Serial.println(")");
        } else {
            Serial.print("Finished a loop without a complete signal; code: ");
            Serial.println(IrRxBase::decode(testIrParams, results));
        }

        Serial.println();
    }
}



static void setIrRxPins() {
    //pinMode(IR_SXR_REAR_PIN, INPUT_PULLUP);
    //pinMode(IR_SXR_RIGHT_PIN, INPUT);
    //pinMode(IR_SXR_LEFT_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_FRONT_PIN, INPUT);
}

static void enableIrPinInterrupts( void ) {
    Indicator::turnOffLed(MOVE_LED_RED);
    //pinMode(IR_SXR_HIT, INPUT_PULLUP);
    //attachInterrupt(IR_SXR_HIT, interruptHandlerHit, RISING);
    //setIrRxPins();
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_REAR_PIN), interruptHandlerRear, RISING);
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_RIGHT_PIN), interruptHandlerRight, FALLING);
    //attachInterrupt(digitalPinToInterrupt(IR_SXR_LEFT_PIN), interruptHandlerLeft, FALLING);
    attachInterrupt(digitalPinToInterrupt(IR_SXR_FRONT_PIN), interruptHandlerBase, RISING);
}

static void disableIrPinInterrupts( void ) {
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_REAR_PIN));
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_RIGHT_PIN));
    //detachInterrupt(digitalPinToInterrupt(IR_SXR_LEFT_PIN));
    detachInterrupt(digitalPinToInterrupt(IR_SXR_FRONT_PIN));

    Indicator::turnOnLed(MOVE_LED_RED);
}

static void enableTimerInterrupt( void ) {

    TIMER_ENABLE_INTR;
    TIMER_RESET;
    sei();
}

static void disableTimerInterrupt( void ) {

    // Clear Bit on Timer Mask 2, Timer Overflow Interrupt Enable
    TIMER_DISABLE_INTR;
    Indicator::turnOffLed(ARD_STATUS_RED);
}

static void configureTimer() {
    // setup pulse clock timer interrupt
    TIMER_CONFIG_NORMAL();
}

static void processTimerInterrupt() {
    Indicator::turnOnLed(ARD_STATUS_RED);
    processSignalsIn(testIrParams);

}

ISR(TIMER_INTR_NAME) {
    TIMER_RESET;
    processTimerInterrupt();
};

static void resetDecodeResults() {
    decodeResults->rawlen = 0;
    decodeResults->value = 0l;
    decodeResults->bits = 0;
    decodeResults->decode_type = 0;
}

static void interruptHandlerBase( void ) {
    disableIrPinInterrupts();

    testIrParams->recvpin = IR_SXR_FRONT_PIN;
    lastHit = "FRONT";
    testIrParams->rcvstate = STATE_MARK;

    enableTimerInterrupt();

    Indicator::turnOnLed(ACTY_LED_3);

    signalCount = RAWBUF + 1;

    while (testIrParams->rawlen <= RAWBUF
           && signalCount != testIrParams->rawlen
           && testIrParams->rcvstate != STATE_STOP) {
        signalCount = testIrParams->rawlen;
        delay(90);
    }

    disableTimerInterrupt();
    dump(decodeResults);

    lastHit = "CLEARED";
    resetDecodeResults();
    IrRxBase::resume(testIrParams);

    Indicator::turnOffLed(ACTY_LED_3);
    enableIrPinInterrupts();
}


static void processSignalsIn(volatile IrParams_t* irParams) {
    volatile uint8_t irdata = (uint8_t) digitalRead(irParams->recvpin);
    //Serial.print("IrData read: ");
    //Serial.println(irdata);
    irParams->timer++; // One more 50us tick
    if (irParams->rawlen >= RAWBUF) {
        // Buffer overflow
        irParams->rcvstate = STATE_STOP;
    }
    switch (irParams->rcvstate) {
        case STATE_IDLE: // In the middle of a gap
            if (irdata == MARK) {
                if (irParams->timer < GAP_TICKS) {
                    // Not big enough to be a gap.
                    irParams->timer = 0;
                } else {
                    // gap just ended, record duration and start recording transmission
                    irParams->rawlen = 0;
                    irParams->rawbuf[irParams->rawlen++] = irParams->timer;
                    irParams->timer = 0;
                    irParams->rcvstate = STATE_MARK;
                }
            }
            break;
        case STATE_MARK: // timing MARK
            if (irdata == SPACE) {   // MARK ended, record time
                irParams->rawbuf[irParams->rawlen++] = irParams->timer;
                irParams->timer = 0;
                irParams->rcvstate = STATE_SPACE;
            }
            break;
        case STATE_SPACE: // timing SPACE
            if (irdata == MARK) { // SPACE just ended, record it
                irParams->rawbuf[irParams->rawlen++] = irParams->timer;
                irParams->timer = 0;
                irParams->rcvstate = STATE_MARK;
            } else { // SPACE
                if (irParams->timer > GAP_TICKS) {
                    // big SPACE, indicates gap between codes
                    // Mark current code as ready for processing
                    // Switch to STOP
                    // Don't reset timer; keep counting space width
                    irParams->rcvstate = STATE_STOP;
                }
            }
            break;
        case STATE_STOP: // waiting, measuring gap
            if (irdata == MARK) { // reset gap timer
                irParams->timer = 0;
            }
            break;
        default:break;

    }
    Serial.print("Current Rx State: ");
    Serial.println(irParams->rcvstate);
    Serial.print("Timer value: ");
    Serial.println(irParams->timer);
}

//static void interruptHandlerFront( void ) {
//    disableIrPinInterrupts();
//
//    testIrParams.recvpin = IR_SXR_FRONT_PIN;
//    IrRxBase::processSignalsIn(testIrParams);
//
//    static portBASE_TYPE xHigherPriorityTaskWoken;
//
//    xHigherPriorityTaskWoken = pdFALSE;
//    lastHit = "FRONT";
//
//    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );
//
//    if( xHigherPriorityTaskWoken == pdTRUE ) {
//        // portSWITCH_CONTEXT();
//        vPortYield();
//    }
//}

//
//static void vHandlerTask( void *pvParameters ) {
//    bool success = true;
//    xHigherPriorityTaskWoken = pdFALSE;
//
//    while (success) {
//        BaseType_t semaphoreTaken = xSemaphoreTakeFromISR(xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken);
//
//        if (semaphoreTaken == pdTRUE && lastHit != "CLEARED") {
//
//
//
//            /*
//             * PROCESS EACH SIGNAL!!!
//             */
//
//            Indicator::turnOnLed(ACTY_LED_3);
//
//            signalCount = RAWBUF + 1;
//
//            while (testIrParams.rawlen <= RAWBUF
//                   && signalCount != testIrParams.rawlen
//                   && testIrParams.rcvstate != STATE_STOP) {
//                signalCount = testIrParams.rawlen;
//                Taskr::delayMs(135);
//            }
//
//            disableTimerInterrupt();
//            dump(decodeResults);
//
//            lastHit = "CLEARED";
//            resetDecodeResults();
//            IrRxBase::resume(testIrParams);
//
//            Indicator::turnOffLed(ACTY_LED_3);
//            enableIrPinInterrupts();
//        }
//
//        Taskr::delayMs(45);
//    }
//}


//static void interruptHandlerHit( void ) {
//    xHigherPriorityTaskWoken = pdFALSE;
//
//    /* 'Give' the semaphore multiple times.  The first will unblock the handler
//    task, the following 'gives' are to demonstrate that the semaphore latches
//    the events to allow the handler task to process them in turn without any
//    events getting lost.  This simulates multiple interrupts being taken by the
//    processor, even though in this case the events are simulated within a single
//    interrupt occurrence.*/
//    lastHit = "HIT";
//    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );
//
//    if( xHigherPriorityTaskWoken == pdTRUE ) {
//        /*
//        NOTE: The syntax for forcing a context switch is different depending
//        on the port being used.  Refer to the examples for the port you are
//        using for the correct method to use! */
//        // portSWITCH_CONTEXT();
//        vPortYield();
//    }
//}

//static void interruptHandlerRear( void ) {
//    disableIrPinInterrupts();
//
//    testIrParams.recvpin = IR_SXR_REAR_PIN;
//    IrRxBase::processSignalsIn(testIrParams);
//
//    xHigherPriorityTaskWoken = pdFALSE;
//
//    lastHit = "REAR";
//    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );
//
//    if( xHigherPriorityTaskWoken == pdTRUE ) {
//        vPortYield();
//    }
//}

//static void interruptHandlerRight( void ) {
//    disableIrPinInterrupts();
//
//    testIrParams.recvpin = IR_SXR_RIGHT_PIN;
//    enableTimerInterrupt();
//
//    xHigherPriorityTaskWoken = pdFALSE;
//    lastHit = "RIGHT";
//    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );
//
//    if( xHigherPriorityTaskWoken == pdTRUE ) {
//        vPortYield();
//    }
//}
