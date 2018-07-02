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
#define TRAVERSE_INCREMENT_DELAY 15
String locationUpdate;

void setup() {
  Serial.begin(115200);
  traverseServo.attach(TRAVERSE_SERVO_PIN);
  traverseServo.write(TRAVERSE_START_POS);
  delay(1000);
  traversePosition = TRAVERSE_START_POS;
  Serial.println(F("Moved to initial position"));
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  digitalWrite(ENA,HIGH);  
}

void loop() {
  for (traversePosition = traversePosition; traversePosition < 180; traversePosition += 1) {
    traverseServo.write(traversePosition);
    delay(TRAVERSE_INCREMENT_DELAY);
    locationUpdate = String("Moved to: ") + String(traversePosition);
    Serial.println(locationUpdate);
    delay(1);
  }
  for (traversePosition = traversePosition; traversePosition > 0; traversePosition -= 1) {
    traverseServo.write(traversePosition);
    delay(TRAVERSE_INCREMENT_DELAY);
    locationUpdate = String("Moved to: ") + String(traversePosition);
    Serial.println(locationUpdate);
    delay(1);
  }
}

