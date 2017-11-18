// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

#include <Arduino.h>
#include <Servo.h>
#include "RobotStatus.h"

#define SERIAL_PORT_SPEED 115200
#define SERVO_MIN_DEG 40
#define SERVO_MAX_DEG 140
#define SERVO_STRAIGHT_DEG 90

#define MOTOR_POWER_HALTED 95
#define MOTOR_POWER_FORWARD_STOP 95
#define MOTOR_POWER_REVERSE_STOP 94
#define MOTOR_POWER_SINGLE_STEP_CHANGE_MAX 3

#define MOTOR_POWER_FORWARD_MAX 100
#define MOTOR_POWER_FORWARD_SURGE 98
#define MOTOR_POWER_FORWARD_NORMAL 97
#define MOTOR_POWER_FORWARD_COAST 96
#define MOTOR_POWER_FORWARD_PREP 96

#define MOTOR_POWER_REVERSE_MAX 79
#define MOTOR_POWER_REVERSE_SURGE 79
#define MOTOR_POWER_REVERSE_NORMAL 90
#define MOTOR_POWER_REVERSE_COAST 92
#define MOTOR_POWER_REVERSE_PREP 94

#define US_RCVR_PIN 0
#define STEERING_PIN 1
#define ESC_PIN 2
#define MOVE_DELAY 10


Servo usRcvrServo;
Servo steeringServo;
Servo speedControl;

String inFromSerial;

int WarningState = 0;
int ErrorState = 0;
int InfoState = 0;

int currentMotorPower = MOTOR_POWER_HALTED;

int usReceiverServoPos = SERVO_STRAIGHT_DEG;
int steeringServoPos = SERVO_STRAIGHT_DEG;

Servo servos[] = {
  usRcvrServo,
  steeringServo
};

bool targetPowerTooHigh(int targetPower) {
  return (targetPower > MOTOR_POWER_FORWARD_MAX 
    || targetPower < MOTOR_POWER_REVERSE_MAX);
}

bool powerChangeTooExtreme(int targetPower) {
  return (currentMotorPower - targetPower > MOTOR_POWER_SINGLE_STEP_CHANGE_MAX 
    || targetPower - currentMotorPower > MOTOR_POWER_SINGLE_STEP_CHANGE_MAX);
}

bool currentlyInStoppedRange() {
  return currentMotorPower <= MOTOR_POWER_FORWARD_STOP && currentMotorPower >= MOTOR_POWER_REVERSE_STOP;
}

int getRegulatedTargetPower(int targetPower) {
  if (!targetPowerTooHigh(targetPower) && currentlyInStoppedRange()) {
    return targetPower;
  }
  if (targetPower > MOTOR_POWER_FORWARD_MAX && !powerChangeTooExtreme(targetPower)) {
    return MOTOR_POWER_FORWARD_MAX;
  }
  if (targetPower < MOTOR_POWER_REVERSE_MAX && !powerChangeTooExtreme(targetPower)) {
    return MOTOR_POWER_REVERSE_MAX;
  }
  if (targetPower > currentMotorPower && powerChangeTooExtreme(targetPower)) {
    return currentMotorPower + MOTOR_POWER_SINGLE_STEP_CHANGE_MAX;
  }
  if (targetPower < currentMotorPower && powerChangeTooExtreme(targetPower)) {
    return currentMotorPower - MOTOR_POWER_SINGLE_STEP_CHANGE_MAX;
  }
  // Fell through somehow
  return targetPower;
}

void setMotorPower(int targetPower) {
  //Serial.print("Current power:");
  //Serial.println(currentMotorPower);
  //Serial.print("Target power: ");
  //Serial.println(targetPower);
  delay(5);
  currentMotorPower = targetPower;
  delay(5);
  speedControl.write(currentMotorPower);
  delay(5);
  //Serial.print("Wrote motor power to: ");
  //Serial.println(currentMotorPower);
  delay(10);
}

void accelerateForward(int targetPower) {
  if (!currentlyInStoppedRange() && targetPower > currentMotorPower) {
    while (currentMotorPower < targetPower) {
      setMotorPower(currentMotorPower + 1);
    }
  }
  else if (currentlyInStoppedRange() && targetPower > currentMotorPower) {
    setMotorPower(MOTOR_POWER_FORWARD_SURGE);
  }
}

void decelerateForward(int targetPower) {
    while (currentMotorPower > targetPower) {
      setMotorPower(currentMotorPower - 1);
    }
  
}

void accelerateBackward(int targetPower) {
  setMotorPower(targetPower);
}

