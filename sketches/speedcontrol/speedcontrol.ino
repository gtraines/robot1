// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

#include <Arduino.h>
#include <Servo.h> 

#define SERIAL_PORT_SPEED 115200
#define SERVO_MIN_DEG 40
#define SERVO_MAX_DEG 140
#define SERVO_STRAIGHT_DEG 90

#define US_RCVR_PIN 0
#define STEERING_PIN 1
#define ESC_PIN 2
#define MOVE_DELAY 10

Servo usRcvrServo;
Servo escServo;
String inFromSerial;

int servoTestPos = SERVO_STRAIGHT_DEG;
int usReceiverServoPos = SERVO_STRAIGHT_DEG;
int steeringServoPos = SERVO_STRAIGHT_DEG;

Servo servos[] = {
  usRcvrServo
};

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0,0");   // send an initial string
    delay(300);
  }
}

void setupEsc()
{
  escServo.attach(ESC_PIN);
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
  Serial.begin(SERIAL_PORT_SPEED);
  setupServo(usRcvrServo, US_RCVR_PIN, SERVO_STRAIGHT_DEG);
  setupEsc();
  
  for(servoTestPos = 0; servoTestPos < SERVO_MAX_DEG; servoTestPos += 1) {
    for(int iServo = 0; iServo < 2; iServo++) {
      moveServo(servos[iServo], servoTestPos);
    }
    delay(MOVE_DELAY);
  }
  

} 

void loop() {
  while (Serial.available() > 0) {
    int escValue = Serial.parseInt();
    escServo.write(escValue);
    Serial.println(escValue);
  }
  delay(5);
} 
