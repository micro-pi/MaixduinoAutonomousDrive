#include <project_cfg.h>

#include <FreeRTOS.h>

#include <stdio.h>
#include <string.h>
#include <task.h>

#include <tasks.h>

#include "modules/camera/CameraModule.h"
#include "modules/circular_queue/CircularQueue.h"
#include "modules/cmd/CommandModule.h"
#include "modules/moving/MovingModule.h"

#include "devices/esp32/ESP32.h"
#include "devices/itg3200/ITG3200.h"
#include "devices/main_motor/MainMotor.h"

static ESP32 esp32("ESP32");
static ITG3200 gyro("ITG3205");
static MainMotor mainMotorLeft("Left Main Motor");
static MainMotor mainMotorRight("Right Main Motor");

static CircularQueue<MovingModuleInterface> movingModuleCommands(10);
static CommandModule commandModule("Command Module", movingModuleCommands);
static MovingModule movingModule("Moving Module", movingModuleCommands, mainMotorLeft, mainMotorRight);
static CameraModule cameraModule("Camera Module");

static Device *DEVICES[] = {
    &esp32,
    &gyro,
    &mainMotorLeft,
    &mainMotorRight,
};

static Module *MODULES_100MS[] = {
    &commandModule,
    &movingModule,
    &cameraModule,
};

#define NUM_OF_MODULES_100MS (sizeof(MODULES_100MS) / sizeof(Module *))
#define NUM_OF_DEVICES (sizeof(DEVICES) / sizeof(Device *))

static K210ESP32Data spi0Esp32TxBuffer;
static K210ESP32Data spi0Esp32RxBuffer;

void init() {
  uint32_t numOfModules = NUM_OF_MODULES_100MS;
  uint32_t numOfDevices = NUM_OF_DEVICES;
  uint32_t i;

  handle_t i2c0;
  handle_t spi0;
  handle_t pwm0;

  pwm0 = io_open("/dev/pwm0");
  i2c0 = io_open("/dev/i2c0");
  spi0 = io_open("/dev/spi0");

  /* Before init devices configurations */
  mainMotorLeft.setPwm(pwm0);
  mainMotorLeft.setFrequency(MOVING_PWM_FREQUENCY);
  mainMotorLeft.setForwardChannel(LEFT_CHANNEL_FORWARD);
  mainMotorLeft.setBackwardChannel(LEFT_CHANNEL_BACK);

  mainMotorRight.setPwm(pwm0);
  mainMotorRight.setFrequency(MOVING_PWM_FREQUENCY);
  mainMotorRight.setForwardChannel(RIGHT_CHANNEL_FORWARD);
  mainMotorRight.setBackwardChannel(RIGHT_CHANNEL_BACK);

  esp32.setSpi(spi0);
  esp32.setMode(SPI_MODE_2);
  esp32.setClockRate(SPI_MASTER_CLOCK_RATE);

  gyro.setI2c(i2c0);

  printf("Devices: %d\r\n", numOfDevices);
  for (i = 0; i < numOfDevices; i++) {
    DEVICES[i]->begin();
  }
  /* TODO: Add methods to check if devices are present and initialized */
  /* After init devices configurations */
  gyro.setFullScaleSelection(RANGE_2000_DEG_PER_SEC);
  gyro.setDigitalLowPassFilter(BANDWIDTH_5HZ_RATE_1KHZ);
  gyro.setRawDataReadyEnabled(true);

  printf("Who Am I             : 0x%02x\r\n", gyro.whoAmI());
  printf("\r\n----Sample Rate Divider----\r\n");
  printf("Sample Rate Divider  : 0x%02x\r\n", gyro.getSampleRateDivider());
  printf("\r\n------DLPF, Full Scale-----\r\n");
  printf("Full scale selection : 0x%02x\r\n", gyro.getFullScaleSelection());
  printf("Digital low pass     : 0x%02x\r\n", gyro.getDigitalLowPassFilter());
  printf("\r\n--Interrupt Configuration--\r\n");
  printf("Logic level          : 0x%02x\r\n", gyro.getLogicLevelIntOutputPin());
  printf("Drive type           : 0x%02x\r\n", gyro.getDriveTypeIntOutputPin());
  printf("Latch mode           : 0x%02x\r\n", gyro.getLatchMode());
  printf("Latch clear method   : 0x%02x\r\n", gyro.getLatchClearMethod());
  printf("Interrupt Enabled    : 0x%02x\r\n", gyro.isInterruptEnabled());
  printf("Raw data ready       : 0x%02x\r\n", gyro.isRawDataReadyEnabled());
  printf("\r\n------Interrupt Status-----\r\n");
  printf("PLL ready            : 0x%02x\r\n", gyro.isPllReady());
  printf("Raw data is ready    : 0x%02x\r\n", gyro.isRawDataReady());
  printf("\r\n------Power Management-----\r\n");
  printf("Low power sleep mode : 0x%02x\r\n", gyro.isSleepMode());
  printf("X in standby mode    : 0x%02x\r\n", gyro.isStandbyModeX());
  printf("Y in standby mode    : 0x%02x\r\n", gyro.isStandbyModeY());
  printf("Z in standby mode    : 0x%02x\r\n", gyro.isStandbyModeZ());
  printf("Clock source         : 0x%02x\r\n", gyro.getClockSource());

  printf("Modules: %d\r\n", numOfModules);

  for (i = 0; i < numOfModules; i++) {
    printf("Init module '%s'\r\n", MODULES_100MS[i]->getName());
    MODULES_100MS[i]->init();
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
void task1000ms(void *arg) {
  const TickType_t xFrequency = 1000;
  TickType_t xLastWakeTime;

  /* Initialise the xLastWakeTime variable with the current time. */
  xLastWakeTime = xTaskGetTickCount();

  while (1) {
    sprintf((char *)spi0Esp32TxBuffer.data, "Hello ESP32, xLastWakeTime: %d", xLastWakeTime);
    spi0Esp32TxBuffer.type = STRING;
    spi0Esp32TxBuffer.id = (uint8_t)xLastWakeTime;
    spi0Esp32TxBuffer.size = strlen((char *)spi0Esp32TxBuffer.data);
    esp32.transferFullDuplex(spi0Esp32TxBuffer, spi0Esp32RxBuffer);

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

  printf("Run task %s\r\n", "task1000ms");
  xReturn = xTaskCreateAtProcessor(CORE_0, &task1000ms, "task1000ms", 4096, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    printf("Task %s run problem\r\n", "task1000ms");
  } else {
    printf("Rask %s is running\r\n", "task1000ms");
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
