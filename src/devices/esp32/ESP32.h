#ifndef ESP32_H
#define ESP32_H

#include "../../common/common.h"
#include "../Device.h"

#include <osdefs.h>

class ESP32 : public Device {
private:
  handle_t spi;
  spi_mode_t mode;
  double clockRate;
  handle_t device;

public:
  ESP32(const char *deviceName);
  void setSpi(const handle_t spi);
  void setMode(const spi_mode_t mode);
  void setClockRate(const double clockRate);
  void begin(void);
  int transferFullDuplex(const K210ESP32Data *spi0Esp32TxBuffer, K210ESP32Data *spi0Esp32RxBuffer);
  virtual ~ESP32(void);
};

#endif