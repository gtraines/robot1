
#include <Arduino.h>
#include <Indicator.h>
#include <PotMotor.h>

#define IR_TRIGGER 2
#define SERVO 3

#define ARD_STATUS_GRN 24
#define ARD_STATUS_RED 25

#define ACTY_LED_1 27
#define ACTY_LED_2 29
#define ACTY_LED_3 31

#define MOVE_LED_GRN 50
#define MOVE_LED_RED 51
#define MOVE_LED_BLUE 53

#define CANNON_LED 52

#define ELEVATION_MAX 740
#define ELEVATION_MIN 325
#define ELEVATION_DELTA 15

#define MOTOR_MIN_SPEED 50
#define MOTOR_MED_SPEED 100
#define MOTOR_MAX_SPEED 150
#define MOTOR_JERK_SPEED 255
#define ELEV_JERK_LENGTH 10
#define MOTOR_UPDATE_INTERVAL 60

#define MOTOR_POS 23
#define MOTOR_NEG 22
#define MOTOR_ENABLE 8
#define MOTOR_POSITION A0

PotMotor* _elevationMotor = NULL;


void setMotorIncreaseElevation() {
  Indicator::turnOnLed(MOVE_LED_GRN);
}

void setMotorDecreaseElevation() {
  Indicator::turnOnLed(MOVE_LED_BLUE);
  Indicator::turnOnLed(MOVE_LED_RED);
}

void elevationStop() {
    Indicator::turnOffLed(MOVE_LED_BLUE);
    Indicator::turnOffLed(MOVE_LED_RED);
    Indicator::turnOffLed(MOVE_LED_GRN);
}

void printInt(int intToPrint) {
  indicateTx();
  Serial.println(intToPrint);
}

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(MOTOR_POS, OUTPUT);
  pinMode(MOTOR_NEG, OUTPUT);
  
  pinMode(ARD_STATUS_GRN, OUTPUT);
  pinMode(ARD_STATUS_RED, OUTPUT);
  
  pinMode(ACTY_LED_1, OUTPUT);
  pinMode(ACTY_LED_2, OUTPUT);
  pinMode(ACTY_LED_3, OUTPUT);

  pinMode(MOVE_LED_GRN, OUTPUT);
  pinMode(MOVE_LED_RED, OUTPUT);
  pinMode(MOVE_LED_BLUE, OUTPUT);

  pinMode(CANNON_LED, OUTPUT);
  _elevationMotor = new PotMotor((int)MOTOR_ENABLE, 
    (int)MOTOR_POS, (int)MOTOR_NEG, (int)MOTOR_POSITION, 
    (int)ELEVATION_MIN, (int)ELEVATION_MAX, (int)ELEVATION_DELTA, 
    (int)MOTOR_MIN_SPEED, (int)MOTOR_MAX_SPEED, (int)MOTOR_MED_SPEED, (int)MOTOR_JERK_SPEED);
  
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
