//www.elegoo.com
//2016.09.12

/*define logic control output pin*/
#define in1 9
#define in2 8
#define in3 7
#define in4 6
/*define channel enable output pins*/
#define ENA 10
#define ENB 5

/*define left function*/
void moveBackward()
{
  digitalWrite(ENB,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("Back");
}
/*define right function*/
void moveForward()
{
  digitalWrite(ENB,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Forward");
}

void turnLeft() {
  digitalWrite(ENA,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  Serial.println("Left");
}

void turnRight() 
{
  digitalWrite(ENA,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  Serial.println("Right");
}


void steerStraight() 
{
  digitalWrite(ENA,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  Serial.println("Straight");
}

void fullStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  Serial.println("Full stop");
}
/*put your setup code here, to run once*/
void setup() {
 Serial.begin(115200); //Open the serial port and set the baud rate to 9600
/*Set the defined pins to the output*/
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

/*put your main code here, to run repeatedly*/
void loop() {
  fullStop();
  delay(1000);
  turnLeft();
  delay(2000);
  steerStraight();
  delay(1000);
  turnRight();
  delay(2000);
  steerStraight();
  delay(500);
//  fullStop();
//  delay(500);
//  moveBackward();
//  delay(500);
//  turnLeft();
//  delay(500);
//  steerStraight();
//  delay(500);
//  turnRight();
//  delay(500);
}
