/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Servo.h>
#include <avr/io.h>
#include <Indicator.h>

#define TRAVERSE_SERVO 3

#define ELEVATION_MOTOR_POS 23
#define ELEVATION_MOTOR_NEG 22
#define ELEVATION_MOTOR_ENABLE 8
#define ELEVATION_MOTOR_POSITION A0

#define IR_TRIGGER 2

#define IR_SXR_HIT 17
#define IR_SXR_REAR_PIN 18
#define IR_SXR_RIGHT_PIN 19
#define IR_SXR_LEFT_PIN 20
#define IR_SXR_FRONT_PIN 21

#define ARD_STATUS_GRN 24
#define ARD_STATUS_RED 25

#define ACTY_LED_1 27
#define ACTY_LED_2 31
#define ACTY_LED_3 29

#define MOVE_LED_GRN 50
#define MOVE_LED_RED 51
#define MOVE_LED_BLUE 53

#define CANNON_LED 52


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

void interruptHandler();
void funcWith8BitParameter(uint8_t param);
bool funcWithGlobalSideEffect();

int pos = 0;    // variable to store the servo position

volatile bool fastDelay = false;
uint8_t delayTime = 2000;

void setup() {

  Serial.begin(115200);

  myservo.attach(TRAVERSE_SERVO);
  pinMode(IR_SXR_FRONT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IR_SXR_FRONT_PIN), interruptHandler, RISING);
  myservo.write(170);
  pos = myservo.read();

  pinMode(ACTY_LED_1, OUTPUT);
  digitalWrite(ACTY_LED_1, HIGH);
  pinMode(ACTY_LED_2, OUTPUT);
  digitalWrite(ACTY_LED_2, HIGH);
  pinMode(ACTY_LED_3, OUTPUT);
  digitalWrite(ACTY_LED_3, HIGH);
}

void loop() {
  Indicator::turnOnLed(ACTY_LED_3);
  
  if (fastDelay) {
    delay(200);
  } else {
    delay(delayTime);
  }

  Indicator::turnOffLed(ACTY_LED_3);
  
  if (fastDelay) {
    delay(200);
  } else {
    delay(delayTime);
  }

  // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }
  // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }

}

void interruptHandler() {

  Indicator::turnOnLed(ACTY_LED_1);

  cli();

  funcWith8BitParameter(20);

  fastDelay = funcWithGlobalSideEffect();

  attachInterrupt(IR_SXR_FRONT_PIN, interruptHandler, RISING);
  Indicator::turnOffLed(ACTY_LED_1);
}

void funcWith8BitParameter(uint8_t param) {
  uint8_t blinkTimes = param;
  unsigned long startMicros = 0;
  unsigned long endMicros = 0;
  unsigned long incrMicros = 0;

  for (uint8_t idx = 0; idx < blinkTimes; idx++) {
    delayMicroseconds(50000);
    Indicator::turnOnLed(ACTY_LED_2);
    delayMicroseconds(50000);
    Indicator::turnOffLed(ACTY_LED_2);

  }
}

bool funcWithGlobalSideEffect() {
  return !fastDelay;
}

