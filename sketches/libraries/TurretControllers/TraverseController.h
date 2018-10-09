//
// Created by graham on 10/7/18.
//

#ifndef TURRET_TRAVERSECONTROLLER_H
#define TURRET_TRAVERSECONTROLLER_H


#include <Servo.h>

struct traverse_state_t {
    bool isMoving;
    int delayMillis;
    int targetPosition;
    int currentPosition;
};

class TraverseController {
public:
    TraverseController();
    explicit TraverseController(Servo* traverseServo);
    ~TraverseController();
    bool canMoveTo(int targetPosition);
    bool moveTo(int targetPosition, int delayMillis);
    bool setConditionNeutral();
    void functionCheckDemo();
    int currentServoPosition;
    int servoMaxPosition;
    int servoStraightPosition;
    int servoMinPosition;
    Servo* traverseServo;

};


#endif //TURRET_TRAVERSECONTROLLER_H
