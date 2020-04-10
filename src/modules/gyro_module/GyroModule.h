#ifndef GYRO_MODULE_H
#define GYRO_MODULE_H

#include "../../devices/itg3200/ITG3200.h"
#include "../Module.h"

#include <devices.h>

class GyroModule : public Module {
private:
  ITG3200 *itg3200;
  xQueueHandle movingModuleCommandsQueue;

public:
  /**
   * @brief Default constructor
   */
  GyroModule(const char *moduleName);
  ErrorCode initModule(void);
  void setITG3200(ITG3200 &itg3200);
  void setMovingModuleCommandsQueue(xQueueHandle movingModuleCommandsQueue);
  void mainFunction(void);
  /**
   * @brief Destructor
   */
  virtual ~GyroModule();
};

#endif
