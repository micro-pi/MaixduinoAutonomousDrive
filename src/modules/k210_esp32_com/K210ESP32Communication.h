#ifndef K210_ESP32_COMMUNICATION_H
#define K210_ESP32_COMMUNICATION_H

#include "../Module.h"
#include "../circular_queue/CircularQueue.h"

#include <devices.h>

class K210ESP32Communication : public Module {
private:
  CircularQueue<MovingModuleInterface> &movingModuleCommands;

public:
  /**
   * @brief Default constructor
   */
  K210ESP32Communication(const char *moduleName, CircularQueue<MovingModuleInterface> &movingModuleCmds);
  ErrorCode init(void);
  void mainFunction(void);
  /**
   * @brief Destructor
   */
  virtual ~K210ESP32Communication(void);
};

#endif
