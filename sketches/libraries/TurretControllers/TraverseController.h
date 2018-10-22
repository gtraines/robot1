//
// Created by graham on 10/7/18.
//

#ifndef TURRET_TRAVERSECONTROLLER_H
#define TURRET_TRAVERSECONTROLLER_H

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Servo.h>

class TraverseController {
protected:
    static void clearIndicators();
    static int getNextMoveToIntRads(int currentTargetIntRads, int stepSize);
    static bool functionCheckSpeedDemo();
    static void updateTurretState(int currentIntRads);
    static TickType_t getTakeDelay();
    static int getCurrentDelayMillis();
    static int getStepSize();
public:
    static void initialize(Servo* traverseServo);
	~TraverseController() {
		delete _traverseServo;
	}
    static bool canMoveTo(int targetPosition);
    static bool moveTo(int targetPosition, int delayMillis);
    static bool moveToIntRads(int intRads, int delayMillis);
    static bool moveToIntRads(int intRads);
    static bool setConditionNeutral();
    static void functionCheckDemo(void* pvParameters);
    static void dutyCycle(void* pvParameters);
    static int getCurrentIntRads();
    static int getTargetIntRads();
    static TaskHandle_t traverseTaskHandle;
    static Servo* _traverseServo;
    static int currentPositionIntRads;
    
};


#endif //TURRET_TRAVERSECONTROLLER_H
