#ifndef MOVING_MODULE_H
#define MOVING_MODULE_H

#include "../../devices/main_motor/MainMotor.h"
#include "../../devices/sonars/Sonars.h"
#include "../Module.h"
#include "../circular_queue/CircularQueue.h"

#include <devices.h>

class MovingModule : public Module {
private:
  MovingModuleInterface lastCmd;
  xQueueHandle movingModuleCommandsQueue;
  MainMotor *mainMotorLeft;
  MainMotor *mainMotorRight;
  Sonars *sonars;

public:
  /**
   * @brief Default constructor
   */
  MovingModule(const char *moduleName);
  ErrorCode initModule(void);
  void setMovingModuleCommandsQueue(xQueueHandle movingModuleCommandsQueue);
  void setMainMotorLeft(MainMotor &mainMotorLeft);
  void setMainMotorRight(MainMotor &mainMotorRight);
  void setSonars(Sonars &sonars);
  void mainFunction(void);

  MovingModuleCommands getLastMovingModuleCommands(void);
  MovingModuleCommandAttribute getLastMovingModuleCommandAttribute(void);
  MovingModuleDirection getLastMovingModuleDirection(void);
  uint16_t getLastPwmValue(void);

  /**
   * @brief Destructor
   */
  virtual ~MovingModule(void);

  void pwmCommand(const MovingModuleCommandAttribute commandAttribute, const uint16_t pwmValue);

private:
  void stopCommand(const MovingModuleCommandAttribute commandAttribute);
  void startCommand(const MovingModuleCommandAttribute commandAttribute);
  void moveCommand(const MovingModuleCommandAttribute commandAttribute, const MovingModuleDirection movingDirection, const uint16_t pwmValue);

  double getDutyCyclePercentage(const uint16_t pwmValue);
};

#endif
