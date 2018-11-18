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

void CannonController::functionCheckDemo(void* pvParameters) {

    for (int idx = 0; idx < 6; idx++) {
        Indicator::alertStrobeFast(CANNON_LED);
        vTaskDelay(600/portTICK_PERIOD_MS);
    }
}

bool CannonController::initialize() {
    Indicator::turnOffLed(CANNON_LED);
    TurretState::cannonCommand = new CannonCommand_t();
    TurretState::cannonState = new CannonState_t();

    BaseType_t cannonStatus = xTaskCreate(
            CannonController::dutyCycle,
            (const portCHAR *) "CannonControllerTask",
            128,  // Stack size
            NULL,
            1,  // Priority
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
            TurretState::cannonState->isFiring = true;
            bool successfulFire = fireCannon(TurretState::cannonCommand->signalId,
                    TurretState::cannonCommand->burstLength);
            if (successfulFire) {
                TurretState::cannonCommand->status = CommandStatus::COMPLETE;
                TurretState::cannonState->isFiring = false;
            }
        }

    }

}

TickType_t CannonController::getTakeDelay() {
    return Taskr::getMillis(90);
}

bool CannonController::fireCannon(CannonSignal signal, int burstLength) {
    bool signalSuccess = transmitSignal(signal);
    Indicator::alertStrobeFast(CANNON_LED);
    return signalSuccess;
}

bool CannonController::transmitSignal(CannonSignal signal) {
    switch (signal) {
        case CannonSignal::BLUE:
            cannon->send(BLUE_SIGNAL, SIGNAL_DATA_LEN, 36);
            break;
        case CannonSignal::RED:
            cannon->send(RED_SIGNAL, SIGNAL_DATA_LEN, 36);
            break;
        case CannonSignal::PURPLE:
            cannon->send(PURPLE_SIGNAL, SIGNAL_DATA_LEN, 36);
            break;
    }
    return true;
}
