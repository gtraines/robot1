//#include <AccelStepper.h>
#include <Arduino.h>
#include <XBOXONE.h>
#include <Servo.h>
#include <InputValues.h>

/* ****** 
 * PIN DEFINES
 */
#define SERVO_PIN 11

// Pan Motor
#define PAN_DIRECTION 22
#define PAN_PULSE 23

// Tilt Motor
#define TILT_DIRECTION 24 
#define TILT_PULSE 25

#define MOTOR_4_DIRECTION 42
#define MOTOR_4_PULSE 43

#define MOTOR_3_DIRECTION 26
#define MOTOR_3_PULSE 27

#define MOTOR_2_DIRECTION 28
#define MOTOR_2_PULSE 29

#define MOTOR_1_DIRECTION 32
#define MOTOR_1_PULSE 33


USB Usb;
XBOXONE Xbox(&Usb);
Servo myservo;  // create servo object to control a servo

int valR;    // focus motor intergers
int valL;
//AccelStepper stepper1(1, 2, 3);


// motor 1
int motorOneCwise; //tracking left and right
int motorOneCCwise;
//int motorOneDirectionPin = 44;
//int motorOnePulsePin = 45;

#define DIRECTION_FORWARD HIGH
#define DIRECTION_BACK LOW

#define DIRECTION_LEFT LOW
#define DIRECTION_RIGHT HIGH

void updateFocusMotor(Buttons* buttonInputs);
void setDirection(int direction, int motorPin) {
    digitalWrite(motorPin, direction);
}
// motor 2
int motorTwoForward; //= 0; track forward/down
int motorTwoBackward; //= 0; track backward/up
//int motorTwoDirectionPin = 46;
//int motorTwoPulesPin = 47;


// motor 3
int motorThreeForward; // track forward/up
int motorThreeBackward; // track backward/down when tracking up motor three goes forward and motor 2 backwards
//int motorThreeDirectionPin = 48;
//int mototThreePulsePin = 49;


// motor 4
int motorFourCwise;
int motorFourCCwise;
//int motorFourDirectionPin = 42;
//int motorFourPulsePin = 43;

//motor 5
int tiltUp; //= 0;
int tiltDown; //= 0;
//int motorFiveDirectionPin = 24;
//int motorFivePulsePin = 25;

// motor 6
int panRight; //= 0;
int panLeft; //= 0;
//int motorSixDirectionPin = 22;
//int motorSixPulsePin = 23;

int x = 0; //this can be altered to make the acceleration incriment slower
float decreaseL = 1;
float decreaseR = 1; //
float decreaseUp = 1; // motor 3 moving on its own
float decreaseDown = 1; // motor 3 moving on its own
float decreaseL1 = 1; // motor 2 moving on its own
float decreaseR1 = 1; // motor 2 moving on its own
float decreaseCCW = 1; // motor 4
float decreaseCW = 1; // motor 4
float initialSpeed = 1200; //this can be altered to start at a lower speed
float finalSpeed = 600; //this can be altered to make it go at a higher final speed


void initializeStepper(int directionPin, int pulsePin) {
    pinMode(directionPin, OUTPUT); //pan direction pin
    pinMode(pulsePin, OUTPUT); //step pin 
}

//#define MAX_SPEED 100
//#define INPUT_READ_INTERVAL 100
//unsigned long last_input_time = 0;

//int sensorValue = 0;
//int sensorPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //stepper1.setMaxSpeed(3000);
  //stepper1.setAcceleration(1000);

  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXBOX USB Library Started"));
  //  focus motor
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 11 to the servo object

    initializeStepper(PAN_DIRECTION, PAN_PULSE);
    initializeStepper(TILT_DIRECTION, TILT_PULSE);
    initializeStepper(MOTOR_6_DIRECTION, MOTOR_6_PULSE);
    initializeStepper(MOTOR_5_DIRECTION, MOTOR_5_PULSE);
    initializeStepper(MOTOR_4_DIRECTION, MOTOR_4_PULSE);
    initializeStepper(MOTOR_3_DIRECTION, MOTOR_3_PULSE);
    initializeStepper(MOTOR_2_DIRECTION, MOTOR_2_PULSE);
    initializeStepper(MOTOR_1_DIRECTION, MOTOR_1_PULSE);

  // motor 6 pan control
  digitalWrite (22, LOW); 
  digitalWrite (23, HIGH);

  // motor 5
  digitalWrite (24, HIGH);
  digitalWrite (25, HIGH);

  // motor 4
  digitalWrite (42, LOW);
  digitalWrite (43, HIGH);

  // motor 3
  digitalWrite (26, LOW);
  digitalWrite (27, HIGH);

  // motor 2
  digitalWrite (28, HIGH);
  digitalWrite (29, HIGH);

  // motor 1
  digitalWrite (32, LOW);
  digitalWrite (33, HIGH);
}

