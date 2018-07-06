/*
 * IRremote: IRrecvDump - dump details of IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 * JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
 * LG added by Darryl Smith (based on the JVC protocol)
 */
#include <Arduino.h>
#include <IRremote.h>

#define HIT_PIN 26
#define DIR_1_REAR_PIN 28
#define DIR_2_RIGHT_PIN 30
#define DIR_3_LEFT_PIN 32
#define DIR_4_FRONT_PIN 34
#define DIR_5_FLOATING_PIN 36

#define RED_HIT 33EBDD7B
#define BLUE_HIT A3F34992
#define PURPLE_HIT1 33EBDD7A

IRrecv _hitSxr(HIT_PIN);
IRrecv _dir1Sxr(DIR_1_REAR_PIN);
IRrecv _dir2Sxr(DIR_2_RIGHT_PIN);
IRrecv _dir3Sxr(DIR_3_LEFT_PIN);
IRrecv _dir4Sxr(DIR_4_FRONT_PIN);
IRrecv _dir5Sxr(DIR_5_FLOATING_PIN);

decode_results _hitResults;
decode_results _dir1Results;
decode_results _dir2Results;
decode_results _dir3Results;
decode_results _dir4Results;
decode_results _dir5Results;

void setup()
{
    pinMode(31, OUTPUT);
    digitalWrite(31, HIGH);

    Serial.begin(115200);
    pinMode(HIT_PIN, INPUT_PULLUP);
    pinMode(DIR_1_REAR_PIN, INPUT_PULLUP);
    pinMode(DIR_2_RIGHT_PIN, INPUT_PULLUP);
    pinMode(DIR_3_LEFT_PIN, INPUT_PULLUP);
    pinMode(DIR_4_FRONT_PIN, INPUT_PULLUP);
    pinMode(DIR_5_FLOATING_PIN, INPUT_PULLUP);

    // Start the receivers
    _hitSxr.enableIRIn();
    _dir1Sxr.enableIRIn();
    _dir2Sxr.enableIRIn();
    _dir3Sxr.enableIRIn();
    _dir4Sxr.enableIRIn();
    _dir5Sxr.enableIRIn();
}

// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
//void dump(void *v) {
//  decode_results *results = (decode_results *)v
void dump(String sensorName, decode_results *results) {
    Serial.print("Sensor name: ");
    Serial.print(sensorName);
    Serial.print(" Value: ");
    Serial.print(results->value, HEX);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(")");
}


void loop() {
  if (_hitSxr.decode(&_hitResults)) {
        digitalWrite(31, LOW);
        Serial.println(_hitResults.value, HEX);
        dump("Hit Sensor", &_hitResults);
        _hitSxr.resume(); // Receive the next value
  }
  if (_dir1Sxr.decode(&_dir1Results)) {
        digitalWrite(31, LOW);
        Serial.println(_dir1Results.value, HEX);
        dump("DIR_1_REAR_PIN", &_dir1Results);
        _dir1Sxr.resume(); // Receive the next value
  }
  if (_dir2Sxr.decode(&_dir2Results)) {
        digitalWrite(31, LOW);
        Serial.println(_dir2Results.value, HEX);
        dump("DIR_2_RIGHT_PIN", &_dir2Results);
        _dir2Sxr.resume(); // Receive the next value
  }
  if (_dir3Sxr.decode(&_dir3Results)) {
        digitalWrite(31, LOW);
        Serial.println(_dir3Results.value, HEX);
        dump("DIR_3_LEFT_PIN", &_dir3Results);
        _dir3Sxr.resume(); // Receive the next value
  }
  if (_dir4Sxr.decode(&_dir4Results)) {
        digitalWrite(31, LOW);
        Serial.println(_dir4Results.value, HEX);
        dump("DIR_4_FRONT_PIN", &_dir4Results);
        _dir4Sxr.resume(); // Receive the next value
  }
  if (_dir5Sxr.decode(&_dir5Results)) {
        digitalWrite(31, LOW);
        Serial.println(_dir5Results.value, HEX);
        dump("DIR_5_FLOATING_PIN", &_dir5Results);
        _dir5Sxr.resume(); // Receive the next value
  }
  
  digitalWrite(31, HIGH);
  delay(5);
}