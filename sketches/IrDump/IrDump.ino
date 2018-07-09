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

#define DEBUG true
#define HIT_PIN 26
#define DIR_1_REAR_PIN 28
#define DIR_2_RIGHT_PIN 30
#define DIR_3_LEFT_PIN 32
#define DIR_4_FRONT_PIN 34

#define RED_HIT 33EBDD7B 34EBDF0E D104AF4A
#define BLUE_HIT A3F34992
#define PURPLE_HIT1 33EBDD7A

boolean _sxrResultAvail = false;
boolean _hitSxrResultAvail = false;
boolean _dir1SxrResultAvail = false;
boolean _dir2SxrResultAvail = false;
boolean _dir3SxrResultAvail = false;
boolean _dir4SxrResultAvail = false;

IRrecv _hitSxr(HIT_PIN);
IRrecv _dir1Sxr(DIR_1_REAR_PIN);
IRrecv _dir2Sxr(DIR_2_RIGHT_PIN);
IRrecv _dir3Sxr(DIR_3_LEFT_PIN);
IRrecv _dir4Sxr(DIR_4_FRONT_PIN);

decode_results _hitResults;
decode_results _dir1Results;
decode_results _dir2Results;
decode_results _dir3Results;
decode_results _dir4Results;

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
    //pinMode(DIR_5_FLOATING_PIN, INPUT_PULLUP);
    //pinMode(DIR_6_FLOATING_PIN, INPUT_PULLUP);
    
    // Start the receivers
    _hitSxr.enableIRIn();
    _dir1Sxr.enableIRIn();
    _dir2Sxr.enableIRIn();
    _dir3Sxr.enableIRIn();
    _dir4Sxr.enableIRIn();
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
        _sxrResultAvail = true;
        _hitSxrResultAvail = true;
  }

  if (_dir1Sxr.decode(&_dir1Results)) {
        digitalWrite(31, LOW);
        _sxrResultAvail = true;
        _dir1SxrResultAvail = true;

  }
  if (_dir2Sxr.decode(&_dir2Results)) {
        digitalWrite(31, LOW);
        _sxrResultAvail = true;
        _dir2SxrResultAvail = true;
  }
  if (_dir3Sxr.decode(&_dir3Results)) {
        digitalWrite(31, LOW);
        _sxrResultAvail = true;
        _dir3SxrResultAvail = true;
  }
  if (_dir4Sxr.decode(&_dir4Results)) {
        digitalWrite(31, LOW);
        _sxrResultAvail = true;
        _dir4SxrResultAvail = true;
  }

    if (_sxrResultAvail == true) {
        
        if (_hitSxrResultAvail) {
            dump("Hit Sensor", &_hitResults);
            _hitSxrResultAvail = false;
            _hitSxr.resume();
        }
        if (_dir1SxrResultAvail) {
            dump("DIR REAR", &_dir1Results);
            _dir1SxrResultAvail = false;
            _dir1Sxr.resume();
        }
        if (_dir2SxrResultAvail) {
            dump("DIR LEFT", &_dir2Results);
            _dir2SxrResultAvail = false;
            _dir2Sxr.resume();
        }
        if (_dir3SxrResultAvail) {
            dump("DIR RIGHT", &_dir3Results);
            _dir3SxrResultAvail = false;
            _dir3Sxr.resume();
        }
        if (_dir4SxrResultAvail) {
            dump("DIR FRONT", &_dir4Results);
            _dir4SxrResultAvail = false;
            _dir4Sxr.resume();
        }
        _sxrResultAvail = false;
    }

    digitalWrite(31, HIGH);
    delay(1);
}