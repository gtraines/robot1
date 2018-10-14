//
// Created by graham on 10/7/18.
//

#ifndef TURRET_TRAVERSECONTROLLER_H
#define TURRET_TRAVERSECONTROLLER_H

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Servo.h>

struct traverse_state_t {
    bool isMoving;
    int delayMillis;
    int targetPosition;
    int currentPosition;
};

class TraverseController {
protected:
    static void clearIndicators();
public:
    static void initialize(Servo* traverseServo);
	~TraverseController() {
		delete _traverseServo;
	}
    static bool canMoveTo(int targetPosition);
    static bool moveTo(int targetPosition, int delayMillis);
    static bool setConditionNeutral();
    static void functionCheckDemo(void* pvParameters);
    static TaskHandle_t traverseTaskHandle;
    static Servo* _traverseServo;
    
};


#endif //TURRET_TRAVERSECONTROLLER_H
