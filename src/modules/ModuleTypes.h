#ifndef MODULE_TYPES_H
#define MODULE_TYPES_H

#include <stdint.h>

enum ErrorCode {
  E_OK,
  E_NOK
};

/**
 * Moving Module Commands
 */
enum MovingModuleCommands {
  /**
   * Stop command
   */
  MOVING_MODULE_COMMAND_STOP = (0u),
  /**
   * Start command
   */
  MOVING_MODULE_COMMAND_START = (1u),
  /**
   * Move command
   */
  MOVING_MODULE_COMMAND_MOVE = (2u),
  /**
   * PWM command
   */
  MOVING_MODULE_COMMAND_PWM = (3u),
  /**
   * None
   */
  MOVING_MODULE_COMMAND_NONE
};

enum MovingModuleCommandAttribute {
  /**
   * All
   */
  MOVING_MODULE_COMMAND_ATTRIBUTE_ALL = (0u),
  /**
   * Right
   */
  MOVING_MODULE_COMMAND_ATTRIBUTE_RIGHT = (1u),
  /**
   * Left
   */
  MOVING_MODULE_COMMAND_ATTRIBUTE_LEFT = (2u),
  /**
   * None
   */
  MOVING_MODULE_COMMAND_ATTRIBUTE_NONE
};

enum MovingModuleDirection {
  /**
   * Forward command
   */
  MOVING_MODULE_DIRECTION_FORWARD = (0u),
  /**
   * Back command
   */
  MOVING_MODULE_DIRECTION_BACK = (1u),
  /**
   * Around command
   */
  MOVING_MODULE_DIRECTION_AROUND = (2u),
  /**
   * None
   */
  MOVING_MODULE_DIRECTION_NONE
};

struct MovingModuleInterface {
  MovingModuleCommands command;
  MovingModuleCommandAttribute commandAttribute;
  MovingModuleDirection movingDirection;
  uint16_t pwmValue;
};

#endif
