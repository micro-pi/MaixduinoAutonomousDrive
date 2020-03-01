#ifndef MOVING_MODULE_H
#define MOVING_MODULE_H

#include "../Module.h"

#include <devices.h>

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

class MovingModule : public Module {
private:
  handle_t pwm0;
  double frequency;
  uint32_t leftPinF;
  uint32_t leftPinB;
  uint32_t rightPinF;
  uint32_t rightPinB;

public:
  /**
   * @brief Default constructor
   */
  MovingModule(const double frequency, const uint32_t leftPinF, const uint32_t leftPinB, const uint32_t rightPinF, const uint32_t rightPinB);
  ErrorCode init(void);
  void mainFunction(void);
  /**
   * @brief Destructor
   */
  ~MovingModule(void);

private:
  void stopCommand(const MovingModuleCommandAttribute commandAttribute);
  void startCommand(const MovingModuleCommandAttribute commandAttribute);
  void moveCommand(const MovingModuleCommandAttribute commandAttribute, const MovingModuleDirection movingDirection, const uint16_t pwmValue);
  void pwmCommand(const MovingModuleCommandAttribute commandAttribute, const uint16_t pwmValue);
};

#endif