void updatePanMotor(HatInputs* rightHat) {
  int panDelay;

  if (rightHat->X > 5000) {
    setDirection(PAN_DIRECTION, DIRECTION_RIGHT);
    panDelay = map(panRight, 5000, 32767, 3600, 1);
  }

  if (rightHat->X < -5000) {
    setDirection(PAN_DIRECTION, DIRECTION_LEFT);
    panDelay = map(panLeft, -5000, -32768, 3600, 1);
  }
  
    digitalWrite(23, HIGH);
    delayMicroseconds(panDelay);
    digitalWrite(23, LOW);
}

void loop() {

  Usb.Task();
  // put your main code here, to run repeatedly:
    Buttons buttonInputs = new Buttons();
    buttonInputs->L2 = Xbox.getButtonPress(L2);
    buttonInputs->R2 = Xbox.getButtonPress(R2);
    
    
    HatInputs rightHat = HatInputs { 
        X = Xbox.getAnalogHat(RightHatX), 
        Y = Xbox.getAnalogHat(RightHatY)
    };
    
    HatInputs leftHat = HatInputs {
        X = Xbox.getAnalogHat(LeftHatX),
        Y = Xbox.getAnalogHat(LeftHatY)
    };
    
    DirectionalPad dPad = new DirectionalPad {
        Up = Xbox.getButtonPress(UP),
        Down = Xbox.getButtonPress(DOWN),
        Left = Xbox.getButtonPress(LEFT),
        Right = Xbox.getButtonPress(RIGHT)
    }
    
    updateFocusMotor(buttonInputs);
    updatePanMotor(&rightHat);




  ///////////////Tilt motor 5 (lead screw) xbox right stick y axis like in halo.

  tiltUp = (Xbox.getAnalogHat(RightHatY));
  tiltUp = map(tiltUp, 7500, 32767, 3600, 1);

  tiltDown = (Xbox.getAnalogHat(RightHatY));
  tiltDown = map(tiltDown, -7500, -32768, 3600, 1);

  if (Xbox.getAnalogHat(RightHatY) > 7500) {
    digitalWrite (24, LOW); // direction
    //delay (5);
    digitalWrite (25, HIGH); // pulse
    delayMicroseconds (tiltUp);
    digitalWrite (25, LOW);  // pulse
    delayMicroseconds (tiltUp);
  }

  if (Xbox.getAnalogHat(RightHatY) < -7500) {
    digitalWrite (24, HIGH); // direction
    //delay (5);
    digitalWrite (25, HIGH); // pulse
    delayMicroseconds (tiltDown);
    digitalWrite (25, LOW); // pulse
    delayMicroseconds (tiltDown);
  }

  // tracking forward motors 2 and 3 tracking up same motors

  motorTwoForward = (Xbox.getAnalogHat(LeftHatY));
  motorTwoForward = map(motorTwoForward, 5000, 32767, 3600, 1);

  motorTwoBackward = (Xbox.getAnalogHat(LeftHatY));
  motorTwoBackward = map(motorTwoBackward, -5000, -32768, 3600, 1);

  //motorThreeForward = (Xbox.getAnalogHat(LeftHatY));
  //motorThreeForward = map(motorThreeForward, 5000, 32767, 3600, 1);

  //motorThreeBackward = (Xbox.getAnalogHat(LeftHatY));
  // motorThreeBackward = map(motorThreeBackward, -5000, -32768, 3600, 1);

  if (Xbox.getAnalogHat(LeftHatY) > 5000) {  //Forward direction motor 3
    digitalWrite (26, HIGH); // direction
    //delay (5);
    digitalWrite (27, HIGH); // pulse
    delayMicroseconds (motorTwoForward);
    digitalWrite (27, LOW);  // pulse
    delayMicroseconds (motorTwoForward);


    digitalWrite (28, LOW); // direction motor 2 !!!!!!!!!!!!!!!!!!!! maybe change this when I put the arm together !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    digitalWrite (29, HIGH); // pulse
    delayMicroseconds (motorTwoForward);
    digitalWrite (29, LOW);  // pulse
    delayMicroseconds (motorTwoForward);

  }
  if (Xbox.getAnalogHat(LeftHatY) < -5000) {  //reverse direction motor 3
    digitalWrite (26, LOW); // direction
    //delay (5);
    digitalWrite (27, HIGH); // pulse
    delayMicroseconds (motorTwoBackward);
    digitalWrite (27, LOW);  // pulse
    delayMicroseconds (motorTwoBackward);

    digitalWrite (28, HIGH); // direction motor 2 !!!!!!!!!!!!!!!!!!!! maybe change this when I put the arm together !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    digitalWrite (29, HIGH); // pulse
    delayMicroseconds (motorTwoBackward);
    digitalWrite (29, LOW);  // pulse
    delayMicroseconds (motorTwoBackward);
  }

  //tracking up acceleration sketch
  if (Xbox.getButtonPress(L1) == 1) {

    if (decreaseL < initialSpeed - finalSpeed) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (26, HIGH); // direction forward motor 3
        setDirectionMotor3()
        digitalWrite (28, HIGH); // direction motor 2
        digitalWrite (27, HIGH);
        delayMicroseconds (initialSpeed - decreaseL);
        digitalWrite (27, LOW);
        delayMicroseconds (initialSpeed - decreaseL);
        digitalWrite (29, HIGH);
        delayMicroseconds (initialSpeed - decreaseL);
        digitalWrite (29, LOW);
        delayMicroseconds (initialSpeed - decreaseL);
        x++;


      }
      decreaseL = (decreaseL *1.1);

    }
    digitalWrite (26, HIGH); // direction forward motor 3
    digitalWrite (28, HIGH); // direction motor 2
    digitalWrite (27, HIGH); // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (27, LOW);  // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (29, HIGH); // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (29, LOW);  // pulse
    delayMicroseconds (finalSpeed);



  }
  if (Xbox.getButtonPress(L1) != HIGH) {

    if (decreaseL > 1) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (26, HIGH); // direction forward motor 3
        digitalWrite (28, HIGH); // direction motor 2
        digitalWrite (27, HIGH);
        delayMicroseconds (initialSpeed - decreaseL);
        digitalWrite (27, LOW);
        delayMicroseconds (initialSpeed - decreaseL);
        digitalWrite (29, HIGH);
        delayMicroseconds (initialSpeed - decreaseL);
        digitalWrite (29, LOW);
        delayMicroseconds (initialSpeed - decreaseL);
        x++;


      }
      decreaseL = (decreaseL /1.1);

    }
  }

  //Serial.println(decreaseL);


  //tracking down acceleration sketch

  if (Xbox.getButtonPress(R1) == 1) {

    if (decreaseR < initialSpeed - finalSpeed) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (26, LOW); // direction forward motor 3
        digitalWrite (28, LOW); // direction motor 2
        digitalWrite (27, HIGH);
        delayMicroseconds (initialSpeed - decreaseR);
        digitalWrite (27, LOW);
        delayMicroseconds (initialSpeed - decreaseR);
        digitalWrite (29, HIGH);
        delayMicroseconds (initialSpeed - decreaseR);
        digitalWrite (29, LOW);
        delayMicroseconds (initialSpeed - decreaseR);
        x++;


      }
      decreaseR = (decreaseR *1.1);

    }
    digitalWrite (26, LOW); // direction forward motor 3
    digitalWrite (28, LOW); // direction motor 2
    digitalWrite (27, HIGH); // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (27, LOW);  // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (29, HIGH); // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (29, LOW);  // pulse
    delayMicroseconds (finalSpeed);



  }
  if (Xbox.getButtonPress(R1) != HIGH) {

    if (decreaseR > 1) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (26, LOW); // direction forward motor 3
        digitalWrite (28, LOW); // direction motor 2
        digitalWrite (27, HIGH);
        delayMicroseconds (initialSpeed - decreaseR);
        digitalWrite (27, LOW);
        delayMicroseconds (initialSpeed - decreaseR);
        digitalWrite (29, HIGH);
        delayMicroseconds (initialSpeed - decreaseR);
        digitalWrite (29, LOW);
        delayMicroseconds (initialSpeed - decreaseR);
        x++;


      }
      decreaseR = (decreaseR/1.1);

    }

  }
  //Serial.print ("\t");
  //Serial.println(decreaseR);

  // track left and right motor one

  motorOneCwise = (Xbox.getAnalogHat(LeftHatX));
  motorOneCwise = map(motorOneCwise, 5000, 32767, 3600, 1);

  motorOneCCwise = (Xbox.getAnalogHat(LeftHatX));
  motorOneCCwise = map(motorOneCCwise, -5000, -32768, 3600, 1);



  if (Xbox.getAnalogHat(LeftHatX) > 5000) {
    digitalWrite (32, LOW); // direction
    //delay (5);
    digitalWrite (33, HIGH); // pulse
    delayMicroseconds (motorOneCwise);
    digitalWrite (33, LOW);  // pulse
    delayMicroseconds (motorOneCwise);

  }

  if (Xbox.getAnalogHat(LeftHatX) < -5000) {
    digitalWrite (32, HIGH); // direction
    //delay (5);
    digitalWrite (33, HIGH); // pulse
    delayMicroseconds (motorOneCCwise);
    digitalWrite (33, LOW);  // pulse
    delayMicroseconds (motorOneCCwise);

  }


  //____________________________________________________________________________________________________________________________________


  // button presses for moving 2 and 3 independantly. This is motor 3 up
  if (Xbox.getButtonPress(UP) == 1) {

    if (decreaseUp < initialSpeed - finalSpeed) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (26, HIGH); // direction forward motor 3
        digitalWrite (27, HIGH);
        delayMicroseconds (initialSpeed - decreaseUp);
        digitalWrite (27, LOW);
        delayMicroseconds (initialSpeed - decreaseUp);

        x++;


      }
      decreaseUp = (decreaseUp * 1.1);

    }
    digitalWrite (26, HIGH); // direction forward motor 3
    digitalWrite (27, HIGH); // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (27, LOW);  // pulse
    delayMicroseconds (finalSpeed);




  }
  if (Xbox.getButtonPress(UP) != HIGH) {

    if (decreaseUp > 1) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (26, HIGH); // direction forward motor 3
        digitalWrite (27, HIGH);
        delayMicroseconds (initialSpeed - decreaseUp);
        digitalWrite (27, LOW);
        delayMicroseconds (initialSpeed - decreaseUp);

        x++;


      }
      decreaseUp = (decreaseUp/1.1);

    }
  }

  // button presses for moving 2 and 3 independantly. This is motor 3 down
  if (Xbox.getButtonPress(DOWN) == 1) {

    if (decreaseDown < initialSpeed - finalSpeed) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (26, LOW); // direction backward motor 3
        digitalWrite (27, HIGH);
        delayMicroseconds (initialSpeed - decreaseDown);
        digitalWrite (27, LOW);
        delayMicroseconds (initialSpeed - decreaseDown);

        x++;


      }
      decreaseDown = (decreaseDown * 1.1);

    }
    digitalWrite (26, LOW); // direction backward motor 3
    digitalWrite (27, HIGH); // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (27, LOW);  // pulse
    delayMicroseconds (finalSpeed);




  }
  if (Xbox.getButtonPress(DOWN) != HIGH) {

    if (decreaseDown > 1) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (26, LOW); // direction backward motor 3
        digitalWrite (27, HIGH);
        delayMicroseconds (initialSpeed - decreaseDown);
        digitalWrite (27, LOW);
        delayMicroseconds (initialSpeed - decreaseDown);

        x++;


      }
      decreaseDown = (decreaseDown/1.1);


    }
  }
  //______________________________________________button press to move motor 2 indenpadantly


  // button presses for moving 2 and 3 independantly. This is motor 2 up
  if (Xbox.getButtonPress(RIGHT) == 1) {

    if (decreaseR1 < initialSpeed - finalSpeed) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (28, LOW); // direction forward motor 2
        digitalWrite (29, HIGH);
        delayMicroseconds (initialSpeed - decreaseR1);
        digitalWrite (29, LOW);
        delayMicroseconds (initialSpeed - decreaseR1);

        x++;


      }
      decreaseR1 = (decreaseR1 * 1.1);

    }
    digitalWrite (28, LOW); // direction forward motor 2
    digitalWrite (29, HIGH); // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (29, LOW);  // pulse
    delayMicroseconds (finalSpeed);




  }
  if (Xbox.getButtonPress(RIGHT) != HIGH) {

    if (decreaseR1 > 1) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (28, LOW); // direction forward motor 2
        digitalWrite (29, HIGH);
        delayMicroseconds (initialSpeed - decreaseR1);
        digitalWrite (29, LOW);
        delayMicroseconds (initialSpeed - decreaseR1);

        x++;


      }
      decreaseR1 = (decreaseR1 /1.1);

    }
  }

  // button presses for moving 2 and 3 independantly. This is motor 2 down


  if (Xbox.getButtonPress(LEFT) == 1) {

    if (decreaseL1 < initialSpeed - finalSpeed) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (28, HIGH); // direction backward motor 2
        digitalWrite (29, HIGH);
        delayMicroseconds (initialSpeed - decreaseL1);
        digitalWrite (29, LOW);
        delayMicroseconds (initialSpeed - decreaseL1);

        x++;


      }
       decreaseL1 = (decreaseL1 * 1.1);

    }
    digitalWrite (28, HIGH); // direction backward motor 2
    digitalWrite (29, HIGH); // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (29, LOW);  // pulse
    delayMicroseconds (finalSpeed);




  }
  if (Xbox.getButtonPress(LEFT) != HIGH) {

    if (decreaseL1 > 1) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (28, HIGH); // direction backward motor 2
        digitalWrite (29, HIGH);
        delayMicroseconds (initialSpeed - decreaseL1);
        digitalWrite (29, LOW);
        delayMicroseconds (initialSpeed - decreaseL1);

        x++;


      }
      decreaseL1 = (decreaseL1 / 1.1);


    }
  }

  //_______________________________________________ motor 4 Rotation  ___________________________________________________

  // motor 4 Clock Wise

  if (Xbox.getButtonPress(X) == 1) {

    if (decreaseCW < initialSpeed - finalSpeed) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (42, HIGH); // direction CW motor 4
        digitalWrite (43, HIGH);
        delayMicroseconds (initialSpeed - decreaseCW);
        digitalWrite (43, LOW);
        delayMicroseconds (initialSpeed - decreaseCW);

        x++;


      }
      decreaseCW = (decreaseCW *1.1);

    }
    digitalWrite (42, HIGH); // direction CW motor 4
    digitalWrite (43, HIGH); // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (43, LOW);  // pulse
    delayMicroseconds (finalSpeed);




  }
  if (Xbox.getButtonPress(X) != HIGH) {

    if (decreaseCW > 1) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (42, HIGH); // direction CW motor 4
        digitalWrite (43, HIGH);
        delayMicroseconds (initialSpeed - decreaseCW);
        digitalWrite (43, LOW);
        delayMicroseconds (initialSpeed - decreaseCW);

        x++;


      }
      decreaseCW = (decreaseCW /1.1);

    }
  }

  // Motor 4 Counter clock wise
  if (Xbox.getButtonPress(B) == 1) {

    if (decreaseCCW < initialSpeed - finalSpeed) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (42, LOW); // direction CCW motor 4
        digitalWrite (43, HIGH);
        delayMicroseconds (initialSpeed - decreaseCCW);
        digitalWrite (43, LOW);
        delayMicroseconds (initialSpeed - decreaseCCW);

        x++;


      }
      decreaseCCW = (decreaseCCW *1.1);

    }
    digitalWrite (42, LOW); // direction CCW motor 4
    digitalWrite (43, HIGH); // pulse
    delayMicroseconds (finalSpeed);
    digitalWrite (43, LOW);  // pulse
    delayMicroseconds (finalSpeed);




  }
  if (Xbox.getButtonPress(B) != HIGH) {

    if (decreaseCCW > 1) {
      x = 0;
      while (x < 5 ) {
        digitalWrite (42, LOW); // direction CCW motor 4
        digitalWrite (43, HIGH);
        delayMicroseconds (initialSpeed - decreaseCCW);
        digitalWrite (43, LOW);
        delayMicroseconds (initialSpeed - decreaseCCW);

        x++;


      }
      decreaseCCW = (decreaseCCW /1.1);

    }

  }

}

