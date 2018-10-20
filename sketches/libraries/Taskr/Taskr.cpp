#include "Taskr.h"
#include <Arduino_FreeRTOS.h>
#include <task.h>


TickType_t Taskr::getMillis(int millisToConvert) {
    return millisToConvert/portTICK_PERIOD_MS;
}

void Taskr::delayMs(int millisToConvert) {
    vTaskDelay(Taskr::getMillis(millisToConvert));
}
