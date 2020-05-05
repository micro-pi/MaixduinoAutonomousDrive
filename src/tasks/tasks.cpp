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

void task10ms(void *arg) {
  const TickType_t xFrequency = 10;
  TickType_t xLastWakeTime;
  uint32_t i;
  /* Initialise the xLastWakeTime variable with the current time. */
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    for (i = 0; i < NUM_OF_MODULES_10MS; i++) {
      MODULES_10MS[i]->mainFunction();
    }

    /* Wait for the next cycle. */
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(xFrequency));
  }
}

void task20ms(void *arg) {
  const TickType_t xFrequency = 20;
  TickType_t xLastWakeTime;
  uint32_t i;
  /* Initialise the xLastWakeTime variable with the current time. */
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    for (i = 0; i < NUM_OF_MODULES_20MS; i++) {
      MODULES_20MS[i]->mainFunction();
    }

    /* Wait for the next cycle. */
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(xFrequency));
  }
}

void task50ms(void *arg) {
  const TickType_t xFrequency = 50;
  TickType_t xLastWakeTime;
  uint32_t i;
  /* Initialise the xLastWakeTime variable with the current time. */
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    for (i = 0; i < NUM_OF_MODULES_50MS; i++) {
      MODULES_50MS[i]->mainFunction();
    }

    /* Wait for the next cycle. */
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(xFrequency));
  }
}

void task100ms(void *arg) {
  const TickType_t xFrequency = 100;
  TickType_t xLastWakeTime;
  uint32_t i;
  /* Initialise the xLastWakeTime variable with the current time. */
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    for (i = 0; i < NUM_OF_MODULES_100MS; i++) {
      MODULES_100MS[i]->mainFunction();
    }

    /* Wait for the next cycle. */
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(xFrequency));
  }
}

void task10ms2(void *arg) {
  const TickType_t xFrequency = 10;
  TickType_t xLastWakeTime;
  uint32_t i;
  /* Initialise the xLastWakeTime variable with the current time. */
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    for (i = 0; i < NUM_OF_MODULES_10MS2; i++) {
      MODULES_10MS2[i]->mainFunction();
    }

    /* Wait for the next cycle. */
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(xFrequency));
  }
}

void task1000ms(void *arg) {
  const TickType_t xFrequency = 1000;
  TickType_t xLastWakeTime;
  uint32_t i;
  /* Initialise the xLastWakeTime variable with the current time. */
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    for (i = 0; i < NUM_OF_MODULES_1000MS; i++) {
      MODULES_1000MS[i]->mainFunction();
    }

    /* Wait for the next cycle. */
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(xFrequency));
  }
}