void decelerateBackward(int targetPower) {
  while (currentMotorPower < targetPower) {
    setMotorPower(currentMotorPower + 1);
  }
}

void moveForward(int targetPower) {
  //Serial.print("MoveForward::Target power:");
  //Serial.println(targetPower);
  if (currentlyInStoppedRange() && targetPower < MOTOR_POWER_FORWARD_SURGE) {
    //accelerate(MOTOR_POWER_FORWARD_PREP);
    accelerateForward(MOTOR_POWER_FORWARD_SURGE);
    decelerateForward(targetPower);
  }
  else {
    accelerateForward(targetPower);
  }
}

void haltMotion() {
  if (!currentlyInStoppedRange()) {
    
    if (currentMotorPower > MOTOR_POWER_HALTED) {
      decelerateForward(MOTOR_POWER_FORWARD_COAST);
      delay(300);
      decelerateForward(MOTOR_POWER_FORWARD_PREP);
      delay(300);
      decelerateForward(MOTOR_POWER_FORWARD_STOP);
    }

    if (currentMotorPower < MOTOR_POWER_HALTED) {
      decelerateBackward(MOTOR_POWER_REVERSE_COAST);
      delay(300);
      decelerateBackward(MOTOR_POWER_REVERSE_PREP);
      delay(300);
      decelerateForward(MOTOR_POWER_REVERSE_STOP);
    }
  }

  setMotorPower(MOTOR_POWER_HALTED);
}

void backUp(int targetPower) {
  //Serial.print("Backup::Target power:");
  //Serial.println(targetPower);
  if (currentlyInStoppedRange() && currentMotorPower > MOTOR_POWER_REVERSE_SURGE) {
    haltMotion();
    setMotorPower(MOTOR_POWER_REVERSE_PREP);
    accelerateBackward(MOTOR_POWER_REVERSE_SURGE);
    decelerateBackward(targetPower);
  }
  else {
    accelerateBackward(targetPower);
  }
}

void moveServo(Servo servoToMove, int posToMoveTo) {
  if (posToMoveTo < SERVO_MIN_DEG) {
    posToMoveTo = SERVO_MIN_DEG;
  }
  
  if (posToMoveTo > SERVO_MAX_DEG) {
    posToMoveTo = SERVO_MAX_DEG;
  }
  delay(1);
  servoToMove.write(posToMoveTo);
}

void setupEsc() {
  Serial.println("Attaching speed control");
  delay(10);
  speedControl.attach(ESC_PIN);
  delay(10);
}

void setup() {
  Serial.begin(SERIAL_PORT_SPEED);
  Serial.println("Setting up");
  usRcvrServo.attach(US_RCVR_PIN);
  delay(10);
  usRcvrServo.write(SERVO_STRAIGHT_DEG);
  delay(10);
  steeringServo.attach(STEERING_PIN);
  delay(10);
  steeringServo.write(SERVO_STRAIGHT_DEG);
  delay(10);
  setupEsc();
  Serial.println("Moving servoes");
  
} 

void loop() {
  moveServo(usRcvrServo, SERVO_STRAIGHT_DEG);
  delay(10);
  steeringServo.write(0);
  delay(10);
  
  setMotorPower(MOTOR_POWER_FORWARD_PREP);
  delay(500);
  setMotorPower(MOTOR_POWER_FORWARD_SURGE);
  delay(500);
  setMotorPower(MOTOR_POWER_FORWARD_NORMAL);
  delay(2000);
  setMotorPower(MOTOR_POWER_FORWARD_COAST);
  delay(2000);
  setMotorPower(MOTOR_POWER_FORWARD_STOP);
  delay(200);
  setMotorPower(0);
  delay(200);
  setMotorPower(MOTOR_POWER_REVERSE_PREP);
  delay(300);
  setMotorPower(MOTOR_POWER_REVERSE_SURGE);
  delay(300);
  setMotorPower(MOTOR_POWER_REVERSE_STOP);
  delay(300);
  setMotorPower(MOTOR_POWER_REVERSE_PREP);
  delay(300);
  setMotorPower(MOTOR_POWER_REVERSE_SURGE);
  delay(200);
  setMotorPower(MOTOR_POWER_REVERSE_COAST);
  delay(1000);
  setMotorPower(MOTOR_POWER_REVERSE_PREP);
  delay(1000);
  setMotorPower(MOTOR_POWER_REVERSE_STOP);
  delay(1500);
  setMotorPower(MOTOR_POWER_FORWARD_PREP);
  delay(200);
  setMotorPower(MOTOR_POWER_FORWARD_SURGE);
  delay(200);
} 
