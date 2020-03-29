#ifndef K210_ESP32_COMMUNICATION_H
#define K210_ESP32_COMMUNICATION_H

#include "../../devices/esp32/ESP32.h"
#include "../Module.h"
#include "../circular_queue/CircularQueue.h"

#include <devices.h>

class K210ESP32Communication : public Module {
private:
  xQueueHandle movingModuleCommandsQueue;
  MovingModuleInterface movingModuleInterface;
  K210ESP32Data spi0Esp32TxBuffer;
  K210ESP32Data spi0Esp32RxBuffer;
  ESP32 *esp32;

public:
  /**
   * @brief Default constructor
   */
  K210ESP32Communication(const char *moduleName);
  ErrorCode init(void);
  void setMovingModuleCommandsQueue(xQueueHandle movingModuleCommandsQueue);
  void setEsp32Device(ESP32 &esp32);
  void mainFunction(void);
  /**
   * @brief Destructor
   */
  virtual ~K210ESP32Communication(void);
};

#endif
