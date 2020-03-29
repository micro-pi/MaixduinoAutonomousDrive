#include <FreeRTOS.h>

#include "devices/AllDevices.h"
#include "modules/AllModules.h"
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

void task100ms(void *arg) {
  const TickType_t xFrequency = 100;
  TickType_t xLastWakeTime;
  uint32_t n = NUM_OF_MODULES_100MS;
  uint32_t i;
  /* Initialise the xLastWakeTime variable with the current time. */
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    for (i = 0; i < n; i++) {
      MODULES_100MS[i]->mainFunction();
    }

    /* Wait for the next cycle. */
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(xFrequency));
  }
}
