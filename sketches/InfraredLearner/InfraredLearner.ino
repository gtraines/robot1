#include "IRLibAll.h"
 
//Create a receiver object to listen on pin 2
#define IR_SIGNAL 2
#define IR_POWER 47

IRrecvPCI myReceiver(IR_SIGNAL);
 
//Create a decoder object 
IRdecode myDecoder;   
 
void setup() {
  Serial.begin(115200);
  //pinMode(IR_POWER, OUTPUT);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  //digitalWrite(IR_POWER, HIGH);
  Serial.println(F("Ready to receive IR signals"));
}
 
void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    myReceiver.enableIRIn();      //Restart receiver
  }
}
