#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <TurretPins.h>
#include <Indicator.h>
#include <TraverseController.h>
#include <ElevationController.h>

void setPins();
boolean turnOffAllIndicators();
void setArdStatusGood();
void setArdStatusError();

void TaskIndicatorTest(void* pvParameters);
void TaskCannonTest(void* pvParameters);
void TaskTraverseTest(void* pvParameters);
void TaskElevationTest(void* pvParameters);


TaskHandle_t xTaskHandleIndicatorTest = NULL;
TaskHandle_t xTaskHandleCannonTest = NULL;
TaskHandle_t xTaskHandleElevationTest = NULL;
TaskHandle_t xTaskHandleTraverseTest = NULL;

Servo* traverseServo;
ElevationController* elevationController = new ElevationController();
TraverseController* traverseController;

void setup() {
    setPins();
    
    if (turnOffAllIndicators()) {
        setArdStatusGood();
    } else {
        setArdStatusError();
    }

    /* Would prefer to do this some other way, but something about the Servo obj
     * gets weird when I instantiate it inside of the TraverseController
     * Probably the same issue I had with the SpeedController
     */
    traverseServo = new Servo();
    traverseServo->attach(TRAVERSE_SERVO);
    traverseController = new TraverseController(traverseServo);
    
    xTaskCreate(
      TaskIndicatorTest
    ,  (const portCHAR *) "IndicatorTest"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  &xTaskHandleIndicatorTest );

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

void setArdStatusGood() {
    Indicator::turnOffLed(ARD_STATUS_RED);
    Indicator::turnOnLed(ARD_STATUS_GRN);
}

void setArdStatusError() {
    Indicator::turnOffLed(ARD_STATUS_GRN);
    Indicator::turnOnLed(ARD_STATUS_RED);
}

void setPins() {
    pinMode(ELEVATION_MOTOR_ENABLE, OUTPUT);
    pinMode(ELEVATION_MOTOR_POS, OUTPUT);
    pinMode(ELEVATION_MOTOR_NEG, OUTPUT);

    pinMode(ARD_STATUS_GRN, OUTPUT);
    pinMode(ARD_STATUS_RED, OUTPUT);

    pinMode(ACTY_LED_1, OUTPUT);
    pinMode(ACTY_LED_2, OUTPUT);
    pinMode(ACTY_LED_3, OUTPUT);

    pinMode(MOVE_LED_GRN, OUTPUT);
    pinMode(MOVE_LED_RED, OUTPUT);
    pinMode(MOVE_LED_BLUE, OUTPUT);

    pinMode(CANNON_LED, OUTPUT);
}

boolean turnOffAllIndicators() {
    Indicator::turnOffLed(ARD_STATUS_GRN);
    Indicator::turnOffLed(ARD_STATUS_RED);

    Indicator::turnOffLed(ACTY_LED_1);
    Indicator::turnOffLed(ACTY_LED_2);
    Indicator::turnOffLed(ACTY_LED_3);

    Indicator::turnOffLed(MOVE_LED_GRN);
    Indicator::turnOffLed(MOVE_LED_RED);
    Indicator::turnOffLed(MOVE_LED_BLUE);

    Indicator::turnOffLed(CANNON_LED);

    return true;
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

