/* rawR&cv.ino Example sketch for IRLib2
 *  Illustrate how to capture raw timing values for an unknow protocol.
 *  You will capture a signal using this sketch. It will output data the 
 *  serial monitor that you can cut and paste into the "rawSend.ino"
 *  sketch.
 */
// Recommend only use IRLibRecvPCI or IRLibRecvLoop for best results
#include <Arduino.h>
#include <IRLibRecvPCI.h> 
#define IR_SENSOR_HIT 2

IRrecvPCI myReceiver(IR_SENSOR_HIT);//pin number for the receiver

// BLUE!!!
// #define RAW_DATA_LEN 18
// uint16_t rawData[RAW_DATA_LEN]={
// 	5998, 574, 526, 470, 1550, 470, 486, 562, 
// 	1498, 470, 442, 582, 526, 470, 526, 498, 
// 	1526, 1000};
// #define RAW_DATA_LEN 18
// uint16_t rawData[RAW_DATA_LEN]={
// 	6062, 510, 494, 530, 1522, 470, 406, 618, 
// 	1522, 474, 450, 570, 526, 470, 466, 558, 
// 	1522, 1000};

// RED RED RED !!!
// #define RAW_DATA_LEN 18
// uint16_t rawData[RAW_DATA_LEN]={
// 	6038, 502, 522, 478, 1498, 514, 522, 482, 
// 	1538, 474, 518, 506, 430, 566, 1486, 530, 
// 	486, 1000};
// Do a cut-and-paste of the following lines into the 
// designated location in rawSend.ino

// #define RAW_DATA_LEN 18
// uint16_t rawData[RAW_DATA_LEN]={
// 	6098, 466, 534, 490, 1526, 466, 450, 574, 
// 	1522, 494, 514, 486, 526, 470, 1546, 470, 
// 	530, 1000};

// // PURPLE PURPLE PURPLE!
// #define RAW_DATA_LEN 18
// uint16_t rawData[RAW_DATA_LEN]={
// 	5982, 562, 518, 486, 1530, 482, 518, 490, 
// 	1530, 482, 482, 538, 486, 538, 1426, 566, 
// 	1510, 1000};
// Do a cut-and-paste of the following lines into the 
// designated location in rawSend.ino

// #define RAW_DATA_LEN 18
// uint16_t rawData[RAW_DATA_LEN]={
// 	5974, 566, 514, 490, 1502, 514, 510, 510, 
// 	1506, 490, 478, 538, 490, 510, 1450, 566, 
// 	1482, 1000};


void setup() {
  Serial.begin(115200);
  delay(2000); while (!Serial); //delay for Leonardo
  //pinMode(IR_SENSOR_HIT, INPUT_PULLUP);
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

