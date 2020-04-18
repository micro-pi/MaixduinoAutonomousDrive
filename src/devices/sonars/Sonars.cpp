#include "Sonars.h"
#include <devices.h>

Sonars::Sonars(const char *deviceName) : Device(deviceName) {
  this->i2c = 0;
}

void Sonars::setI2c(const handle_t i2c) {
  this->i2c = i2c;
}

/**
 * @brief Initialization for Sonars.
 */
ErrorCode Sonars::initDevice() {
  // uint32_t ctx;
  ErrorCode errorCode;
  // int bytes;
  // uint8_t data;

  if (this->i2c > 0) {
    this->device = i2c_get_device(this->i2c, SONARS_ADDRESS, 7);
    i2c_dev_set_clock_rate(this->device, 400000);

    //   ctx = 0;
    //   do {
    //     /* read first byte */
    //     bytes = io_read(this->device, &data, 1);
    //     if ((bytes <= 0) || (data != SONARS_ADDRESS)) {
    //       errorCode = E_NOK;
    //       vTaskDelay(1);
    //     } else {
    errorCode = E_OK;
    //       break;
    //     }
    //     ctx++;
    //   } while ((ctx <= 20) && (errorCode == E_NOK));
  } else {
    errorCode = E_NOK;
  }
  return errorCode;
}

/**
 * @brief Read a byte with the register address of Sonars.
 * @param[in] reg The register address of Sonars to read
 * @return The byte that is read from the register
 */
int8_t Sonars::read(uint8_t reg) {
  int8_t data;
  io_write(this->device, &reg, 1);
  io_read(this->device, (uint8_t *)&data, 1);
  return data;
}

/**
 * @brief Write a byte to the register of the MMA7660
 * @param[in] reg The register address of Sonars to write
 * @param[in] data The data to write
 * @return len Success, other Fail
 */
int Sonars::write(uint8_t reg, uint8_t data) {
  this->writeBuffer[0] = reg;
  this->writeBuffer[1] = data;
  return io_write(this->device, this->writeBuffer, 2);
}

/**
 * @brief Read a word with the register address of Sonars.
 * @param[in] reg The register address of Sonars to read
 * @return The byte that is read from the register
 */
int16_t Sonars::read16(uint8_t reg) {
  io_write(this->device, &reg, 1);
  io_read(this->device, readBuffer, 2);
  return (int16_t)((readBuffer[0] << 8) | (readBuffer[1]));
}

void Sonars::readData(void) {
  writeBuffer[0] = DATA_0_H_CMD;
  io_write(this->device, writeBuffer, 1);
  io_read(this->device, readBuffer, 12);
}

uint8_t Sonars::whoAmI(void) {
  return this->read(WHO_AM_I_CMD);
}

void Sonars::getAllDistances(int16_t &sonar1, int16_t &sonar2, int16_t &sonar3, int16_t &sonar4, int16_t &sonar5, int16_t &sonar6) {
  /* Read 12 bytes in readBuffer */
  readData();
  sonar1 = ((int16_t)((readBuffer[0x00] << 8) | (readBuffer[0x01])));
  sonar2 = ((int16_t)((readBuffer[0x02] << 8) | (readBuffer[0x03])));
  sonar3 = ((int16_t)((readBuffer[0x04] << 8) | (readBuffer[0x05])));
  sonar4 = ((int16_t)((readBuffer[0x06] << 8) | (readBuffer[0x07])));
  sonar5 = ((int16_t)((readBuffer[0x08] << 8) | (readBuffer[0x09])));
  sonar6 = ((int16_t)((readBuffer[0x0A] << 8) | (readBuffer[0x0B])));
}
/**
 * @param sonarNumber Sonar number from 0 to 5
 */
int16_t Sonars::getDistance(const uint8_t sonarNumber) {
  if (sonarNumber < 6) {
    return read16(DATA_0_H_CMD + (sonarNumber * 2));
  } else {
    return -3;
  }
}

bool Sonars::isDataReady(void) {
  return (this->read(STATUS_CMD) & READY_DATA_BIT) == true;
}

Sonars::~Sonars() {
}