#include "MovingModule.h"
#include <syslog.h>

MovingModule::MovingModule(const char *moduleName) : Module(moduleName) {
  this->movingModuleCommandsQueue = nullptr;
  this->mainMotorLeft = nullptr;
  this->mainMotorRight = nullptr;
}

ErrorCode MovingModule::init(void) {
  ErrorCode errorCode;
  errorCode = E_OK;
  return errorCode;
}

void MovingModule::setMovingModuleCommandsQueue(xQueueHandle movingModuleCommandsQueue) {
  this->movingModuleCommandsQueue = movingModuleCommandsQueue;
}

void MovingModule::setMainMotorLeft(MainMotor &mainMotorLeft) {
  this->mainMotorLeft = &mainMotorLeft;
}

void MovingModule::setMainMotorRight(MainMotor &mainMotorRight) {
  this->mainMotorRight = &mainMotorRight;
}

void MovingModule::mainFunction(void) {
  portBASE_TYPE xStatus;

  if (this->movingModuleCommandsQueue != nullptr) {
    xStatus = xQueueReceive(this->movingModuleCommandsQueue, &lastCmd, portMAX_DELAY);
    if (xStatus == pdPASS) {
      switch (lastCmd.command) {
        case MOVING_MODULE_COMMAND_STOP:
          stopCommand(lastCmd.commandAttribute);
          break;

        case MOVING_MODULE_COMMAND_START:
          startCommand(lastCmd.commandAttribute);
          break;

        case MOVING_MODULE_COMMAND_MOVE:
          moveCommand(lastCmd.commandAttribute, lastCmd.movingDirection, lastCmd.pwmValue);
          break;

        case MOVING_MODULE_COMMAND_PWM:
          pwmCommand(lastCmd.commandAttribute, lastCmd.pwmValue);
          break;

        default:
          /* Unsupported command */
          break;
      }
    } else {
      /* MISRA : the queue is empty */
    }
  }
}

MovingModule::~MovingModule(void) {
}

void MovingModule::stopCommand(const MovingModuleCommandAttribute commandAttribute) {
  /* TODO: look here https://github.com/kendryte/kendryte-freertos-demo/blob/develop/pwm/main.c */
}

void MovingModule::startCommand(const MovingModuleCommandAttribute commandAttribute) {
}

void MovingModule::moveCommand(const MovingModuleCommandAttribute commandAttribute, const MovingModuleDirection movingDirection, const uint16_t pwmValue) {
}

void MovingModule::pwmCommand(const MovingModuleCommandAttribute commandAttribute, const uint16_t pwmValue) {
}
