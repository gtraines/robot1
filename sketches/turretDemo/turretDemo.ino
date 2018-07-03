
#include <Arduino.h>

#define MOTOR_POS 23
#define MOTOR_NEG 22
#define MOTOR_ENABLE 8
#define MOTOR_POSITION A0
#define ELEVATION_MAX 715
#define ELEVATION_MIN 280

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

#define ELEVATION_DELTA 25
#define CANNON_LED 52

int _elevation = 0;

void elevateTo(int targetElevation) {
    elevationStop();
    
    int elev = getCurrentElevation();
    
    if (canMoveToElevation(targetElevation) && abs(targetElevation - elev) > ELEVATION_DELTA) {
      if (targetElevation > elev) {
        increaseElevation(targetElevation);
      } else {
        decreaseElevation(targetElevation);
      }
    } else {
      setArdStatusError();
    }
}

void increaseElevation(int targetElevation) {
  analogWrite(MOTOR_ENABLE, 90);
  turnOnLed(MOVE_LED_GRN);
  digitalWrite(MOTOR_POS, HIGH);
  digitalWrite(MOTOR_NEG, LOW);
  int elev = getCurrentElevation();
  
  while (targetElevation > elev && abs(targetElevation - elev) > ELEVATION_DELTA) {
    delay(5);
    elev = getCurrentElevation();
  }
  
  elevationStop();
  turnOffLed(MOVE_LED_GRN);
  elev = getCurrentElevation();
  
  if (elev > targetElevation && abs(targetElevation - elev) > ELEVATION_DELTA) {
    elevateTo(targetElevation);
  }
}

void decreaseElevation(int targetElevation) {
  analogWrite(MOTOR_ENABLE, 90);
  
  turnOnLed(MOVE_LED_BLUE);
  turnOnLed(MOVE_LED_RED);
  digitalWrite(MOTOR_POS, LOW);
  digitalWrite(MOTOR_NEG, HIGH);
  int elev = getCurrentElevation();
  
  while (targetElevation < elev && abs(targetElevation - elev) > ELEVATION_DELTA) {
    delay(5);
    elev = getCurrentElevation();
  }
  
  elevationStop();
  turnOffLed(MOVE_LED_BLUE);
  turnOffLed(MOVE_LED_RED);
  elev = getCurrentElevation();
  
  if (elev < targetElevation && abs(targetElevation - elev) > ELEVATION_DELTA) {
    elevateTo(targetElevation);
  }
}

void elevationStop() {
    
    digitalWrite(MOTOR_POS, LOW);
    digitalWrite(MOTOR_NEG, LOW);
}

boolean canMoveToElevation(int targetElevation) {
  return targetElevation >= ELEVATION_MIN && targetElevation <= ELEVATION_MAX;
}

int getCurrentElevation() {
  int currentElevation = analogRead(MOTOR_POSITION);
  
  if (currentElevation != _elevation) {
    _elevation = currentElevation;
  }
  
  return _elevation;
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

  elevateTo(ELEVATION_MIN);
  elevateTo(ELEVATION_MAX);
  elevateTo(500);
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
  momentaryLedOn(ACTY_LED_3);
}

void indicateTx() {
  momentaryLedOn(ACTY_LED_1);
}

void turnOnLed(int pinNumber) {
  digitalWrite(pinNumber, LOW);
}

void turnOffLed(int pinNumber) {
  digitalWrite(pinNumber, HIGH);
}

void loop() {
  
  

}
