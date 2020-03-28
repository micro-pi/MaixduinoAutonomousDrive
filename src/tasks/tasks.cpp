#include <FreeRTOS.h>

#include "AllDevices.h"
#include "tasks.h"
#include <project_cfg.h>
#include <task.h>

void vPowerBlinkTaskCore0(void *arg) {
  const TickType_t xFrequency = 500;
  TickType_t xLastWakeTime;

  /* Initialise the xLastWakeTime variable with the current time. */
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    powerLed.blink();

    /* Wait for the next cycle. */
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(xFrequency));
  }
}
