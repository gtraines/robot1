
#include <Arduino.h>
#include <Indicator.h>
#include <PotMotor.h>

#include <TurretPins.h>
#include <ElevationConfig.h>
#include <IndicatorConfig.h>
#include <IrConfig.h>
#include <TraverseConfig.h>

#include <HardwareSerial.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

SemaphoreHandle_t xSerialSemaphore;
const uint16_t intervalTicks = 10;

void TaskElevationTest( void *pvParameters );
void TaskIndicatorTest( void *pvParameters );

PotMotor* _elevationMotor = NULL;

void printInt(int intToPrint) {
  indicateTx();
  Serial.println(intToPrint);
}

void setup() {
  Serial.begin(115200);

  setPins();

  _elevationMotor = new PotMotor((int)ELEVATION_MOTOR_ENABLE, 
    (int)ELEVATION_MOTOR_POS, (int)ELEVATION_MOTOR_NEG, (int)ELEVATION_MOTOR_POSITION, 
    (int)ELEVATION_MIN, (int)ELEVATION_MAX, (int)ELEVATION_RESOLUTION, 
    (int)MOTOR_MIN_SPEED, (int)MOTOR_MAX_SPEED, (int)MOTOR_MED_SPEED, (int)MOTOR_JERK_SPEED);
  
  _elevationMotor->setReadingDelay(MOTOR_UPDATE_INTERVAL);

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
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskIndicatorTest
    ,  (const portCHAR *) "IndicatorTest"
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
  for (int iter=0; iter<10; iter++) {
    _elevationMotor->moveTo(ELEVATION_MIN);
    _elevationMotor->moveTo(ELEVATION_MAX);
    _elevationMotor->moveTo(500);
    _elevationMotor->moveTo(600);
    vTaskDelay(500/portTICK_PERIOD_MS);
    
    Indicator::strobeLed(CANNON_LED, 10);
    
    _elevationMotor->moveTo(320);
    _elevationMotor->moveTo(700);
    _elevationMotor->moveTo(500);
    _elevationMotor->moveTo(320);
    _elevationMotor->moveTo(600);

    vTaskDelay(500/portTICK_PERIOD_MS);
    Indicator::strobeLed(CANNON_LED, 10);
    _elevationMotor->moveTo(350);
    _elevationMotor->moveTo(600);

  }
}

/*
 * Thread 2, turn the LED on and signal thread 1 to turn the LED off.
 */
// Declare the thread function for TaskIndicatorTest
void TaskIndicatorTest( void* pvParameters ) {

  for (int iter=0; iter<10; iter++) // A Task shall never return or exit.
  {
    Indicator::momentaryLedOn(ACTY_LED_1);
    Indicator::momentaryLedOn(ACTY_LED_2);
    Indicator::momentaryLedOn(ACTY_LED_3);
  
    Indicator::momentaryLedOn(MOVE_LED_GRN);
    Indicator::momentaryLedOn(MOVE_LED_RED);
    Indicator::momentaryLedOn(MOVE_LED_BLUE);

    Indicator::momentaryLedOn(CANNON_LED);
    Indicator::momentaryLedOn(CANNON_LED);
    Indicator::strobeLed(CANNON_LED, 10);
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void loop() {

}
