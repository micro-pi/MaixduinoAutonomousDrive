#include "MovingModule.h"

ErrorCode getCommand(MovingModuleInterface &movingModuleInterface) {
  /* TODO: Implement me as a normal interface */
  movingModuleInterface.command = MOVING_MODULE_COMMAND_STOP;
  movingModuleInterface.commandAttribute = MOVING_MODULE_COMMAND_ATTRIBUTE_ALL;
  movingModuleInterface.movingDirection = MOVING_MODULE_DIRECTION_NONE;
  movingModuleInterface.pwmValue = 0u;
  return E_OK;
}

MovingModule::MovingModule(void) {
}

ErrorCode MovingModule::init(void) {

  return E_OK;
}

void MovingModule::mainFunction(void) {
  MovingModuleInterface movingModuleInterface;
  ErrorCode errorCode;
  errorCode = getCommand(movingModuleInterface);
  if (errorCode == E_OK) {
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
  } else if (errorCode == E_NOK) {
    /* In case of error */
  } else {
    /* MISRA */
  }
}

MovingModule::~MovingModule(void) {
}

void MovingModule::stopCommand(const MovingModuleCommandAttribute commandAttribute) {
}

void MovingModule::startCommand(const MovingModuleCommandAttribute commandAttribute) {
}

void MovingModule::moveCommand(const MovingModuleCommandAttribute commandAttribute, const MovingModuleDirection movingDirection, const uint16_t pwmValue) {
}

void MovingModule::pwmCommand(const MovingModuleCommandAttribute commandAttribute, const uint16_t pwmValue) {
}