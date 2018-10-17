#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <CannonController.h>
#include <TraverseController.h>
#include <ElevationController.h>
#include <TurretController.h>

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
void ReceiveFunction();
TaskHandle_t receiverHandle = NULL;
TaskHandle_t senderHandle = NULL;

void TaskSender(void* pvParameters) {
    for (;;) {
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
        }
    }

}

void TaskReceiver(void* pvParameters) {
    for (;;) {
        /*
         * Function code
         */
        ReceiveFunction();
        uint32_t receivedValue = 0;
        int clearCountOnExit = pdTRUE;
        TickType_t ticksToWait = 100/portTICK_PERIOD_MS;

        // Allows a task to wait in the Blocked state for its notification value to be greater than zero
        // Either:
                // decrements or clears the task's notification value before it returns
                // clears the task's notification value before it returns
        receivedValue = ulTaskNotifyTake(clearCountOnExit, ticksToWait);
    }
}

void setup() {
    traverseServo->attach(TRAVERSE_SERVO);

    TurretController::initialize(traverseServo);

    TurretController::functionCheckDemo(NULL);
}

void loop() {
    Indicator::turnOnLed(ARD_STATUS_GRN);
    delay(800);
    Indicator::turnOffLed(ARD_STATUS_GRN);
    delay(300);
}
