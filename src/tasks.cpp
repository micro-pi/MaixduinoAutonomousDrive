#include <FreeRTOS.h>

#include <Led.h>
#include <project_cfg.h>
#include <stdio.h>
#include <task.h>
#include <tasks.h>
#include <utils.h>

void vPowerBlinkTaskCore0(void *arg) {
  const TickType_t xFrequency = 500;
  handle_t gpio0;
  TickType_t xLastWakeTime;

  /* Initialise the xLastWakeTime variable with the current time. */
  xLastWakeTime = xTaskGetTickCount();
  gpio0 = io_open("/dev/gpio0");

  Led blinker(gpio0, LED_PIN);
  blinker.begin();
  while (1) {
    blinker.blink();

    /* Wait for the next cycle. */
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(xFrequency));
  }
}
