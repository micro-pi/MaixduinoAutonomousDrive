#include "MovingModule.h"
#include <syslog.h>

MovingModule::MovingModule(const char *moduleName) : Module(moduleName) {
  this->movingModuleCommandsQueue = nullptr;
  this->mainMotorLeft = nullptr;
  this->mainMotorRight = nullptr;
}

ErrorCode MovingModule::initModule(void) {
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

void MovingModule::setGlobalData(GlobalData &globalData) {
  this->globalData = &globalData;
}

void MovingModule::mainFunction(void) {
  MovingModuleInterface lastCmdCopy;
  portBASE_TYPE xStatus;

  if (this->movingModuleCommandsQueue != nullptr) {
    xStatus = xQueueReceive(this->movingModuleCommandsQueue, &lastCmd, 0);
    if (xStatus == pdPASS) {
      if (globalData != nullptr) {
        lastCmdCopy = lastCmd;
        globalData->setMovingModuleInterface(lastCmd);
      }
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

MovingModuleCommands MovingModule::getLastMovingModuleCommands(void) {
  return lastCmd.command;
}

MovingModuleCommandAttribute MovingModule::getLastMovingModuleCommandAttribute(void) {
  return lastCmd.commandAttribute;
}

MovingModuleDirection MovingModule::getLastMovingModuleDirection(void) {
  return lastCmd.movingDirection;
}

uint16_t MovingModule::getLastPwmValue(void) {
  return lastCmd.pwmValue;
}

MovingModule::~MovingModule(void) {
}

void MovingModule::stopCommand(const MovingModuleCommandAttribute commandAttribute) {
  switch (commandAttribute) {
    case MOVING_MODULE_COMMAND_ATTRIBUTE_ALL:
      if (this->mainMotorLeft != nullptr) {
        this->mainMotorLeft->stop();
      }
      if (this->mainMotorRight != nullptr) {
        this->mainMotorRight->stop();
      }
      break;

    case MOVING_MODULE_COMMAND_ATTRIBUTE_RIGHT:
      if (this->mainMotorRight != nullptr) {
        this->mainMotorRight->stop();
      }
      break;

    case MOVING_MODULE_COMMAND_ATTRIBUTE_LEFT:
      if (this->mainMotorLeft != nullptr) {
        this->mainMotorLeft->stop();
      }
      break;

    case MOVING_MODULE_COMMAND_ATTRIBUTE_NONE:
      break;

    default:
      break;
  }
}

void MovingModule::startCommand(const MovingModuleCommandAttribute commandAttribute) {
}

void MovingModule::moveCommand(const MovingModuleCommandAttribute commandAttribute, const MovingModuleDirection movingDirection, const uint16_t pwmValue) {
  switch (commandAttribute) {
    case MOVING_MODULE_COMMAND_ATTRIBUTE_ALL:
      switch (movingDirection) {
        case MOVING_MODULE_DIRECTION_FORWARD:
          if (this->mainMotorLeft != nullptr) {
            this->mainMotorLeft->goForward(getDutyCyclePercentage(pwmValue));
          }
          if (this->mainMotorRight != nullptr) {
            this->mainMotorRight->goForward(getDutyCyclePercentage(pwmValue));
          }
          break;

        case MOVING_MODULE_DIRECTION_BACK:
          if (this->mainMotorLeft != nullptr) {
            this->mainMotorLeft->goBackward(getDutyCyclePercentage(pwmValue));
          }
          if (this->mainMotorRight != nullptr) {
            this->mainMotorRight->goBackward(getDutyCyclePercentage(pwmValue));
          }
          break;

        case MOVING_MODULE_DIRECTION_AROUND_LF_RB:
          if (this->mainMotorLeft != nullptr) {
            this->mainMotorLeft->goForward(getDutyCyclePercentage(pwmValue));
          }
          if (this->mainMotorRight != nullptr) {
            this->mainMotorRight->goBackward(getDutyCyclePercentage(pwmValue));
          }
          break;

        case MOVING_MODULE_DIRECTION_AROUND_LB_RF:
          if (this->mainMotorLeft != nullptr) {
            this->mainMotorLeft->goBackward(getDutyCyclePercentage(pwmValue));
          }
          if (this->mainMotorRight != nullptr) {
            this->mainMotorRight->goForward(getDutyCyclePercentage(pwmValue));
          }
          break;

        default:
          break;
      }
      break;

    case MOVING_MODULE_COMMAND_ATTRIBUTE_RIGHT:
      switch (movingDirection) {
        case MOVING_MODULE_DIRECTION_FORWARD:
          if (this->mainMotorRight != nullptr) {
            this->mainMotorRight->goForward(getDutyCyclePercentage(pwmValue));
          }
          break;

        case MOVING_MODULE_DIRECTION_BACK:
          if (this->mainMotorRight != nullptr) {
            this->mainMotorRight->goBackward(getDutyCyclePercentage(pwmValue));
          }
          break;

        default:
          break;
      }
      break;

    case MOVING_MODULE_COMMAND_ATTRIBUTE_LEFT:
      switch (movingDirection) {
        case MOVING_MODULE_DIRECTION_FORWARD:
          if (this->mainMotorLeft != nullptr) {
            this->mainMotorLeft->goForward(getDutyCyclePercentage(pwmValue));
          }
          break;

        case MOVING_MODULE_DIRECTION_BACK:
          if (this->mainMotorLeft != nullptr) {
            this->mainMotorLeft->goBackward(getDutyCyclePercentage(pwmValue));
          }
          break;

        default:
          break;
      }
      break;

    default:
      break;
  }
}

void MovingModule::pwmCommand(const MovingModuleCommandAttribute commandAttribute, const uint16_t pwmValue) {
  switch (commandAttribute) {
    case MOVING_MODULE_COMMAND_ATTRIBUTE_ALL:
      if (this->mainMotorLeft != nullptr) {
        this->mainMotorLeft->setDutyCycleForward(getDutyCyclePercentage(pwmValue));
        this->mainMotorLeft->setDutyCycleBackward(getDutyCyclePercentage(pwmValue));
      }
      if (this->mainMotorRight != nullptr) {
        this->mainMotorRight->setDutyCycleForward(getDutyCyclePercentage(pwmValue));
        this->mainMotorRight->setDutyCycleBackward(getDutyCyclePercentage(pwmValue));
      }
      break;

    case MOVING_MODULE_COMMAND_ATTRIBUTE_RIGHT:
      if (this->mainMotorRight != nullptr) {
        this->mainMotorRight->setDutyCycleForward(getDutyCyclePercentage(pwmValue));
        this->mainMotorRight->setDutyCycleBackward(getDutyCyclePercentage(pwmValue));
      }
      break;

    case MOVING_MODULE_COMMAND_ATTRIBUTE_LEFT:
      if (this->mainMotorLeft != nullptr) {
        this->mainMotorLeft->setDutyCycleForward(getDutyCyclePercentage(pwmValue));
        this->mainMotorLeft->setDutyCycleBackward(getDutyCyclePercentage(pwmValue));
      }
      break;

    default:
      break;
  }
}

double MovingModule::getDutyCyclePercentage(const uint16_t pwmValue) {
  /* Resolution 0.001 */
  return pwmValue * 0.001;
}