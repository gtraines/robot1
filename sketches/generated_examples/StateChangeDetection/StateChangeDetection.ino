/*
  State change detection (edge detection)

  Often, you don't need to know the state of a digital input all the time, but
  you just need to know when the input changes from one state to another.
  For example, you want to know when a button goes from OFF to ON. This is called
  state change detection, or edge detection.

  This example shows how to detect when a button or button changes from off to on
  and on to off.

  The circuit:
  - pushbutton attached to pin 2 from +5V
  - 10 kilohm resistor attached to pin 2 from ground
  - LED attached from pin 13 to ground (or use the built-in LED on most
    Arduino boards)

  created  27 Sep 2005
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ButtonStateChange
*/
#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <Servo.h>

Servo* usRcvrServo;
Servo* steeringServo;
Servo* speedControl;

// this constant won't change:
const int  buttonPin = 12;    // the pin that the pushbutton is attached to
const volatile int ledPin = 13;       // the pin that the LED is attached to

#define CH_1_PIN A0
// ESC
#define CH_2_PIN 2
// Steering
#define CH_3_PIN 3
#define CH_4_PIN A3 

#define STEERING_PIN 9

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
uint8_t interruptCtr = 0;
uint16_t lastReadValue = 0;

volatile int16_t ch2SignalValue = 0;
volatile bool ch2NewSignal = false;
volatile uint16_t ch3SignalValue = 0;
volatile bool ch3NewSignal = false;
uint8_t steeringServoValue = 90;
uint16_t steeringIntermediate = 1500;

void printSignal(uint8_t channel, uint16_t signal);
void handleCh1Signal();
void handleCh2Signal();
void handleCh3Signal();
void handleCh4Signal();

uint16_t baseHandler(uint8_t channel, uint8_t pinNumber);

void setup() {
  cli();

    // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
    //pinMode(CH_1_PIN, INPUT);
  //pinMode(CH_2_PIN, INPUT);
  pinMode(CH_3_PIN, INPUT);
  //pinMode(CH_4_PIN, INPUT);
  pinMode(STEERING_PIN, OUTPUT);
  digitalWrite(STEERING_PIN, LOW);

  //steeringServo = new Servo();
  //steeringServo->attach(STEERING_PIN);
  //steeringServo->write(steeringServoValue);

  Serial.begin(115200);

  // attachInterrupt(digitalPinToInterrupt(analogInputToDigitalPin(CH_1_PIN)), handleCh1Signal, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(CH_2_PIN), handleCh2Signal, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CH_3_PIN), handleCh3Signal, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(analogInputToDigitalPin(CH_4_PIN)), handleCh4Signal, CHANGE);
  sei();
}

void loop() {
  if (ch2NewSignal) {
    ch2NewSignal = false;
    printSignal(CH_2_PIN, ch2SignalValue);
    ch2SignalValue = 0;
  }

  if (ch3NewSignal) {
    ch3NewSignal = false;
    noInterrupts();
    // if (ch3SignalValue == 1500) {
    //   steeringServoValue = 90;
    // } else if (ch3SignalValue > 1500) {
    //   steeringIntermediate = ch3SignalValue - 1500;
    //   steeringServoValue = 90 + (2 * (steeringIntermediate / 10));
    // } else if (ch3SignalValue < 1500) {
    //   steeringIntermediate = ch3SignalValue - 900;
    //   steeringServoValue = 2 * (steeringIntermediate / 10);
    // }
    //steeringServo->write(steeringServoValue);
    
    printSignal(CH_3_PIN, ch3SignalValue);
    interrupts();
  }
  //steeringServo->writeMicroseconds(ch3SignalValue);
  delay(1);

}

void printSignal(uint8_t channel, uint16_t signal) {
  if (signal != 1500) {
    Serial.print(channel);
    Serial.print(":");
    Serial.println(signal);
  }
}

uint16_t baseHandler(uint8_t channel, uint8_t pinNumber) {
  //noInterrupts();
  
  volatile unsigned long ms_start = micros();
  digitalWrite(STEERING_PIN, HIGH);
  volatile uint8_t pinData = digitalRead(pinNumber);
  while (pinData == HIGH && (micros() - ms_start) < 20000) {
    delayMicroseconds(1);
    pinData = digitalRead(pinNumber);
  }
  
  volatile unsigned long ms_end = micros();
  digitalWrite(STEERING_PIN, LOW);
  volatile unsigned long ms_total = ms_end - ms_start;
  if (ms_total < 550 || ms_total > 20000) {
    ms_total = 0;
  }
  if (ms_total > 1450 && ms_total < 1550) {
    ms_total = 1500;
  }

  //interrupts();
  return ms_total;
}

void handleCh1Signal() {
  uint16_t signal = baseHandler(1, CH_1_PIN);
}
void handleCh2Signal() {
  uint16_t signal = baseHandler(2, CH_2_PIN);
  if (signal != 0) {
    ch2NewSignal = true;
    ch2SignalValue = signal;
  }
}
void handleCh3Signal() {
  uint16_t signal = baseHandler(3, CH_3_PIN);
  if (signal != 0) {
    ch3NewSignal = true;
    if (signal <= 980 && ch3SignalValue - signal > 800 && ch3NewSignal > 0) {
      signal += 1000;
    }

    ch3SignalValue = signal;
  }
}
void handleCh4Signal() {
  uint16_t signal = baseHandler(4, CH_4_PIN);
}