#include "MovingModule.h"

MovingModule::MovingModule(const char *moduleName, CircularQueue<MovingModuleInterface> &movingModuleCmds, const double frequency, const uint32_t leftChannelF, const uint32_t leftChannelB, const uint32_t rightChannelF, const uint32_t rightChannelB) : Module(moduleName), movingModuleCommands(movingModuleCmds) {
  this->pwm = 0;
  this->frequency = frequency;
  this->leftChannelF = leftChannelF;
  this->leftChannelB = leftChannelB;
  this->rightChannelF = rightChannelF;
  this->rightChannelB = rightChannelB;
}

ErrorCode MovingModule::init(void) {
  ErrorCode errorCode;
  this->pwm = io_open("/dev/pwm0");
  configASSERT(this->pwm);
  if (this->pwm == 0) {
    errorCode = E_NOK;
  } else {
    pwm_set_frequency(this->pwm, this->frequency);
    pwm_set_enable(this->pwm, this->leftChannelF, false);
    pwm_set_enable(this->pwm, this->leftChannelB, false);
    pwm_set_enable(this->pwm, this->rightChannelF, false);
    pwm_set_enable(this->pwm, this->rightChannelB, false);
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
