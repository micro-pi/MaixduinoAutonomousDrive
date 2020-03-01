#include <project_cfg.h>

#include <FreeRTOS.h>

#include <stdio.h>
#include <task.h>

#include <tasks.h>

#include "modules/moving/MovingModule.h"

int main() {
  BaseType_t xReturn;

  MovingModule movingModule;
  movingModule.init();
  movingModule.mainFunction();

  xReturn = xTaskCreateAtProcessor(CORE_0, &vPowerBlinkTaskCore0, "vPowerBlinkTaskCore0", 256, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    printf("Task %s run problem\r\n", "vPowerBlinkTaskCore0");
  }

  for (;;) {
  }
}