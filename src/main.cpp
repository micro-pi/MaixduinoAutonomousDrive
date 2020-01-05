#include <project_cfg.h>

#include <FreeRTOS.h>

#include <stdio.h>
#include <task.h>

#include <tasks.h>

int main() {
  BaseType_t xReturn;

  xReturn = xTaskCreateAtProcessor(CORE_0, &vPowerBlinkTaskCore0, "vPowerBlinkTaskCore0", 256, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    printf("Task %s run problem\r\n", "vPowerBlinkTaskCore0");
  }

  for (;;) {
  }
}