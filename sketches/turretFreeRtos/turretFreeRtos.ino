 
#include <Arduino.h>
#include <Indicator.h>
#include <PotMotor.h>

#include <TurretPins.h>
#include <ElevationConfig.h>
#include <IndicatorConfig.h>
#include <IrConfig.h>
#include <TraverseConfig.h>

#include <ElevationController.h>
#include <IrCannonController.h>

#include <HardwareSerial.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>

void TaskElevationTest( void *pvParameters );
void TaskIndicatorTest( void *pvParameters );
void TaskCannonTest( void *pvParameters );

ElevationController* elevationController = new ElevationController();
IrCannonController* cannonController = new IrCannonController();

void printInt(int intToPrint) {
  indicateTx();
  Serial.println(intToPrint);
}

void setup() {
  Serial.begin(115200);

  setPins();

  if (turnOffAllIndicators()) {
    setArdStatusGood();
  } else {
    setArdStatusError();
  }

  createAndStartTasks();
}

void createAndStartTasks() {
    // Now set up two tasks to run independently.
  xTaskCreate(
    TaskElevationTest
    ,  (const portCHAR *)"ElevationTest"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );
    
  xTaskCreate(
    TaskCannonTest
    ,  (const portCHAR *) "IndicatorTest"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  xTaskCreate(
    TaskIndicatorTest
    ,  (const portCHAR *) "CannonTest"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

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

void setArdStatusGood() {
  Indicator::turnOffLed(ARD_STATUS_RED);
  Indicator::turnOnLed(ARD_STATUS_GRN);
}

void setArdStatusError() {
  Indicator::turnOffLed(ARD_STATUS_GRN);
  Indicator::turnOnLed(ARD_STATUS_RED);
}

void indicateRx() {
  Indicator::momentaryLedOn(ACTY_LED_3);
}

void indicateTx() {
  Indicator::momentaryLedOn(ACTY_LED_1);
}

/*
 * Thread 1, turn the LED off when signalled by thread 2.
 */
// Declare the thread function for thread 1.
void TaskElevationTest( void *pvParameters ) {
    for (;;) {
        elevationController->demoFunctionCheck();
    }
}

void TaskCannonTest( void *pvParameters ) {
    for (;;) {
        cannonController->demoFunctionCheck();
    }
}
/*
 * Thread 2, turn the LED on and signal thread 1 to turn the LED off.
 */
// Declare the thread function for TaskIndicatorTest
void TaskIndicatorTest( void* pvParameters ) {

  for (;;) // A Task shall never return or exit.
  {
    Indicator::momentaryLedOn(ACTY_LED_1);
    Indicator::momentaryLedOn(ACTY_LED_2);
    Indicator::momentaryLedOn(ACTY_LED_3);
  
    Indicator::momentaryLedOn(MOVE_LED_GRN);
    Indicator::momentaryLedOn(MOVE_LED_RED);
    Indicator::momentaryLedOn(MOVE_LED_BLUE);

    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    
    Indicator::alertBlink(ACTY_LED_1);
    Indicator::alertBlink(ACTY_LED_2);
    Indicator::alertBlink(ACTY_LED_3);
  
    Indicator::alertStrobeFast(MOVE_LED_GRN);
    Indicator::alertStrobeFast(MOVE_LED_RED);
    Indicator::alertStrobeFast(MOVE_LED_BLUE);
    
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    
    Indicator::alertBlinkFast(ACTY_LED_1);
    Indicator::alertBlinkFast(ACTY_LED_2);
    Indicator::alertBlinkFast(ACTY_LED_3);
  
    Indicator::alertStrobeSlow(MOVE_LED_GRN);
    Indicator::alertStrobeSlow(MOVE_LED_RED);
    Indicator::alertStrobeSlow(MOVE_LED_BLUE);
    
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    
  }
}

void loop() {

}