void updateFocusMotor(Buttons* buttonInputs) {
    int servoWriteTime;
    //___________________________focus motor______________________
  if (buttonInputs->R2 > 0) {
    servoWriteTime = map(buttonInputs->R2, 0, 1023, 1500, 1700);
  }

  if (buttonInputs->L2 > 0) {
    servoWriteTime = map(buttonInputs->L2, 0, 1023, 1500, 1000);
  }
  
  myservo.writeMicroseconds(servoWriteTime);
}


void printMotorStatus() {

  //readout for motor one
  /*
    Serial.print(", Track clockwise: ");
    Serial.print(motorOneCwise);
    Serial.print("\t");
    Serial.print(", Track counterclockwise: ");
    Serial.print(motorOneCCwise);
    Serial.print("\t");

    //read out for motor two and three
    Serial.print(", Track Forward: ");
    Serial.print(motorTwoForward);
    Serial.print("\t");
    Serial.print(", Track Backward: ");
    Serial.println(motorTwoBackward);

    // tilt up and down
    Serial.print("\t");
    Serial.print(", Tilt Up: ");
    Serial.print(tiltUp);
    Serial.print("\t");
    Serial.print(", Tilt Down: ");
    Serial.print(tiltDown);
    Serial.print("\t");
    // pan left and right
    Serial.print (", Pan Right: ");
    Serial.print(panRight);
    Serial.print("\t");
    Serial.print (", Pan Left: ");
    Serial.println(panLeft);
  */


}
