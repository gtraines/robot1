//www.elegoo.com
//2016.12.08
#include <Servo.h>

Servo traverseServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int traversePosition = 0;
int ENA=8; 
int IN1=24;
int IN2=25;
#define TRAVERSE_SERVO_PIN 5 
#define TRAVERSE_START_POS 90
#define TRAVERSE_INCREMENT_DELAY 30

void setup() {
  traverseServo.attach(TRAVERSE_SERVO_PIN);
  traverseServo.write(TRAVERSE_START_POS);
  delay(1000);
  traversePosition = TRAVERSE_START_POS;
  Serial.write("Moved to initial position");
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  digitalWrite(ENA,HIGH);  
}

void loop() {
  for (traversePosition = traversePosition; traversePosition <= 180; traversePosition += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    traverseServo.write(traversePosition);              // tell servo to go to position in variable 'pos'
    delay(TRAVERSE_INCREMENT_DELAY);                       // waits 15ms for the servo to reach the position
    Serial.write("Moved to %d", traversePosition);
  }
  for (traversePosition = traversePosition; traversePosition >= 0; traversePosition -= 1) { // goes from 180 degrees to 0 degrees
    traverseServo.write(traversePosition);              // tell servo to go to position in variable 'pos'
    delay(TRAVERSE_INCREMENT_DELAY);                       // waits 15ms for the servo to reach the position
    Serial.write("Moved to %d", traversePosition);
  }
}

