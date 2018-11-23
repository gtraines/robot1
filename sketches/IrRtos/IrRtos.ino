#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <TurretController.h>
#include <semphr.h>

/* The tasks to be created. */
static void vHandlerTask( void *pvParameters );
/* The service routine for the interrupt.  This is the interrupt that the task
will be synchronized with. */
static void interruptHandlerHit( void );
static void interruptHandlerRear( void );
static void interruptHandlerRight( void );
static void interruptHandlerLeft( void );
static void interruptHandlerFront( void );
/* Declare a variable of type SemaphoreHandle_t.  This is used to reference the
semaphore that is used to synchronize a task with an interrupt. */
static SemaphoreHandle_t xCountingSemaphore = NULL;

static String lastHit = "INITIAL";

void setup() {
    TurretController::setPins();
    TurretController::turnOffAllIndicators();

    Serial.begin(115200);
    Serial.println("Started");

    /* Before a semaphore is used it must be explicitly created.  In this example
    a counting semaphore is created.  The semaphore is created to have a maximum
    count value of 10, and an initial count value of 0. */
    xCountingSemaphore = xSemaphoreCreateCounting( 10, 0 );

    /* Install the interrupt handler. */
//  _dos_setvect( 0x82, vExampleInterruptHandler );
    //pinMode(IR_SXR_HIT, INPUT_PULLUP);
    //attachInterrupt(IR_SXR_HIT, interruptHandlerHit, RISING);

    pinMode(IR_SXR_DIRECTION_REAR, INPUT_PULLUP);
    attachInterrupt(INT0, interruptHandlerRear, RISING);

    pinMode(IR_SXR_DIRECTION_RIGHT, INPUT_PULLUP);
    attachInterrupt(INT1, interruptHandlerRight, RISING);

    pinMode(IR_SXR_DIRECTION_LEFT, INPUT_PULLUP);
    attachInterrupt(INT2, interruptHandlerLeft, RISING);

    pinMode(IR_SXR_DIRECTION_FRONT, INPUT_PULLUP);
    attachInterrupt(INT3, interruptHandlerFront, RISING);

    Indicator::turnOffLed(ARD_STATUS_RED);

    /* Check the semaphore was created successfully. */
    if( xCountingSemaphore != NULL ) {
        /* Create the 'handler' task.  This is the task that will be synchronized
        with the interrupt.  The handler task is created with a high priority to
        ensure it runs immediately after the interrupt exits.  In this case a
        priority of 3 is chosen. */
        xTaskCreate(vHandlerTask, "Handler", 200, NULL, 3, NULL);
    }
}

void loop() {

}

static void vHandlerTask( void *pvParameters )
{
    bool success = true;
    static BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;

    /* As per most tasks, this task is implemented within an infinite loop. */
    Indicator::turnOnLed(ARD_STATUS_GRN);
    while (success) {
        Indicator::alertStrobeFast(ACTY_LED_1);
        BaseType_t semaphoreTaken = xSemaphoreTakeFromISR(xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken);

        if (semaphoreTaken == pdTRUE) {
            Indicator::alertStrobeFast(ACTY_LED_3);
            /* To get here the event must have occurred.  Process the event (in this
            case we just print out a message). */
            Serial.println( "Handler task - Processing event." );
            Serial.println( lastHit );
        }

    }
}

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
        /* Giving the semaphore unblocked a task, and the priority of the
        unblocked task is higher than the currently running task - force
        a context switch to ensure that the interrupt returns directly to
        the unblocked (higher priority) task.

        NOTE: The syntax for forcing a context switch is different depending
        on the port being used.  Refer to the examples for the port you are
        using for the correct method to use! */
        // portSWITCH_CONTEXT();
        vPortYield();
    }
}

static void interruptHandlerRear( void ) {
    static portBASE_TYPE xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;

    lastHit = "REAR";
    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );

    if( xHigherPriorityTaskWoken == pdTRUE )
    {
        /* Giving the semaphore unblocked a task, and the priority of the
        unblocked task is higher than the currently running task - force
        a context switch to ensure that the interrupt returns directly to
        the unblocked (higher priority) task.

        NOTE: The syntax for forcing a context switch is different depending
        on the port being used.  Refer to the examples for the port you are
        using for the correct method to use! */
        // portSWITCH_CONTEXT();
        vPortYield();
    }
}

static void interruptHandlerRight( void ) {

    static portBASE_TYPE xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;
    lastHit = "RIGHT";
    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );

    if( xHigherPriorityTaskWoken == pdTRUE )
    {
        // portSWITCH_CONTEXT();
        vPortYield();
    }
}

static void interruptHandlerLeft( void ) {

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
    static portBASE_TYPE xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;
    lastHit = "FRONT";

    xSemaphoreGiveFromISR( xCountingSemaphore, (BaseType_t*)&xHigherPriorityTaskWoken );

    if( xHigherPriorityTaskWoken == pdTRUE ) {
        // portSWITCH_CONTEXT();
        vPortYield();
    }
}

