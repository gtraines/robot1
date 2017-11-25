
/* Test Speed Control  */
#include <Arduino.h>
#include <Servo.h>
#include "InternalOperation.h"
#include "SpeedControlCommand.h"
#include "SpeedControl.h"

#define UPDATE_STEP_SIZE 50
#define ESC_PIN_NUMBER 3

int firstSensor = 0;    // first analog sensor
int secondSensor = 0;   // second analog sensor
int thirdSensor = 0;    // digital sensor
int inByte = 0;         // incoming serial byte

unsigned long loopStartMillis = 0;

Servo speedControlServo;
SpeedControl tazer;

void setup() {
    Serial.begin(115200);
    speedControlServo.attach(ESC_PIN_NUMBER);
    tazer.attach(speedControlServo, UPDATE_STEP_SIZE);

    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    
    establishContact();  // send a byte to establish contact until receiver responds
}

void loop() {
  // if we get a valid byte, read analog ins:
//   if (Serial.available() > 0) {
//     // get incoming byte:
//     inByte = Serial.read();
//     // read first analog input, divide by 4 to make the range 0-255:
//     firstSensor = analogRead(A0) / 4;
//     // delay 10ms to let the ADC recover:
//     delay(10);
//     // read second analog input, divide by 4 to make the range 0-255:
//     secondSensor = analogRead(1) / 4;
//     // read switch, map it to 0 or 255L
//     thirdSensor = map(digitalRead(2), 0, 1, 0, 255);
//     // send sensor values:
//     Serial.write(firstSensor);
//     Serial.write(secondSensor);
//     Serial.write(thirdSensor);
//   }

    loopStartMillis = millis();

    if (Serial.available() > 0) {
        int command = Serial.parseInt();

        if (tazer.availableToReceiveCommand()) {
            SpeedControlCommand commandInstance(-3, loopStartMillis);
            
            int result = ((SpeedControl)tazer).commandMove(commandInstance);
        }
    }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}