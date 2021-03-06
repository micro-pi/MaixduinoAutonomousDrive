#ifndef CAMERA_MODULE_H
#define CAMERA_MODULE_H

#include "../Module.h"
#include "../circular_queue/CircularQueue.h"

#include <devices.h>

class CameraModule : public Module {
public:
  /**
   * @brief Default constructor
   */
  CameraModule(const char *moduleName);
  ErrorCode initModule(void);
  void mainFunction(void);
  /**
   * @brief Destructor
   */
  virtual ~CameraModule(void);
};

#endif
