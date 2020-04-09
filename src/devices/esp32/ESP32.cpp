#include "ESP32.h"

#include <devices.h>

ESP32::ESP32(const char *deviceName) : Device(deviceName) {
  this->spi = 0;
  this->mode = SPI_MODE_0;
  this->clockRate = 8000000;
}

void ESP32::setSpi(const handle_t spi) {
  this->spi = spi;
}

void ESP32::setMode(const spi_mode_t mode) {
  this->mode = mode;
}

void ESP32::setClockRate(const double clockRate) {
  this->clockRate = clockRate;
}

ErrorCode ESP32::initDevice() {
  ErrorCode errorCode;
  if (this->spi > 0) {
    this->device = spi_get_device(this->spi, this->mode, SPI_FF_STANDARD, 1, 8); /* TODO: 1<<SPI_SLAVE_SELECT instead of 1 */
    spi_dev_set_clock_rate(this->device, this->clockRate);
    errorCode = E_OK;
  } else {
    errorCode = E_NOK;
  }
  return errorCode;
}

int ESP32::transferFullDuplex(K210ESP32Data &spi0Esp32TxBuffer, K210ESP32Data &spi0Esp32RxBuffer) {
  spi0Esp32TxBuffer.crc = k210Esp32DataCrc16(spi0Esp32TxBuffer);
  return spi_dev_transfer_full_duplex(this->device, (uint8_t *)&spi0Esp32TxBuffer, sizeof(K210ESP32Data), (uint8_t *)&spi0Esp32RxBuffer, sizeof(K210ESP32Data));
}

ESP32::~ESP32() {
}