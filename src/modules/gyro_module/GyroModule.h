#ifndef GYRO_MODULE_H
#define GYRO_MODULE_H

#include "../../devices/itg3200/ITG3200.h"
#include "../Module.h"
#include "../moving/MovingModule.h"

#include <devices.h>

class GyroModule : public Module {
private:
  ITG3200 *itg3200;
  MovingModule *movingModule;
  xQueueHandle movingModuleCommandsQueue;
  int16_t x;
  int16_t y;
  int16_t z;

  int32_t absoluteX;
  int32_t absoluteY;
  int32_t absoluteZ;

public:
  /**
   * @brief Default constructor
   */
  GyroModule(const char *moduleName);
  ErrorCode initModule(void);
  void setITG3200(ITG3200 &itg3200);
  void setMovingModule(MovingModule &movingModule);
  void setMovingModuleCommandsQueue(xQueueHandle movingModuleCommandsQueue);
  void mainFunction(void);
  /**
   * @brief Destructor
   */
  virtual ~GyroModule();
};

#endif
