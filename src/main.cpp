#include <project_cfg.h>

#include <FreeRTOS.h>

#include <stdio.h>
#include <task.h>

#include <tasks.h>

#include "modules/camera/CameraModule.h"
#include "modules/circular_queue/CircularQueue.h"
#include "modules/cmd/CommandModule.h"
#include "modules/moving/MovingModule.h"

static CircularQueue<MovingModuleInterface> movingModuleCommands(10);
static CommandModule commandModule("Command Module", movingModuleCommands);
static MovingModule movingModule("Moving Module", movingModuleCommands, MOVING_PWM_FREQUENCY, LEFT_CHANNEL_FORWARD, LEFT_CHANNEL_BACK, RIGHT_CHANNEL_FORWARD, RIGHT_CHANNEL_BACK);
static CameraModule cameraModule("Camera Module");

Module *modules[] = {
    &commandModule,
    &movingModule,
    &cameraModule};

void init() {
  uint32_t n = sizeof(modules) / sizeof(Module *);
  uint32_t i;

  printf("Modules: %d\r\n", n);

  for (i = 0; i < n; i++) {
    printf("Init module '%s'\r\n", modules[i]->getName());
    modules[i]->init();
  }
}

void task100ms(void *arg) {
  const TickType_t xFrequency = 100;
  TickType_t xLastWakeTime;
  uint32_t n = sizeof(modules) / sizeof(Module *);
  uint32_t i;
  /* Initialise the xLastWakeTime variable with the current time. */
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    for (i = 0; i < n; i++) {
      modules[i]->mainFunction();
    }

    /* Wait for the next cycle. */
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(xFrequency));
  }
}

int main() {
  BaseType_t xReturn;
  printf("Start init\r\n");
  init();
  printf("Initialized\r\n");

  printf("Run task %s\r\n", "vPowerBlinkTaskCore0");
  xReturn = xTaskCreateAtProcessor(CORE_0, &vPowerBlinkTaskCore0, "vPowerBlinkTaskCore0", 256, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    printf("Task %s run problem\r\n", "vPowerBlinkTaskCore0");
  } else {
    printf("Rask %s is running\r\n", "vPowerBlinkTaskCore0");
  }

  printf("Run task %s\r\n", "task100ms");
  xReturn = xTaskCreateAtProcessor(CORE_1, &task100ms, "task100ms", 4096, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    printf("Task %s run problem\r\n", "task100ms");
  } else {
    printf("Rask %s is running\r\n", "task100ms");
  }

  for (;;) {
  }
}

/*
#include <devices.h>
#include <stdio.h>

#include <pin_cfg.h>

const fpioa_cfg_t g_fpioa_cfg =
    {
        .version = PIN_CFG_VERSION,
        .functions_count = 2,
        .functions =
            {
                {22, FUNC_TIMER0_TOGGLE1},
                {23, FUNC_TIMER0_TOGGLE2}}};

#define CHANNEL1 (0)
#define CHANNEL2 (1)

handle_t pwm0;
// handle_t timer;

// void irq_time(void *userdata) {
//   static double cnt = 0.01;
//   static int flag = 0;
//   pwm_set_active_duty_cycle_percentage(pwm0, CHANNEL1, cnt);
//   flag ? (cnt -= 0.01) : (cnt += 0.01);
//   if (cnt > 1.0) {
//     cnt = 1.0;
//     flag = 1;
//   } else if (cnt < 0.0) {
//     cnt = 0.0;
//     flag = 0;
//   }
// }

int main() {
  pwm0 = io_open("/dev/pwm0");
  configASSERT(pwm0);
  pwm_set_frequency(pwm0, 1000); //set 200KHZ
  pwm_set_enable(pwm0, CHANNEL1, false);
  pwm_set_enable(pwm0, CHANNEL2, false);
  pwm_set_active_duty_cycle_percentage(pwm0, CHANNEL1, 0.5); //duty 50%
  pwm_set_active_duty_cycle_percentage(pwm0, CHANNEL2, 0.1); //duty 50%
  pwm_set_enable(pwm0, CHANNEL1, true);
  pwm_set_enable(pwm0, CHANNEL2, true);

  // timer = io_open("/dev/timer10");
  // configASSERT(timer);

  // timer_set_interval(timer, 1e7);
  // timer_set_on_tick(timer, irq_time, NULL);
  // timer_set_enable(timer, 1);

  while (1)
    ;
}
*/
