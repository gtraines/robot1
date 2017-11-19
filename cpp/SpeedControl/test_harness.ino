#include <Arduino.h>
#include <Servo>
#include "SpeedControl.h"

#define UPDATE_STEP_SIZE 50
#define ESC_PIN_NUMBER 3

Servo esc;
SpeedControl tazer;

unsigned long loopStartMillis = 0;

void setup() {
    esc.attach(ESC_PIN_NUMBER);
    tazer.attach(esc, UPDATE_STEP_SIZE);
}

void loop() {
    loopStartMillis = millis();

    if (Serial.available() > 0) {
        int command = Serial.parseInt();

        if (tazer.getMillisUntilAvailableForCommand() <= 0) {
            tazer.commandMove(command);
        }
    }

    tazer.incrementStep();

    while (UPDATE_STEP_SIZE > (millis() - loopStartMillis))
    {
        delay(5);
    }

}