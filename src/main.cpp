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
  ErrorCode errorCode;
  uint32_t i;

  handle_t gpio0;
  handle_t i2c0;
  handle_t spi0;
  handle_t pwm0;

  ITG3200DlpfFsConfig dlpfFsConfig;
  ITG3200InterruptConfig interruptConfig;
  ITG3200InterruptStatus interruptStatus;

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

  itg3200.setI2c(i2c0);

  sonars.setI2c(i2c0);

  LOGI(TAG, "Devices: %d", NUM_OF_DEVICES);
  for (i = 0; i < NUM_OF_DEVICES; i++) {
    errorCode = DEVICES[i]->begin();
    if (errorCode == E_OK) {
      LOGI(TAG, "Device \"%s\" initialized successfully!", DEVICES[i]->getName());
    } else {
      LOGW(TAG, "Device \"%s\" not initialized!", DEVICES[i]->getName());
    }
  }

  /* After init devices configurations */
  if (itg3200.getErrorCode() == E_OK) {
    /* send a reset to the device */
    (void)itg3200.resetDevice();

    // itg3200.write(ITG3200_PWR_M, 0x80);   //send a reset to the device
    // itg3200.write(ITG3200_SMPL, 19); //sample rate divider

    /* sample rate divider */
    itg3200.setSampleRateDivider(19U);

    dlpfFsConfig.value = 0x00u;
    dlpfFsConfig.config.fullScaleRange = RANGE_2000_DEG_PER_SEC;
    dlpfFsConfig.config.lowPassFilter = BANDWIDTH_5HZ_RATE_1KHZ;
    itg3200.setDlpfFsConfig(dlpfFsConfig);

    interruptConfig.value = 0x00u;
    interruptConfig.config.interruptEnabled = true;
    interruptConfig.config.rawDataReadyEnabled = true;
    itg3200.setInterruptConfig(interruptConfig);

    itg3200.zeroCalibrate(20, 0);
    dlpfFsConfig = itg3200.getDlpfFsConfig();
    interruptConfig = itg3200.getInterruptConfig();
    interruptStatus = itg3200.getInterruptStatus();
    LOGI(TAG, "Device               : %s", itg3200.getName());
    LOGI(TAG, "Who Am I             : 0x%02x", itg3200.whoAmI());
    LOGI(TAG, "----Sample Rate Divider----");
    LOGI(TAG, "Sample Rate Divider  : 0x%02x", itg3200.getSampleRateDivider());
    LOGI(TAG, "------DLPF, Full Scale-----");
    LOGI(TAG, "Full scale selection : 0x%02x", dlpfFsConfig.config.fullScaleRange);
    LOGI(TAG, "Digital low pass     : 0x%02x", dlpfFsConfig.config.lowPassFilter);
    LOGI(TAG, "--Interrupt Configuration--");
    LOGI(TAG, "Logic level          : 0x%02x", interruptConfig.config.logicLevelIntOutputPin);
    LOGI(TAG, "Drive type           : 0x%02x", interruptConfig.config.driveTypeIntOutputPin);
    LOGI(TAG, "Latch mode           : 0x%02x", interruptConfig.config.latchMode);
    LOGI(TAG, "Latch clear method   : 0x%02x", interruptConfig.config.latchClearMethod);
    LOGI(TAG, "Interrupt Enabled    : 0x%02x", interruptConfig.config.interruptEnabled);
    LOGI(TAG, "Raw data ready       : 0x%02x", interruptConfig.config.rawDataReadyEnabled);
    LOGI(TAG, "------Interrupt Status-----");
    LOGI(TAG, "PLL ready            : 0x%02x", interruptStatus.status.pllReady);
    LOGI(TAG, "Raw data is ready    : 0x%02x", interruptStatus.status.rawDataReady);
    LOGI(TAG, "------Power Management-----");
    LOGI(TAG, "Low power sleep mode : 0x%02x", itg3200.isSleepMode());
    LOGI(TAG, "X in standby mode    : 0x%02x", itg3200.isStandbyModeX());
    LOGI(TAG, "Y in standby mode    : 0x%02x", itg3200.isStandbyModeY());
    LOGI(TAG, "Z in standby mode    : 0x%02x", itg3200.isStandbyModeZ());
    LOGI(TAG, "Clock source         : 0x%02x", itg3200.getClockSource());
  }

  /* Initialize Modules 10ms */
  k210Esp32Communication.setMovingModuleCommandsQueue(movingModuleCommandsQueue);
  k210Esp32Communication.setEsp32Device(esp32);

  /* Initialize Modules 10ms 2 */
  gyroModule.setMovingModuleCommandsQueue(movingModuleCommandsQueue);
  gyroModule.setITG3200(itg3200);
  gyroModule.setGlobalData(globalData);
  gyroModule.setMovingModule(movingModule);

  /* Initialize Modules 20ms */
  sonarsModule.setSonars(sonars);
  sonarsModule.setGlobalData(globalData);

  /* Initialize Modules 50ms */
  autonomusModule.setGlobalData(globalData);

  /* Initialize Modules 100ms */
  movingModule.setMovingModuleCommandsQueue(movingModuleCommandsQueue);
  movingModule.setMainMotorLeft(mainMotorLeft);
  movingModule.setMainMotorRight(mainMotorRight);
  movingModule.setGlobalData(globalData);

  /* Initialize Modules 1000ms */

  LOGI(TAG, "Modules 10ms: %d", NUM_OF_MODULES_10MS);
  for (i = 0; i < NUM_OF_MODULES_10MS; i++) {
    LOGI(TAG, "Init module '%s'", MODULES_10MS[i]->getName());
    errorCode = MODULES_10MS[i]->init();
    if (errorCode == E_OK) {
      LOGI(TAG, "Module \"%s\" initialized successfully!", MODULES_10MS[i]->getName());
    } else {
      LOGW(TAG, "Module \"%s\" not initialized!", MODULES_10MS[i]->getName());
    }
  }

  LOGI(TAG, "Modules 10ms2: %d", NUM_OF_MODULES_10MS2);
  for (i = 0; i < NUM_OF_MODULES_10MS2; i++) {
    LOGI(TAG, "Init module '%s'", MODULES_10MS2[i]->getName());
    errorCode = MODULES_10MS2[i]->init();
    if (errorCode == E_OK) {
      LOGI(TAG, "Module \"%s\" initialized successfully!", MODULES_10MS2[i]->getName());
    } else {
      LOGW(TAG, "Module \"%s\" not initialized!", MODULES_10MS2[i]->getName());
    }
  }

  LOGI(TAG, "Modules 20ms: %d", NUM_OF_MODULES_20MS);
  for (i = 0; i < NUM_OF_MODULES_20MS; i++) {
    LOGI(TAG, "Init module '%s'", MODULES_20MS[i]->getName());
    errorCode = MODULES_20MS[i]->init();
    if (errorCode == E_OK) {
      LOGI(TAG, "Module \"%s\" initialized successfully!", MODULES_20MS[i]->getName());
    } else {
      LOGW(TAG, "Module \"%s\" not initialized!", MODULES_20MS[i]->getName());
    }
  }

  LOGI(TAG, "Modules 50ms: %d", NUM_OF_MODULES_50MS);
  for (i = 0; i < NUM_OF_MODULES_50MS; i++) {
    LOGI(TAG, "Init module '%s'", MODULES_50MS[i]->getName());
    errorCode = MODULES_50MS[i]->init();
    if (errorCode == E_OK) {
      LOGI(TAG, "Module \"%s\" initialized successfully!", MODULES_50MS[i]->getName());
    } else {
      LOGW(TAG, "Module \"%s\" not initialized!", MODULES_50MS[i]->getName());
    }
  }

  LOGI(TAG, "Modules 100ms: %d", NUM_OF_MODULES_100MS);
  for (i = 0; i < NUM_OF_MODULES_100MS; i++) {
    LOGI(TAG, "Init module '%s'", MODULES_100MS[i]->getName());
    errorCode = MODULES_100MS[i]->init();
    if (errorCode == E_OK) {
      LOGI(TAG, "Module \"%s\" initialized successfully!", MODULES_100MS[i]->getName());
    } else {
      LOGW(TAG, "Module \"%s\" not initialized!", MODULES_100MS[i]->getName());
    }
  }

  LOGI(TAG, "Modules 1000ms: %d", NUM_OF_MODULES_1000MS);
  for (i = 0; i < NUM_OF_MODULES_1000MS; i++) {
    LOGI(TAG, "Init module '%s'", MODULES_1000MS[i]->getName());
    errorCode = MODULES_1000MS[i]->init();
    if (errorCode == E_OK) {
      LOGI(TAG, "Module \"%s\" initialized successfully!", MODULES_1000MS[i]->getName());
    } else {
      LOGW(TAG, "Module \"%s\" not initialized!", MODULES_1000MS[i]->getName());
    }
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

  LOGI(TAG, "Run task %s", "task10ms");
  xReturn = xTaskCreateAtProcessor(CORE_0, &task10ms, "task10ms", 4096, NULL, 5, NULL);
  if (xReturn != pdPASS) {
    LOGI(TAG, "Task %s run problem", "task10ms");
  } else {
    LOGI(TAG, "Rask %s is running", "task10ms");
  }

  LOGI(TAG, "Run task %s", "task20ms");
  xReturn = xTaskCreateAtProcessor(CORE_0, &task20ms, "task20ms", 4096, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    LOGI(TAG, "Task %s run problem", "task20ms");
  } else {
    LOGI(TAG, "Rask %s is running", "task20ms");
  }

  LOGI(TAG, "Run task %s", "task100ms");
  xReturn = xTaskCreateAtProcessor(CORE_1, &task100ms, "task100ms", 4096, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    LOGI(TAG, "Task %s run problem", "task100ms");
  } else {
    LOGI(TAG, "Rask %s is running", "task100ms");
  }

  LOGI(TAG, "Run task %s", "task10ms2");
  xReturn = xTaskCreateAtProcessor(CORE_1, &task10ms2, "task10ms2", 4096, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    LOGI(TAG, "Task %s run problem", "task10ms2");
  } else {
    LOGI(TAG, "Rask %s is running", "task10ms2");
  }

  LOGI(TAG, "Run task %s", "task1000ms");
  xReturn = xTaskCreateAtProcessor(CORE_1, &task1000ms, "task1000ms", 8192, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    LOGI(TAG, "Task %s run problem", "task1000ms");
  } else {
    LOGI(TAG, "Rask %s is running", "task1000ms");
  }

  LOGI(TAG, "Run task %s", "task50ms");
  xReturn = xTaskCreateAtProcessor(CORE_0, &task50ms, "task50ms", 4096, NULL, 2, NULL);
  if (xReturn != pdPASS) {
    LOGI(TAG, "Task %s run problem", "task50ms");
  } else {
    LOGI(TAG, "Rask %s is running", "task50ms");
  }

  for (;;) {
  }
}
