
#ifndef ROBOT1_INDICATOR_H
#define ROBOT1_INDICATOR_H

class Indicator {
public:
    static void turnOnLed(int pinNumber);
    static void turnOffLed(int pinNumber);
    static void momentaryLedOn(int pinNumber);
    static void momentaryLedOn(int pinNumber, int delay);
    static void strobeLed(int pinNumber, int delay, int numberTimes);

    static void alertBlink(int pinNumber);
    static void alertBlinkFast(int pinNumber);
    static void alertBlinkSlow(int pinNumber);
    
    static void alertStrobe(int pinNumber);
    static void alertStrobeFast(int pinNumber);
    static void alertStrobeSlow(int pinNumber);
    
    static void strobeSlow(int pinNumber, int numberTimes);
    static void strobeMedium(int pinNumber, int numberTimes);
    static void strobeFast(int pinNumber, int numberTimes);
};
#endif // ROBOT1_INDICATOR_H
