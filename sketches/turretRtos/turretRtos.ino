#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <CannonController.h>
#include <TraverseController.h>
#include <ElevationController.h>
#include <TurretController.h>
#include <HardwareSerial.h>

Servo* traverseServo = new Servo();


// Set configUSE_TASK_NOTIFICATIONS 1

/*
 * When configUSE_TASK_NOTIFICATIONS is set to 1, each task has a Notification State
 * Notification State = Pending | Not-Pending (uint32)
 * When a task receives a notification, its notification state is set to Pending
 * When a task READS its notification, its notification state is set to Not-Pending
 *
 * A task can wait in the Blocked state (with an optional time out) for its notification state
 * to become pending
 */
void TaskSender(void* pvParameters);
void SendFunction();
void TaskReceiver(void* pvParameters);
void TaskHandler(void* pvParameters);
void ReceiveFunction();
TaskHandle_t receiverHandle = NULL;
TaskHandle_t senderHandle = NULL;

void TaskSender(void* pvParameters) {
    for (int idx = 0; idx < INTMAX_MAX; idx++) {
        /* Write function code here */

        // Function code

        /* At some point, TaskSender sends an event to TaskReceiver
         *
         * */
        SendFunction();
        eNotifyAction actionEnumVal = eIncrement;
        uint16_t msgValue = 1;

        int something = xTaskNotifyGive(receiverHandle);  // This calls xTaskNotify(receiverHandle, msgValue, actionEnumVal);
        if (something == pdPASS) {
            // blah
            // Clear out waiting notification
        }
    }

}

void TaskReceiver(void* pvParameters) {
    for (int idx = 0; idx < INTMAX_MAX; idx++) {
        /*
         * Function code
         */

        uint32_t receivedValue = 0; // calling task's notification BEFORE it was cleared or decremented
        int clearCountOnExit = pdTRUE; // if pdTRUE: calling task's notification value is set to 0 BEFORE the call returns
        // if pdFALSE AND the calling task's notification value is > 0,
        // THEN the calling task's notification value will be DECREMENTED before the call to ulTaskNotifyTake returns
        TickType_t ticksToWait = 100/portTICK_PERIOD_MS; // MAX time the task should remain in Blocked state to wait for its notification
        // value to be > 0
        // setting to portMAX_DELAY will cause the task to wait INDEFINITELY, provided INCLUDE_vTaskSuspend 1 in FreeRTOSConfig.h

        // Allows a task to wait in the Blocked state for its notification value to be greater than zero
        // Either:
        // decrements or clears the task's notification value before it returns
        // clears the task's notification value before it returns
        receivedValue = ulTaskNotifyTake(clearCountOnExit, ticksToWait);

        if (receivedValue > 0) {
            ReceiveFunction();
        }
    }
}

/* The rate at which the periodic task generates software interrupts. */
const TickType_t xInterruptFrequency = pdMS_TO_TICKS( 500UL );
void TaskHandler( void *pvParameters ) {
    /* xMaxExpectedBlockTime is set to be a little longer than the maximum expected time between events. */
    const TickType_t xMaxExpectedBlockTime = xInterruptFrequency + pdMS_TO_TICKS( 90 );
    uint32_t ulEventsToProcess;
    /* As per most tasks, this task is implemented within an infinite loop. */
    for(int idx = 0; idx < 1000; idx++)
    {
        /* Wait to receive a notification sent directly to this task from the interrupt service routine. */
        ulEventsToProcess = ulTaskNotifyTake( pdTRUE, xMaxExpectedBlockTime );
        if( ulEventsToProcess != 0 )
        {
            /* To get here at least one event must have occurred. Loop here until all the pending events have been
             * processed (in this case, just print out a message for each event).
             * */
            while( ulEventsToProcess > 0 )
            {
                Serial.print("Handler task - Processing event.\r\n" );
                ulEventsToProcess--;
            }
        }
        else
        {
            /* If this part of the function is reached then an interrupt did not arrive within the expected time,
             * and (in a real application) it may be necessary to perform some error recovery operations. */
        }
    }
}

void setup() {
    traverseServo->attach(TRAVERSE_SERVO);

    TurretController::initialize(traverseServo);
}

void loop() {

}