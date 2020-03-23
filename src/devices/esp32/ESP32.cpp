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

void ESP32::begin() {
  if (this->spi > 0) {
    this->device = spi_get_device(this->spi, this->mode, SPI_FF_STANDARD, 1, 8);
    spi_dev_set_clock_rate(this->device, this->clockRate);
  }
}

int ESP32::transferFullDuplex(const K210ESP32Data *spi0Esp32TxBuffer, K210ESP32Data *spi0Esp32RxBuffer) {
  if (spi0Esp32TxBuffer != nullptr && spi0Esp32RxBuffer != nullptr) {
    /* TODO: Add CRC16 calculation and check */
    return spi_dev_transfer_full_duplex(this->device, (uint8_t *)spi0Esp32TxBuffer, sizeof(K210ESP32Data), (uint8_t *)spi0Esp32RxBuffer, sizeof(K210ESP32Data));
  }
  return -1;
}

ESP32::~ESP32() {
}