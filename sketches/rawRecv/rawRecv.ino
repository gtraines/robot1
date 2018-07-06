/* rawR&cv.ino Example sketch for IRLib2
 *  Illustrate how to capture raw timing values for an unknow protocol.
 *  You will capture a signal using this sketch. It will output data the 
 *  serial monitor that you can cut and paste into the "rawSend.ino"
 *  sketch.
 */
// Recommend only use IRLibRecvPCI or IRLibRecvLoop for best results
#include <Arduino.h>
#include <IRLibRecvPCI.h> 
#define IR_SENSOR_HIT 26

IRrecvPCI myReceiver(IR_SENSOR_HIT);//pin number for the receiver

void setup() {
  Serial.begin(115200);
  delay(2000); while (!Serial); //delay for Leonardo
  pinMode(IR_SENSOR_HIT, INPUT_PULLUP);
  pinMode(31, OUTPUT);
  digitalWrite(31, HIGH);
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {

  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    digitalWrite(31, LOW);
    Serial.println(F("Do a cut-and-paste of the following lines into the "));
    Serial.println(F("designated location in rawSend.ino"));
    Serial.print(F("\n#define RAW_DATA_LEN "));
    Serial.println(recvGlobal.recvLength, DEC);
    Serial.print(F("uint16_t rawData[RAW_DATA_LEN]={\n\t"));

    for(bufIndex_t i = 1; i < recvGlobal.recvLength; i++) {
      Serial.print(recvGlobal.recvBuffer[i], DEC);
      Serial.print(F(", "));
      if( (i % 8)==0) Serial.print(F("\n\t"));
    }

    Serial.println(F("1000};"));//Add arbitrary trailing space
    myReceiver.enableIRIn();      //Restart receiver
  }
  digitalWrite(31, HIGH);
}

