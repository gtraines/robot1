#ifndef ROBOT1__TURRET_CONTROLLER__H
#define ROBOT1__TURRET_CONTROLLER__H

#include <HardwareSerial.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <Servo.h>
#include <Indicator.h>
#include <TurretPins.h>
#include <CannonController.h>
#include <ElevationController.h>
#include <TraverseController.h>

class TurretController
{
protected:
    static TickType_t dutyCycleMonitorDelay;
    static bool slewToWaitForCompletion(int traverseTgtIntRads, TraverseSpeed traverseSpeed,
                                     int elevationTgtIntRads, ElevationSpeed elevationSpeed);
    static int getJitterPositionIntRads(int originalPositionIntRads, int jitterIntRads);
  public:
    static void initialize(Servo* traverseServo);
    static void initialize(Servo* traverseServo, HardwareSerial* serial);
    ~TurretController() { }
    static void setStatusError();
    static bool setTraverseTargetIntRads(int tgtIntRads, TraverseSpeed speed);
    static bool setElevationTargetIntRads(int tgtIntRads, ElevationSpeed speed);
    static bool slewToTraverseAndElevation(int traverseTgtIntRads, TraverseSpeed traverseSpeed,
                                           int elevationTgtIntRads, ElevationSpeed elevationSpeed);
    static bool incrementTraverse(TraverseDirection direction, int intRads, TraverseSpeed speed);
    static bool incrementElevation(ElevationDirection direction, int intRads, ElevationSpeed speed);
    static bool fireCannon(CannonSignal signal, uint8_t burstLength);
    static bool fireCannonAreaTarget(int burstLength, CannonSignal signal);
    static bool setPins();
    static bool turnOffAllIndicators();
    static bool setControlMode(int mode);
    static void dutyCycleMonitor(void* pvParameters);
    static void functionCheckWorker(void* pvParameters);
    static TaskHandle_t functionCheckWorkerTaskHandle;
    static TaskHandle_t dutyCycleMonitorTaskHandle;
};

#endif // !ROBOT1_TURRET_CONTROLLER__H
