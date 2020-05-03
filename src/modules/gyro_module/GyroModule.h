#ifndef GYRO_MODULE_H
#define GYRO_MODULE_H

#include "../../devices/itg3200/ITG3200.h"
#include "../Module.h"
#include "../global_data/GlobalData.h"
#include "../moving/MovingModule.h"

#include <devices.h>

class GyroModule : public Module {
private:
  ITG3200 *itg3200;
  GlobalData *globalData;
  MovingModule *movingModule;
  xQueueHandle movingModuleCommandsQueue;

  GyroData gyroData;

public:
  /**
   * @brief Default constructor
   */
  GyroModule(const char *moduleName);
  ErrorCode initModule(void);
  void setITG3200(ITG3200 &itg3200);
  void setGlobalData(GlobalData &globalData);
  void setMovingModule(MovingModule &movingModule);
  void setMovingModuleCommandsQueue(xQueueHandle movingModuleCommandsQueue);
  void mainFunction(void);
  /**
   * @brief Destructor
   */
  virtual ~GyroModule();
};

#endif
