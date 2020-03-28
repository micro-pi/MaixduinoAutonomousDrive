#ifndef MOVING_MODULE_H
#define MOVING_MODULE_H

#include "../../devices/main_motor/MainMotor.h"
#include "../Module.h"
#include "../circular_queue/CircularQueue.h"

#include <devices.h>

class MovingModule : public Module {
private:
  CircularQueue<MovingModuleInterface> &movingModuleCommands;
  MainMotor &mainMotorLeft;
  MainMotor &mainMotorRight;

public:
  /**
   * @brief Default constructor
   */
  MovingModule(const char *moduleName, CircularQueue<MovingModuleInterface> &movingModuleCmds, MainMotor &mainMotorLeft, MainMotor &mainMotorRight);
  ErrorCode init(void);
  void mainFunction(void);
  /**
   * @brief Destructor
   */
  virtual ~MovingModule(void);

private:
  void stopCommand(const MovingModuleCommandAttribute commandAttribute);
  void startCommand(const MovingModuleCommandAttribute commandAttribute);
  void moveCommand(const MovingModuleCommandAttribute commandAttribute, const MovingModuleDirection movingDirection, const uint16_t pwmValue);
  void pwmCommand(const MovingModuleCommandAttribute commandAttribute, const uint16_t pwmValue);
};

#endif
