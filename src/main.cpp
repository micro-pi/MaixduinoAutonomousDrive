#include <project_cfg.h>

#include <FreeRTOS.h>

#include <string.h>
#include <syslog.h>
#include <task.h>

#include "tasks/tasks.h"

#include "devices/AllDevices.h"
#include "modules/AllModules.h"

static const char *TAG = "MAD_K210";

/* Objects */
static xQueueHandle movingModuleCommandsQueue;

void init() {
  uint32_t i;

  handle_t gpio0;
  handle_t i2c0;
  handle_t spi0;
  handle_t pwm0;

  /* Initialize Objects */
  movingModuleCommandsQueue = xQueueCreate(16, sizeof(MovingModuleInterface));

  gpio0 = io_open("/dev/gpio0");
  pwm0 = io_open("/dev/pwm0");
  i2c0 = io_open("/dev/i2c0");
  spi0 = io_open("/dev/spi0");

  /* Initialize Devices */
  powerLed.setGpio(gpio0);
  powerLed.setPin(POWER_LED_PIN);

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

  LOGI(TAG, "Devices: %d", NUM_OF_DEVICES);
  for (i = 0; i < NUM_OF_DEVICES; i++) {
    DEVICES[i]->begin();
  }
  /* TODO: Add methods to check if devices are present and initialized */
  /* After init devices configurations */
  gyro.setFullScaleSelection(RANGE_2000_DEG_PER_SEC);
  gyro.setDigitalLowPassFilter(BANDWIDTH_5HZ_RATE_1KHZ);
  gyro.setRawDataReadyEnabled(true);

  LOGI(TAG, "Who Am I             : 0x%02x", gyro.whoAmI());
  LOGI(TAG, "----Sample Rate Divider----");
  LOGI(TAG, "Sample Rate Divider  : 0x%02x", gyro.getSampleRateDivider());
  LOGI(TAG, "------DLPF, Full Scale-----");
  LOGI(TAG, "Full scale selection : 0x%02x", gyro.getFullScaleSelection());
  LOGI(TAG, "Digital low pass     : 0x%02x", gyro.getDigitalLowPassFilter());
  LOGI(TAG, "--Interrupt Configuration--");
  LOGI(TAG, "Logic level          : 0x%02x", gyro.getLogicLevelIntOutputPin());
  LOGI(TAG, "Drive type           : 0x%02x", gyro.getDriveTypeIntOutputPin());
  LOGI(TAG, "Latch mode           : 0x%02x", gyro.getLatchMode());
  LOGI(TAG, "Latch clear method   : 0x%02x", gyro.getLatchClearMethod());
  LOGI(TAG, "Interrupt Enabled    : 0x%02x", gyro.isInterruptEnabled());
  LOGI(TAG, "Raw data ready       : 0x%02x", gyro.isRawDataReadyEnabled());
  LOGI(TAG, "------Interrupt Status-----");
  LOGI(TAG, "PLL ready            : 0x%02x", gyro.isPllReady());
  LOGI(TAG, "Raw data is ready    : 0x%02x", gyro.isRawDataReady());
  LOGI(TAG, "------Power Management-----");
  LOGI(TAG, "Low power sleep mode : 0x%02x", gyro.isSleepMode());
  LOGI(TAG, "X in standby mode    : 0x%02x", gyro.isStandbyModeX());
  LOGI(TAG, "Y in standby mode    : 0x%02x", gyro.isStandbyModeY());
  LOGI(TAG, "Z in standby mode    : 0x%02x", gyro.isStandbyModeZ());
  LOGI(TAG, "Clock source         : 0x%02x", gyro.getClockSource());

  /* Initialize Modules 100ms */
  movingModule.setMovingModuleCommandsQueue(movingModuleCommandsQueue);
  movingModule.setMainMotorLeft(mainMotorLeft);
  movingModule.setMainMotorRight(mainMotorRight);

  LOGI(TAG, "Modules 100ms: %d", NUM_OF_MODULES_100MS);
  for (i = 0; i < NUM_OF_MODULES_100MS; i++) {
    LOGI(TAG, "Init module '%s'", MODULES_100MS[i]->getName());
    MODULES_100MS[i]->init();
  }

  /* Initialize Modules 1000ms */
  k210Esp32Communication.setMovingModuleCommandsQueue(movingModuleCommandsQueue);
  k210Esp32Communication.setEsp32Device(esp32);

  LOGI(TAG, "Modules 1000ms: %d", NUM_OF_MODULES_1000MS);
  for (i = 0; i < NUM_OF_MODULES_1000MS; i++) {
    LOGI(TAG, "Init module '%s'", MODULES_1000MS[i]->getName());
    MODULES_1000MS[i]->init();
  }
}

int main() {
  BaseType_t xReturn;
  LOGI(TAG, "Start init");
  init();
  LOGI(TAG, "Initialized");

  LOGI(TAG, "Run task %s", "vPowerBlinkTaskCore0");
  xReturn = xTaskCreateAtProcessor(CORE_0, &vPowerBlinkTaskCore0, "vPowerBlinkTaskCore0", 256, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    LOGI(TAG, "Task %s run problem", "vPowerBlinkTaskCore0");
  } else {
    LOGI(TAG, "Rask %s is running", "vPowerBlinkTaskCore0");
  }

  LOGI(TAG, "Run task %s", "task1000ms");
  xReturn = xTaskCreateAtProcessor(CORE_0, &task1000ms, "task1000ms", 4096, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    LOGI(TAG, "Task %s run problem", "task1000ms");
  } else {
    LOGI(TAG, "Rask %s is running", "task1000ms");
  }

  LOGI(TAG, "Run task %s", "task100ms");
  xReturn = xTaskCreateAtProcessor(CORE_1, &task100ms, "task100ms", 4096, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    LOGI(TAG, "Task %s run problem", "task100ms");
  } else {
    LOGI(TAG, "Rask %s is running", "task100ms");
  }

  for (;;) {
  }
}
