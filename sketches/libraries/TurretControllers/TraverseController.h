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
	static void initialize(Servo* traverseServo);
    static bool canMoveTo(int targetPosition);
    static bool moveTo(int targetPosition, int delayMillis);
    static bool setConditionNeutral();
    static void functionCheckDemo();
    static int currentServoPosition;
    static int servoMaxPosition;
    static int servoStraightPosition;
    static int servoMinPosition;
    static Servo* traverseServo;
};


#endif //TURRET_TRAVERSECONTROLLER_H
