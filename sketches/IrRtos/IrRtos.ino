#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <TurretController.h>
#include <IrParams.h>
#include <IrRxBase.h>
#include <Taskr.h>

#define TURRET_DEBUG true


Servo* traverseServo = new Servo();

static void vHandlerTask( void *pvParameters );
static void dump(decode_results* hashedResults);

static void configureTimer();
static void enableTimerInterrupt( void );
static void disableTimerInterrupt( void );

static void setIrRxPins();
static void enableIrPinInterrupts( void );
static void disableIrPinInterrupts( void );

static void interruptHandlerHit( void );
static void interruptHandlerRear( void );
static void interruptHandlerRight( void );
static void interruptHandlerLeft( void );
static void interruptHandlerFront( void );
static SemaphoreHandle_t xCountingSemaphore = NULL;
static IrParams_t testIrParams;
static volatile uint16_t signalCount = 0;
static String lastHit = "INITIAL";

void setup() {

    testIrParams = IrParams_t();
    IrRxBase::resume(testIrParams);

    xCountingSemaphore = xSemaphoreCreateCounting( 1, 0 ); // maxcount, initial count
    configureTimer();
    disableTimerInterrupt();
    enableIrPinInterrupts();

    Serial.begin(38400);
    Serial.println("Started");
    Serial.println("Configuration:");
    Serial.print("Gap size (50us tics): ");
    Serial.println(GAP_TICKS);

    traverseServo->attach(TRAVERSE_SERVO);
    TurretController::initialize(traverseServo);

    if( xCountingSemaphore != NULL ) {
        /* Create the 'handler' task.  This is the task that will be synchronized
        with the interrupt.  The handler task is created with a high priority to
        ensure it runs immediately after the interrupt exits.  In this case a
        priority of 3 is chosen. */
        xTaskCreate(vHandlerTask, "Handler", 512, NULL, 2, NULL);
    } else {
        Indicator::turnOnLed(ARD_STATUS_RED);
    }

}

void loop() {

}

// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
//void dump(void *v) {
//  decode_results *results = (decode_results *)v
static void dump(decode_results *results) {
    Serial.print(" Value: ");
    Serial.print(results->value, HEX);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(")");
}


static void vHandlerTask( void *pvParameters ) {
    bool success = true;
    static BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    uint8_t lastSigCount = 0;
    decode_results* hashedSignal = nullptr;
    while (success) {
        BaseType_t semaphoreTaken = xSemaphoreTakeFromISR(xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken);

        if (semaphoreTaken == pdTRUE && lastHit != "CLEARED") {

            IrRxBase::processSignalsIn(testIrParams);
            enableTimerInterrupt();

            /*
             * PROCESS EACH SIGNAL!!!
             */

            Indicator::turnOnLed(ACTY_LED_3);
            /* To get here the event must have occurred.  Process the event (in this
            case we just print out a message). */
            Serial.println(lastHit);
            lastSigCount = RAWBUF + 1;
            hashedSignal = new decode_results();

            while (testIrParams.rawlen <= RAWBUF
                   && lastSigCount != testIrParams.rawlen
                   && testIrParams.rcvstate != STATE_STOP) {
                lastSigCount = testIrParams.rawlen;
                Taskr::delayMs(90);
            }

            disableTimerInterrupt();
            if (TURRET_DEBUG) {
                for (int i = 0; i < testIrParams.rawlen; ++i) {
                    Serial.print(testIrParams.rawbuf[i]);
                    Serial.print(",");
                }
                Serial.println();
                Serial.print("State:");
                Serial.println(testIrParams.rcvstate);
                Serial.print("End timer value: ");
                Serial.println(testIrParams.timer);
                if (IrRxBase::decode(testIrParams, hashedSignal) > 0) {
                    //Serial.println(hashedSignal->value);
                    dump(hashedSignal);
                } else {
                    Serial.print("Finished a loop without a complete signal; code: ");
                    Serial.println(IrRxBase::decode(testIrParams, hashedSignal));
                }
            }

            lastHit = "CLEARED";
            IrRxBase::resume(testIrParams);
            Indicator::turnOffLed(ACTY_LED_3);
            enableIrPinInterrupts();
        }

        Taskr::delayMs(30);
    }
}

static void setIrRxPins() {
    pinMode(IR_SXR_REAR_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_RIGHT_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_LEFT_PIN, INPUT_PULLUP);
    pinMode(IR_SXR_FRONT_PIN, INPUT_PULLUP);
}

static void enableIrPinInterrupts( void ) {
    Indicator::turnOffLed(MOVE_LED_RED);
    //pinMode(IR_SXR_HIT, INPUT_PULLUP);
    //attachInterrupt(IR_SXR_HIT, interruptHandlerHit, RISING);
    setIrRxPins();
    attachInterrupt(digitalPinToInterrupt(IR_SXR_REAR_PIN), interruptHandlerRear, RISING);
    attachInterrupt(digitalPinToInterrupt(IR_SXR_RIGHT_PIN), interruptHandlerRight, RISING);
    attachInterrupt(digitalPinToInterrupt(IR_SXR_LEFT_PIN), interruptHandlerLeft, RISING);
    attachInterrupt(digitalPinToInterrupt(IR_SXR_FRONT_PIN), interruptHandlerFront, RISING);
}

