#ifndef MOVING_MODULE_H
#define MOVING_MODULE_H

#include "../Module.h"
#include "../circular_queue/CircularQueue.h"

#include <devices.h>

class MovingModule : public Module {
private:
  handle_t pwm0;
  double frequency;
  uint32_t leftPinF;
  uint32_t leftPinB;
  uint32_t rightPinF;
  uint32_t rightPinB;

private:
  CircularQueue<MovingModuleInterface> &movingModuleCommands;

public:
  /**
   * @brief Default constructor
   */
  MovingModule(CircularQueue<MovingModuleInterface> &movingModuleCmds, const double frequency, const uint32_t leftPinF, const uint32_t leftPinB, const uint32_t rightPinF, const uint32_t rightPinB);
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
