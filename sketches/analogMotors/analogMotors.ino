
#include <Arduino.h>

#define MOTOR_POS 22
#define MOTOR_NEG 23
#define MOTOR_ENABLE 8
#define MOTOR_POSITION A0

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

int _elevation = 0;

void elevate(int where) {
  
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
  
  if (systemsCheck()) {
    setArdStatusGood();
  } else {
    setArdStatusError();
  }

}

boolean systemsCheck() {
  turnOffLed(ARD_STATUS_GRN);
  turnOffLed(ARD_STATUS_RED);
  
  turnOffLed(ACTY_LED_1);
  turnOffLed(ACTY_LED_2);
  turnOffLed(ACTY_LED_3);
  
  turnOffLed(MOVE_LED_GRN);
  turnOffLed(MOVE_LED_RED);
  turnOffLed(MOVE_LED_BLUE);
  
  turnOffLed(CANNON_LED);
  
  momentaryLedOn(ACTY_LED_1);
  momentaryLedOn(ACTY_LED_2);
  momentaryLedOn(ACTY_LED_3);
  
  momentaryLedOn(MOVE_LED_GRN);
  momentaryLedOn(MOVE_LED_RED);
  momentaryLedOn(MOVE_LED_BLUE);
  
  momentaryLedOn(CANNON_LED);
  return true;
  
}

void momentaryLedOn(int pinNumber) {
  turnOnLed(pinNumber);
  delay(500);
  turnOffLed(pinNumber);
}


void setArdStatusGood() {
  turnOffLed(ARD_STATUS_RED);
  turnOnLed(ARD_STATUS_GRN);
}

void setArdStatusError() {
  turnOffLed(ARD_STATUS_GRN);
  turnOnLed(ARD_STATUS_RED);
}

void indicateRx() {
  
  
}

void turnOnLed(int pinNumber) {
  digitalWrite(pinNumber, LOW);
}

void turnOffLed(int pinNumber) {
  digitalWrite(pinNumber, HIGH);
}

void loop() {
  int currentElevation = analogRead(MOTOR_POSITION);
  if (currentElevation != _elevation) {
    momentaryLedOn(ACTY_LED_1);
    Serial.println(_elevation);
    _elevation = currentElevation;
  }
  delay(100);
}
