#ifndef MOVING_MODULE_H
#define MOVING_MODULE_H

#include "../Module.h"
#include "../circular_queue/CircularQueue.h"

#include <devices.h>

class MovingModule : public Module {
private:
  handle_t pwm;
  double frequency;
  uint32_t leftChannelF;
  uint32_t leftChannelB;
  uint32_t rightChannelF;
  uint32_t rightChannelB;

private:
  CircularQueue<MovingModuleInterface> &movingModuleCommands;

public:
  /**
   * @brief Default constructor
   */
  MovingModule(CircularQueue<MovingModuleInterface> &movingModuleCmds, const double frequency, const uint32_t leftChannelF, const uint32_t leftChannelB, const uint32_t rightChannelF, const uint32_t rightChannelB);
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
