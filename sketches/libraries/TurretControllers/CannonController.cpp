#include "CannonController.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender
#include <CannonConfig.h>

#include <IndicatorConfig.h>
#include <Taskr.h>
#include <IrConfig.h>
#include <Indicator.h>
#include <CannonCommand.h>
#include <CannonState.h>
#include <TurretPins.h>
#include <TurretState.h>


IRsendRaw* CannonController::cannon = new IRsendRaw();
TaskHandle_t CannonController::cannonTaskHandle = NULL;

uint16_t CannonController::blueSignal[18]={
        5998, 574, 526, 470, 1550, 470, 486, 562,
        1498, 470, 442, 582, 526, 470, 526, 498,
        1526, 1000};

uint16_t CannonController::redSignal[18]={
6038, 502, 522, 478, 1498, 514, 522, 482,
1538, 474, 518, 506, 430, 566, 1486, 530,
486, 1000};

uint16_t CannonController::purpleSignal[18]={
5982, 562, 518, 486, 1530, 482, 518, 490,
1530, 482, 482, 538, 486, 538, 1426, 566,
1510, 1000};

void CannonController::functionCheckDemo(void* pvParameters) {

    for (int idx = 0; idx < 6; idx++) {
        Indicator::alertStrobeFast(CANNON_LED);
        vTaskDelay(600/portTICK_PERIOD_MS);
    }
}

bool CannonController::initialize() {
    Indicator::turnOffLed(CANNON_LED);
    TurretState::cannonCommand = new CannonCommand_t();
    TurretState::cannonCommand->burstLength = 0;

    TurretState::cannonState = new CannonState_t();
    TurretState::cannonState->burstLength = 0;
    TurretState::cannonState->isFiring = false;

    BaseType_t cannonStatus = xTaskCreate(
            CannonController::dutyCycle,
            (const portCHAR *) "CannonControllerTask",
            128,  // Stack size
            NULL,
            3,  // Priority
            &CannonController::cannonTaskHandle);

    return true;
}

void CannonController::dutyCycle(void *pvParameters) {

    bool success = true;
    uint32_t receivedValue = 0;
    while (success) {
        receivedValue = ulTaskNotifyTake(pdTRUE, getTakeDelay());

        if (receivedValue != 0) {
            receivedValue = 0;
            setElevationStateFromCommand();
        }

        if (shouldFire()) {
            fireCannon(TurretState::cannonState->signalId);
        }

        updateTurretState();
    }
}

TickType_t CannonController::getTakeDelay() {
    return Taskr::getMillis(90);
}

bool CannonController::fireCannon(CannonSignal signal) {
    bool signalSuccess = transmitSignal(signal);
    Indicator::alertStrobeFast(CANNON_LED);
    return signalSuccess;
}

bool CannonController::transmitSignal(CannonSignal signal) {
    switch (signal) {
        case CannonSignal::BLUE:
            cannon->send(blueSignal, signalDataLength, 36);
            break;
        case CannonSignal::RED:
            cannon->send(redSignal, signalDataLength, 36);
            break;
        case CannonSignal::PURPLE:
            cannon->send(purpleSignal, signalDataLength, 36);
            break;
    }
    return true;
}

void CannonController::updateTurretState() {
    if (TurretState::cannonState->burstIndex == (TurretState::cannonState->burstLength - 1)) {
        TurretState::cannonState->isFiring = false;
        TurretState::cannonState->burstIndex = 0;
        TurretState::cannonState->burstLength = 0;
        TurretState::cannonCommand->status = CommandStatus::COMPLETE;
    }
    else if (TurretState::cannonState->burstLength > 0) {
        TurretState::cannonState->burstIndex++;
    }
}

void CannonController::setElevationStateFromCommand() {
    TurretState::cannonState->burstIndex = 0;
    TurretState::cannonState->burstLength = TurretState::cannonCommand->burstLength;
    TurretState::cannonState->signalId = TurretState::cannonCommand->signalId;
    TurretState::cannonState->isFiring = TurretState::cannonCommand->burstLength > 0;
    TurretState::cannonCommand->status = CommandStatus::IN_PROGRESS;
}

bool CannonController::shouldFire() {
    return TurretState::cannonState->burstIndex < (TurretState::cannonState->burstLength - 1);
}
