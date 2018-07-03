
#include <Arduino.h>

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

int _lastElevation = 0;

bool elevationProgress(int currentElevation) {
  if (abs(currentElevation - _lastElevation) < ELEVATION_DELTA) {
    return false;
  }

  return true;
}

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

int getElevationTargetDeltaInSlices(int targetElevation) {
  int deltaAnalog = abs(targetElevation - getCurrentElevation());

  return deltaAnalog/ELEVATION_DELTA;
}

int getMotorSpeed(int targetElevation, int lastElevation) {
  int deltaSlices = getElevationTargetDeltaInSlices(targetElevation);
  if (deltaSlices > 25 || (abs(getCurrentElevation() - lastElevation) < ELEVATION_DELTA )) {
    return MOTOR_JERK_SPEED;
  } else if (deltaSlices > 15) {
    return MOTOR_MAX_SPEED;
  } else if (deltaSlices > 5) {
    return MOTOR_MED_SPEED;
  } else {
    return MOTOR_MIN_SPEED;
  }
  
}

void increaseElevation(int targetElevation) {
  analogWrite(MOTOR_ENABLE, MOTOR_JERK_SPEED);
  int currentMotorSpeed = MOTOR_JERK_SPEED;
  turnOnLed(MOVE_LED_GRN);
  digitalWrite(MOTOR_POS, HIGH);
  digitalWrite(MOTOR_NEG, LOW);
  int elev = getCurrentElevation();
  
  int motorSpeedUpdated = currentMotorSpeed;
  while (targetElevation > elev && getElevationTargetDeltaInSlices(targetElevation) > 1) {
    delay(MOTOR_UPDATE_INTERVAL);
    
    motorSpeedUpdated = getMotorSpeed(targetElevation, elev);
    if (motorSpeedUpdated != currentMotorSpeed) {
      analogWrite(MOTOR_ENABLE, motorSpeedUpdated);
      currentMotorSpeed = motorSpeedUpdated;
    }
    
    elev = getCurrentElevation();    
  }
  
  elevationStop();
  turnOffLed(MOVE_LED_GRN);
  elev = getCurrentElevation();
  
  if (elev > targetElevation && getElevationTargetDeltaInSlices(targetElevation) > 1) {
    elevateTo(targetElevation);
  }
}

void decreaseElevation(int targetElevation) {
  analogWrite(MOTOR_ENABLE, MOTOR_JERK_SPEED);
  int currentMotorSpeed = MOTOR_JERK_SPEED;

  turnOnLed(MOVE_LED_BLUE);
  turnOnLed(MOVE_LED_RED);
  digitalWrite(MOTOR_POS, LOW);
  digitalWrite(MOTOR_NEG, HIGH);
  int elev = getCurrentElevation();
  
  int motorSpeedUpdated = currentMotorSpeed;
  while (targetElevation < elev && getElevationTargetDeltaInSlices(targetElevation) > 1) {
    delay(MOTOR_UPDATE_INTERVAL);
    
    motorSpeedUpdated = getMotorSpeed(targetElevation, elev);
    if (motorSpeedUpdated != currentMotorSpeed) {
      analogWrite(MOTOR_ENABLE, motorSpeedUpdated);
      currentMotorSpeed = motorSpeedUpdated;
    };
    elev = getCurrentElevation();
  }
  
  elevationStop();
  turnOffLed(MOVE_LED_BLUE);
  turnOffLed(MOVE_LED_RED);
  elev = getCurrentElevation();
  
  if (elev < targetElevation && getElevationTargetDeltaInSlices(targetElevation) > 1) {
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
  return analogRead(MOTOR_POSITION);
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
  momentaryLedOn(CANNON_LED);
  strobeLed(CANNON_LED, 10);

  elevateTo(ELEVATION_MIN);
  elevateTo(ELEVATION_MAX);
  elevateTo(500);
  elevateTo(600);
  delay(500);
  strobeLed(CANNON_LED, 10);
  elevateTo(320);
  elevateTo(700);
  elevateTo(500);
  elevateTo(320);
  elevateTo(600);
  delay(500);
  strobeLed(CANNON_LED, 10);
  elevateTo(350);
  elevateTo(600);
  return true;
  
}

void momentaryLedOn(int pinNumber) {
  turnOnLed(pinNumber);
  delay(500);
  turnOffLed(pinNumber);
}

void strobeLed(int pinNumber, int numberTimes) {
  int iter = 0;
  for (iter = 0; iter < numberTimes; iter++) {
    turnOnLed(pinNumber);
    delay(50);
    turnOffLed(pinNumber);
    delay(50);
  }
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
