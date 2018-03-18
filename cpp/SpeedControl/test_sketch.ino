
/* Test Speed Control  */
#include <Arduino.h>
#include <HardwareSerial.h>
#include <Servo.h>
#include "InternalOperation.h"
#include "SpeedControlCommand.h"
#include "SpeedControl.h"

#define TIMESTEP_LENGTH_MILLIS 50
#define ESC_PIN_NUMBER 3
#define DEBUG true

int inByte = 0;         // incoming serial byte

unsigned long loopStartMillis = 0;

Servo speedControlServo;
SpeedControl tazer;

void setup() {
    Serial.begin(115200);
    speedControlServo.attach(ESC_PIN_NUMBER);
    tazer.attach(speedControlServo, TIMESTEP_LENGTH_MILLIS);

    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    
    if (DEBUG) {
        establishContact();  // send a byte to establish contact until receiver responds
    }
    
}

void loop() {

    loopStartMillis = millis();

    if (Serial.available() > 0) {
        int command = Serial.parseInt();
        delay(1);
        Serial.print("Received ");
        Serial.println(command);
        int result = -1;
        
        if (tazer.availableToReceiveCommand()) {
            SpeedControlCommand commandInstance(command, loopStartMillis);          
            result = ((SpeedControl)tazer).commandMove(commandInstance);
        } 
        else {
            result = tazer.getMillisUntilAvailableForCommand();
        }
        Serial.print("Tazer controller returned ");
        Serial.println(result);
    }

    while (millis() - loopStartMillis < TIMESTEP_LENGTH_MILLIS) {
        //Serial.println("Waiting");
        delay(5);
    }

    tazer.incrementTimeStep();
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}