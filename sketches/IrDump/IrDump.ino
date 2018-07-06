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
#define DIR_1_PIN 28
#define DIR_2_PIN 30
#define DIR_3_FRONT_PIN 32
#define DIR_4_PIN 34

IRrecv _hitSxr(HIT_PIN);
IRrecv _dir1Sxr(DIR_1_PIN);
IRrecv _dir2Sxr(DIR_2_PIN);
IRrecv _dir3Sxr(DIR_3_FRONT_PIN);
IRrecv _dir4Sxr(DIR_4_PIN);

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
    pinMode(DIR_1_PIN, INPUT_PULLUP);
    pinMode(DIR_2_PIN, INPUT_PULLUP);
    pinMode(DIR_3_FRONT_PIN, INPUT_PULLUP);
    pinMode(DIR_4_PIN, INPUT_PULLUP);

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
    Serial.println(sensorName);
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  } 
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");
  } 
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  } 
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  } 
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {	
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->panasonicAddress,HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {
     Serial.print("Decoded LG: ");
  }
  else if (results->decode_type == JVC) {
     Serial.print("Decoded JVC: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 0; i < count; i++) {
    if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    } 
    else {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println("");
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
        dump("Dir 1 Sensor", &_dir1Results);
        _dir1Sxr.resume(); // Receive the next value
  }
  if (_dir2Sxr.decode(&_dir2Results)) {
        digitalWrite(31, LOW);
        Serial.println(_dir2Results.value, HEX);
        dump("Dir 2 Sensor", &_dir2Results);
        _dir2Sxr.resume(); // Receive the next value
  }
  if (_dir3Sxr.decode(&_dir3Results)) {
        digitalWrite(31, LOW);
        Serial.println(_dir3Results.value, HEX);
        dump("Dir 3 FRONT Sensor", &_dir3Results);
        _dir3Sxr.resume(); // Receive the next value
  }
  if (_dir4Sxr.decode(&_dir4Results)) {
        digitalWrite(31, LOW);
        Serial.println(_dir4Results.value, HEX);
        dump("Dir 4 Sensor", &_dir4Results);
        _dir4Sxr.resume(); // Receive the next value
  }
  digitalWrite(31, HIGH);
}