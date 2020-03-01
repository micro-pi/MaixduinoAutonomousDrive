#include <project_cfg.h>

#include <FreeRTOS.h>

#include <stdio.h>
#include <task.h>

#include <tasks.h>

#include "modules/moving/MovingModule.h"

int main() {
  BaseType_t xReturn;
  double frequency = 2000;
  uint32_t leftPinF = 0;
  uint32_t leftPinB = 1;
  uint32_t rightPinF = 2;
  uint32_t rightPinB = 3;
  MovingModule movingModule(frequency, leftPinF, leftPinB, rightPinF, rightPinB);
  movingModule.init();
  movingModule.mainFunction();

  xReturn = xTaskCreateAtProcessor(CORE_0, &vPowerBlinkTaskCore0, "vPowerBlinkTaskCore0", 256, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    printf("Task %s run problem\r\n", "vPowerBlinkTaskCore0");
  }

  for (;;) {
  }
}