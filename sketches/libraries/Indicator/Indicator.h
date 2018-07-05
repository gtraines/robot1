
#ifndef ROBOT1_INDICATOR_H
#define ROBOT1_INDICATOR_H


class Indicator {
    public:
        static void momentaryLedOn(int pinNumber);
        static void strobeLed(int pinNumber, int numberTimes);
        static void turnOnLed(int pinNumber);
        static void turnOffLed(int pinNumber);
};
#endif // ROBOT1_INDICATOR_H
