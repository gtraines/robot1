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
private:
	Servo* _traverseServo;
public:
	TraverseController(Servo* traverseServo);
	~TraverseController() {
		delete _traverseServo;
	}
    bool canMoveTo(int targetPosition);
    bool moveTo(int targetPosition, int delayMillis);
    bool setConditionNeutral();
    void functionCheckDemo();
    int currentServoPosition;
    int servoMaxPosition;
    int servoStraightPosition;
    int servoMinPosition;
    static bool indicatorFunctionCheck();
};


#endif //TURRET_TRAVERSECONTROLLER_H
