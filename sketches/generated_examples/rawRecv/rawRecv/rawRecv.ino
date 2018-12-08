/* rawR&cv.ino Example sketch for IRLib2
 *  Illustrate how to capture raw timing values for an unknow protocol.
 *  You will capture a signal using this sketch. It will output data the 
 *  serial monitor that you can cut and paste into the "rawSend.ino"
 *  sketch.
 */
// Recommend only use IRLibRecvPCI or IRLibRecvLoop for best results
#include "NewClass.h"
#include <IRLibRecvPCI.h>
#include <Arduino.h>
#include <WString.h>
 

#define IR_SXR_HIT 17
#define IR_SXR_REAR_PIN 18
#define IR_SXR_RIGHT_PIN 19
#define IR_SXR_LEFT_PIN 20
#define IR_SXR_FRONT_PIN 21

uint8_t type;

IRrecvPCI myReceiver(21);//pin number for the receiver

boolean returnsBool();



void setup() {
  Serial.begin(38400);
  
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  
  Serial.println(F("Ready to receive IR signals"));
  
  NewClass newClass = new NewClass();
  NewClass.properrtyDude = 2;
  uint8_t fakee = NewClass.ironPyriteMethod();
  
  newClass.faxMachineBroke = false;
  
}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) { 
    Serial.println(F("Do a cut-and-paste of the following lines into the "));
    Serial.println(F("designated location in rawSend.ino"));
    Serial.print(F("\n#define RAW_DATA_LEN "));
    Serial.println(recvGlobal.recvLength, DEC);
    Serial.print(F("uint16_t rawData[RAW_DATA_LEN]={\n\t"));
    char* charArr[5] = malloc(sizeof(char * 5));
    
    for (bufIndex_t i=1; i<recvGlobal.recvLength; i++) {
      Serial.print(recvGlobal.recvBuffer[i], DEC);
      Serial.print(F(", "));
      if( (i % 8)==0) Serial.print(F("\n\t"));
    }
    Serial.println(F("1000};"));//Add arbitrary trailing space
    myReceiver.enableIRIn();      //Restart receiver

    free charArr;
  }
}

boolean returnsBool() {
  if (ARDUINO > 1000) {
    return true;
  }
  return false;
}

int returnsSomething(bool shouldDoIt) {
  
  int localVar = 0;

  if (localVar < 2) {
    return localVar;
    
  }

  return shouldDoIt ? 1 : 0;
}

String caseStatement(int inbound) {
  switch (inbound) {
    case 1:
      return "One";
      break;
    case 0:
      return "Zero";
      break;
    default:
      return "Something";
  }
}


