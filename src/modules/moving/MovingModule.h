#ifndef MOVING_MODULE_H
#define MOVING_MODULE_H

#include "../../devices/main_motor/MainMotor.h"
#include "../Module.h"
#include "../circular_queue/CircularQueue.h"

#include <devices.h>

class MovingModule : public Module {
private:
  MovingModuleInterface lastCmd;
  xQueueHandle movingModuleCommandsQueue;
  MainMotor *mainMotorLeft;
  MainMotor *mainMotorRight;

public:
  /**
   * @brief Default constructor
   */
  MovingModule(const char *moduleName);
  ErrorCode init(void);
  void setMovingModuleCommandsQueue(xQueueHandle movingModuleCommandsQueue);
  void setMainMotorLeft(MainMotor &mainMotorLeft);
  void setMainMotorRight(MainMotor &mainMotorRight);
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

  double getDutyCyclePercentage(const uint16_t pwmValue);
};

#endif
