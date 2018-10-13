//www.elegoo.com
//2016.09.12

/*In1 connected to the 9 pin, 
 In2 connected to the 8 pin, ENA pin 10,*/
int ENA=10; 
int IN1=9;
int IN2=8;
void setup()
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  digitalWrite(ENA,HIGH);       
}
void loop()
{  
  digitalWrite(IN1,LOW);      
  digitalWrite(IN2,HIGH);        //Right wheel forward
  delay(500);
  digitalWrite(IN1,LOW);      
  digitalWrite(IN2,LOW);         //Right wheel stop
  delay(500);
  digitalWrite(IN1,HIGH);      
  digitalWrite(IN2,LOW);         //Right wheel back
  delay(500);
  digitalWrite(IN1,LOW);      
  digitalWrite(IN2,LOW);         //Right wheel stop
  delay(500);
}

