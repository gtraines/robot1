// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

#include <Arduino.h>
#include <Servo.h> 

#define SERVO_MIN_DEG 40
#define SERVO_MAX_DEG 140
#define SERVO_STRAIGHT_DEG 90

#define US_RCVR_PIN 0
#define STEERING_PIN 1
#define ESC_PIN 2
#define MOVE_DELAY 10

Servo usRcvrServo;
Servo steeringServo;
Servo escServo;

int servoTestPos = SERVO_STRAIGHT_DEG;
int usReceiverServoPos = SERVO_STRAIGHT_DEG;
int steeringServoPos = SERVO_STRAIGHT_DEG;

Servo servos[] = {
  usRcvrServo,
  steeringServo
};

void setupEsc()
{
  escServo.attach(ESC_PIN);
  delay(300);

  escServo.write(40);
  delay(1000);
  
  escServo.write(60);
  delay(1000);
  
  escServo.write(40);
  delay(1000);
}

void setupServo(Servo servoToSetup, int servoPin, int startPos) {
  servoToSetup.attach(servoPin);
  servoToSetup.write(startPos); 
}

void moveServo(Servo servoToMove, int posToMoveTo) {
  if (posToMoveTo < SERVO_MIN_DEG) {
    posToMoveTo = SERVO_MIN_DEG;
  }
  
  if (posToMoveTo > SERVO_MAX_DEG) {
    posToMoveTo = SERVO_MAX_DEG;
  }
  
  servoToMove.write(posToMoveTo);
}

void setup() { 
  setupServo(usRcvrServo, US_RCVR_PIN, SERVO_STRAIGHT_DEG);
  setupServo(steeringServo, STEERING_PIN, SERVO_STRAIGHT_DEG);
  setupEsc();
} 

void loop() {

  for(servoTestPos = 0; servoTestPos < SERVO_MAX_DEG; servoTestPos += 1) {
    for(int iServo = 0; iServo < 2; iServo++) {
      moveServo(servos[iServo], servoTestPos);
    }
    delay(MOVE_DELAY);
  }

  for(servoTestPos = SERVO_MAX_DEG; servoTestPos>=SERVO_MIN_DEG; servoTestPos-=1) {
    for(int iServo = 0; iServo < 2; iServo++) {
      moveServo(servos[iServo], servoTestPos);  
    }
    delay(MOVE_DELAY);    
  }
} 
