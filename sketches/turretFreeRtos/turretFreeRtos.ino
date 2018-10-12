#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <TraverseController.h>
#include <ElevationController.h>
#include <TurretController.h>


void TaskIndicatorTest(void* pvParameters);
void TaskCannonTest(void* pvParameters);
void TaskTraverseTest(void* pvParameters);
void TaskElevationTest(void* pvParameters);

TaskHandle_t xTaskHandleIndicatorTest = NULL;
TaskHandle_t xTaskHandleCannonTest = NULL;
TaskHandle_t xTaskHandleElevationTest = NULL;
TaskHandle_t xTaskHandleTraverseTest = NULL;

Servo* traverseServo;
TurretController* turretController;
ElevationController* elevationController = new ElevationController();
TraverseController* traverseController;

void setup() {

    traverseServo = new Servo();
    traverseServo->attach(TRAVERSE_SERVO);
    turretController = new TurretController(traverseServo);

    xTaskCreate(
            TaskIndicatorTest
            ,  (const portCHAR *) "IndicatorTest"
            ,  128  // Stack size
            ,  NULL
            ,  1  // Priority
            ,  &xTaskHandleIndicatorTest);

    xTaskCreate(
            TaskTraverseTest
            ,  (const portCHAR *) "TraverseTest"
            ,  512  // Stack size
            ,  NULL
            ,  1  // Priority
            ,  &xTaskHandleTraverseTest);

    xTaskCreate(
            TaskElevationTest
            ,  (const portCHAR *) "ElevationTest"
            ,  512  // Stack size
            ,  NULL
            ,  1  // Priority
            ,  &xTaskHandleElevationTest);

    xTaskCreate(
            TaskCannonTest
            ,  (const portCHAR *) "CannonTest"
            ,  128  // Stack size
            ,  NULL
            ,  1  // Priority
            ,  &xTaskHandleCannonTest );

}

void loop() {

}

void TaskElevationTest( void *pvParameters ) {
    for (int idx = 0; idx < 2; idx++) {
        elevationController->functionCheckDemo();
    }
    vTaskDelete(NULL);
}

void TaskTraverseTest( void *pvParameters ) {

    for (int idx = 0; idx < 2; idx++) {
        traverseController->functionCheckDemo();
    }
    vTaskDelete(xTaskHandleTraverseTest);
}

void TaskCannonTest( void *pvParameters ) {

    for (int idx = 0; idx < 2; idx++) {
        Indicator::alertStrobeSlow(CANNON_LED);
        vTaskDelay(500/portTICK_PERIOD_MS);
        Indicator::alertStrobeFast(CANNON_LED);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
    vTaskDelete(xTaskHandleCannonTest);
}

// Declare the thread function for TaskIndicatorTest
void TaskIndicatorTest( void* pvParameters ) {

    Indicator::alertBlinkFast(ACTY_LED_1);
    Indicator::alertBlinkFast(ACTY_LED_2);
    Indicator::alertBlinkFast(ACTY_LED_3);

    Indicator::alertStrobeSlow(MOVE_LED_GRN);
    Indicator::alertStrobeSlow(MOVE_LED_RED);
    Indicator::alertStrobeSlow(MOVE_LED_BLUE);


    vTaskDelete(xTaskHandleIndicatorTest);
}

