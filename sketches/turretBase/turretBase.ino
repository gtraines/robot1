
#include <Arduino.h>
#include <Indicator.h>
#include <PotMotor.h>

#include <TurretPins.h>
#include <ElevationConfig.h>
#include <IndicatorConfig.h>
#include <IrConfig.h>
#include <TraverseConfig.h>

#include <HardwareSerial.h>
#include <FreeRTOS_AVR.h>
#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

PotMotor* _elevationMotor = NULL;


void printInt(int intToPrint) {
  indicateTx();
  Serial.println(intToPrint);
}

void setup() {
  Serial.begin(115200);
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

  _elevationMotor = new PotMotor((int)ELEVATION_MOTOR_ENABLE, 
    (int)ELEVATION_MOTOR_POS, (int)ELEVATION_MOTOR_NEG, (int)ELEVATION_MOTOR_POSITION, 
    (int)ELEVATION_MIN, (int)ELEVATION_MAX, (int)ELEVATION_RESOLUTION, 
    (int)MOTOR_MIN_SPEED, (int)MOTOR_MAX_SPEED, (int)MOTOR_MED_SPEED, (int)MOTOR_JERK_SPEED);
  _elevationMotor->setReadingDelay(MOTOR_UPDATE_INTERVAL);

  if (systemsCheck()) {
    setArdStatusGood();
  } else {
    setArdStatusError();
  }

}

boolean systemsCheck() {

  Indicator::turnOffLed(ARD_STATUS_GRN);
  Indicator::turnOffLed(ARD_STATUS_RED);
  
  Indicator::turnOffLed(ACTY_LED_1);
  Indicator::turnOffLed(ACTY_LED_2);
  Indicator::turnOffLed(ACTY_LED_3);
  
  Indicator::turnOffLed(MOVE_LED_GRN);
  Indicator::turnOffLed(MOVE_LED_RED);
  Indicator::turnOffLed(MOVE_LED_BLUE);
  
  Indicator::turnOffLed(CANNON_LED);
  
  Indicator::momentaryLedOn(ACTY_LED_1);
  Indicator::momentaryLedOn(ACTY_LED_2);
  Indicator::momentaryLedOn(ACTY_LED_3);
  
  Indicator::momentaryLedOn(MOVE_LED_GRN);
  Indicator::momentaryLedOn(MOVE_LED_RED);
  Indicator::momentaryLedOn(MOVE_LED_BLUE);
  
  Indicator::momentaryLedOn(CANNON_LED);
  Indicator::momentaryLedOn(CANNON_LED);
  Indicator::strobeLed(CANNON_LED, 10);

  _elevationMotor->moveTo(ELEVATION_MIN);
  _elevationMotor->moveTo(ELEVATION_MAX);
  _elevationMotor->moveTo(500);
  _elevationMotor->moveTo(600);
  delay(500);
  Indicator::strobeLed(CANNON_LED, 10);
  _elevationMotor->moveTo(320);
  _elevationMotor->moveTo(700);
  _elevationMotor->moveTo(500);
  _elevationMotor->moveTo(320);
  _elevationMotor->moveTo(600);
  delay(500);
  Indicator::strobeLed(CANNON_LED, 10);
  _elevationMotor->moveTo(350);
  _elevationMotor->moveTo(600);
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

void loop() {
  
  

}
