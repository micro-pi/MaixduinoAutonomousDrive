#ifndef SONARS_H
#define SONARS_H

#include "../Device.h"
#include <osdefs.h>

#define SONARS_ADDRESS ((uint8_t)(0x09u))

#define WHO_AM_I_CMD ((uint8_t)(0x00u))
#define RESET_CMD ((uint8_t)(0x01u))
#define CONFIG_CMD ((uint8_t)(0x02u))
#define STATUS_CMD ((uint8_t)(0x03u))
#define DATA_0_H_CMD ((uint8_t)(0x04u))
#define DATA_0_L_CMD ((uint8_t)(0x05u))
#define DATA_1_H_CMD ((uint8_t)(0x06u))
#define DATA_1_L_CMD ((uint8_t)(0x07u))
#define DATA_2_H_CMD ((uint8_t)(0x08u))
#define DATA_2_L_CMD ((uint8_t)(0x09u))
#define DATA_3_H_CMD ((uint8_t)(0x0Au))
#define DATA_3_L_CMD ((uint8_t)(0x0Bu))
#define DATA_4_H_CMD ((uint8_t)(0x0Cu))
#define DATA_4_L_CMD ((uint8_t)(0x0Du))
#define DATA_5_H_CMD ((uint8_t)(0x0Eu))
#define DATA_5_L_CMD ((uint8_t)(0x0Fu))
#define EMPTY_CMD ((uint8_t)(0xFFu))

#define READY_DATA_BIT ((uint8_t)(0x07u))

class Sonars : public Device {
private:
  uint8_t writeBuffer[12];
  uint8_t readBuffer[12];
  handle_t i2c;
  handle_t device;

public:
  Sonars(const char *deviceName);
  void setI2c(const handle_t i2c);
  uint8_t whoAmI(void);
  void getAllDistances(int16_t &sonar1, int16_t &sonar2, int16_t &sonar3, int16_t &sonar4, int16_t &sonar5, int16_t &sonar6);
  int16_t getDistance(const uint8_t sonarNumber);
  bool isDataReady(void);
  virtual ErrorCode initDevice(void) override;

  virtual ~Sonars();

private:
  int8_t read(uint8_t reg);
  int write(uint8_t reg, uint8_t data);
  int16_t read16(uint8_t reg);
  void readData(void);
};

#endif