#include "MovingModule.h"

MovingModule::MovingModule(CircularQueue<MovingModuleInterface> &movingModuleCmds, const double frequency, const uint32_t leftPinF, const uint32_t leftPinB, const uint32_t rightPinF, const uint32_t rightPinB) : movingModuleCommands(movingModuleCmds) {
  this->pwm0 = 0;
  this->frequency = frequency;
  this->leftPinF = leftPinF;
  this->leftPinB = leftPinB;
  this->rightPinF = rightPinF;
  this->rightPinB = rightPinB;
}

ErrorCode MovingModule::init(void) {
  ErrorCode errorCode;
  pwm0 = io_open("/dev/pwm0");
  configASSERT(pwm0);
  if (pwm0 == 0) {
    errorCode = E_NOK;
  } else {
    pwm_set_frequency(pwm0, frequency);
    errorCode = E_OK;
  }

  return errorCode;
}

void MovingModule::mainFunction(void) {
  MovingModuleInterface movingModuleInterface;
  bool isNotEmpty;

  isNotEmpty = movingModuleCommands.deQueue(movingModuleInterface);
  if (true == isNotEmpty) {
    switch (movingModuleInterface.command) {
      case MOVING_MODULE_COMMAND_STOP:
        stopCommand(movingModuleInterface.commandAttribute);
        break;

      case MOVING_MODULE_COMMAND_START:
        startCommand(movingModuleInterface.commandAttribute);
        break;

      case MOVING_MODULE_COMMAND_MOVE:
        moveCommand(movingModuleInterface.commandAttribute, movingModuleInterface.movingDirection, movingModuleInterface.pwmValue);
        break;

      case MOVING_MODULE_COMMAND_PWM:
        pwmCommand(movingModuleInterface.commandAttribute, movingModuleInterface.pwmValue);
        break;

      default:
        /* Unsupported command */
        break;
    }
  } else {
    /* MISRA : the queue is empty */
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