static void disableIrPinInterrupts( void ) {
    detachInterrupt(digitalPinToInterrupt(IR_SXR_REAR_PIN));
    detachInterrupt(digitalPinToInterrupt(IR_SXR_RIGHT_PIN));
    detachInterrupt(digitalPinToInterrupt(IR_SXR_LEFT_PIN));
    detachInterrupt(digitalPinToInterrupt(IR_SXR_FRONT_PIN));

    Indicator::turnOnLed(MOVE_LED_RED);
}

static void enableTimerInterrupt( void ) {

    //Timer2 Overflow Interrupt Enable
    // Set Bit on Timer Mask 2, Timer Overflow Interrupt Enable
    // setup pulse clock timer interrupt
    TCCR2A = 0;  // normal mode

    // Prescale /8 (16M/8 = 0.5 microseconds per tick)
    // Therefore, the timer interval can range from 0.5 to 128 microseconds
    // depending on the reset value (255 to 0)
    cbi(TCCR2B,CS22);
    sbi(TCCR2B,CS21);
    cbi(TCCR2B,CS20);


    sbi(TIMSK2,TOIE2);

    RESET_TIMER2;
    sei();
}

static void disableTimerInterrupt( void ) {

    // Clear Bit on Timer Mask 2, Timer Overflow Interrupt Enable
    cbi(TIMSK2,TOIE2);
    Indicator::turnOffLed(ARD_STATUS_RED);
}

static void configureTimer() {
    // setup pulse clock timer interrupt
    TCCR2A = 0;  // normal mode

    // Prescale /8 (16M/8 = 0.5 microseconds per tick)
    // Therefore, the timer interval can range from 0.5 to 128 microseconds
    // depending on the reset value (255 to 0)
    cbi(TCCR2B,CS22);
    sbi(TCCR2B,CS21);
    cbi(TCCR2B,CS20);

}

static void processTimerInterrupt() {
    Indicator::turnOnLed(ARD_STATUS_RED);
    IrRxBase::processSignalsIn(testIrParams);
}

ISR(TIMER2_OVF_vect) {
    RESET_TIMER2;
    processTimerInterrupt();

};


static void interruptHandlerHit( void ) {
    static portBASE_TYPE xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;

    /* 'Give' the semaphore multiple times.  The first will unblock the handler
    task, the following 'gives' are to demonstrate that the semaphore latches
    the events to allow the handler task to process them in turn without any
    events getting lost.  This simulates multiple interrupts being taken by the
    processor, even though in this case the events are simulated within a single
    interrupt occurrence.*/
    lastHit = "HIT";
    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );

    if( xHigherPriorityTaskWoken == pdTRUE ) {
        /*
        NOTE: The syntax for forcing a context switch is different depending
        on the port being used.  Refer to the examples for the port you are
        using for the correct method to use! */
        // portSWITCH_CONTEXT();
        vPortYield();
    }
}

static void interruptHandlerRear( void ) {
    disableIrPinInterrupts();

    testIrParams.recvpin = IR_SXR_REAR_PIN;
    IrRxBase::processSignalsIn(testIrParams);

    static portBASE_TYPE xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;

    lastHit = "REAR";
    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );

    if( xHigherPriorityTaskWoken == pdTRUE )
    {
        vPortYield();
    }
}

static void interruptHandlerRight( void ) {
    disableIrPinInterrupts();

    testIrParams.recvpin = IR_SXR_RIGHT_PIN;
    IrRxBase::processSignalsIn(testIrParams);

    static portBASE_TYPE xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;
    lastHit = "RIGHT";
    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );

    if( xHigherPriorityTaskWoken == pdTRUE ) {
        vPortYield();
    }
}

static void interruptHandlerLeft( void ) {
    disableIrPinInterrupts();

    testIrParams.recvpin = IR_SXR_LEFT_PIN;
    IrRxBase::processSignalsIn(testIrParams);

    static portBASE_TYPE xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;

    lastHit = "LEFT";
    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );

    if( xHigherPriorityTaskWoken == pdTRUE ) {
        // portSWITCH_CONTEXT();
        vPortYield();
    }
}

static void interruptHandlerFront( void ) {
    disableIrPinInterrupts();

    testIrParams.recvpin = IR_SXR_FRONT_PIN;
    IrRxBase::processSignalsIn(testIrParams);

    static portBASE_TYPE xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;
    lastHit = "FRONT";

    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );

    if( xHigherPriorityTaskWoken == pdTRUE ) {
        // portSWITCH_CONTEXT();
        vPortYield();
    }
}

