//
// Created by graham on 11/24/17.
//

#ifndef SPEEDCONTROLTEST_SERVO_H
#define SPEEDCONTROLTEST_SERVO_H

class Servo {
public:
    Servo() {
        _lastWrote = 0;
    };
    ~Servo() = default;
    void write(int angle) {
        _lastWrote = angle;
    };
    int getLastWrote() {
        return _lastWrote;
    };
private:
    int _lastWrote;

};

#endif //SPEEDCONTROLTEST_SERVO_H
