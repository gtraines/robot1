/*
 * Arduino Uno
 */
// Interrupt Pins:
// Arduino	External                Arduino Pin Change      Arduino Pin Change
// Pin     Interrupt               Pin     Interrupt       Pin     Interrupt
//                 Port                           Port                     Port
// 2       INT0    PD2             2       PCINT18 PD2     A0      PCINT8  PC0
// 3       INT1    PD3             3       PCINT19 PD3     A1      PCINT9  PC1
//                                 4       PCINT20 PD4     A2      PCINT10 PC2
//                                 5       PCINT21 PD5     A3      PCINT11 PC3
//                                 6       PCINT22 PD6     A4      PCINT12 PC4
//                                 7       PCINT23 PD7     A5      PCINT13 PC5
//                                 8       PCINT0  PB0
//                                 9       PCINT1  PB1
//                                 10      PCINT2  PB2
//                                 11      PCINT3  PB3
//                                 12      PCINT4  PB4
//                                 13      PCINT5  PB5

/* 
 * ATmega2560
  */
// External Interrupts ------------------------------------------------------------
// The following External Interrupts are available on the Arduino:
// Arduino           
//   Pin  PORT INT  ATmega2560 pin
//   21     PD0  0     43
//   20     PD1  1     44
//   19     PD2  2     45
//   18     PD3  3     46
//    2     PE4  4      6
//    3     PE5  5      7
//  n/c     PE6  6      8  (fake pin 75) **
//  n/c     PE7  7      9  (fake pin 76)


// Pin Change Interrupts ----------------------------------------------------------
// ATMEGA2560 Pin Change Interrupts
// Arduino              Arduino              Arduino
//   Pin   PORT PCINT     Pin   PORT PCINT     Pin   PORT PCINT
//   A8     PK0  16       10     PB4   4       SS     PB0   0
//   A9     PK1  17       11     PB5   5       SCK    PB1   1
//  A10     PK2  18       12     PB6   6       MOSI   PB2   2
//  A11     PK3  19       13     PB7   7       MISO   PB3   3
//  A12     PK4  20       14     PJ1  10
//  A13     PK5  21       15     PJ0   9
//  A14     PK6  22        0     PE0   8 - this one is a little odd. *
//  A15     PK7  23

// * Note: Arduino Pin 0 is PE0 (PCINT8), which is RX0. Also, it is the only other
// pin on another port on PCI1. This would make it very costly to integrate with
// the library's code and thus is not supported by this library.  It is the same
// pin the Arduino uses to upload sketches, and it is connected to the FT232RL
// USB-to-Serial chip (ATmega16U2 on the R3).

// Fake Pins ---------------------------------------------------------- 
// The library supports all interrupt pins, even though not all pins to the ATmega-2560 processor 
// are exposed on the Arduino board. These pins are supported as "fake pins", and begin with pin 70 
// (there are 70 pins on the ATmega 2560 board). The fake pins are as follows:

// pin: fake 70 PJ2 this is Pin Change Interrupt PCINT11
// pin: fake 71 PJ3 this is Pin Change Interrupt PCINT12
// pin: fake 72 PJ4 this is Pin Change Interrupt PCINT13
// pin: fake 73 PJ5 this is Pin Change Interrupt PCINT14
// pin: fake 74 PJ6 this is Pin Change Interrupt PCINT15
// pin: fake 75 PE6 this is External Interrupt INT6
// pin: fake 76 PE7 this is External Interrupt INT7
// Why support these pins? 
// There are some non-Arduino boards that expose more pins, 
// and even on the Arduino these may be useful for software interrupts. 
// Software interrupts are used in my tests when I'm measuring the speed of the Arduino's interrupt system. 
// You may find another use for them.