//www.elegoo.com
//2016.12.08
#include <Arduino.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
#define TRAVERSE_SERVO 3
int maxPosition = 170;
int minPosition = 10;
int lastPosition = 0;
void setup() {
  lastPosition = 90;
  myservo.attach(TRAVERSE_SERVO);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  
  for (pos = lastPosition; pos < maxPosition; pos++) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  lastPosition = pos;
  for (pos = lastPosition; pos >= minPosition; pos--) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  lastPosition = pos;
}

