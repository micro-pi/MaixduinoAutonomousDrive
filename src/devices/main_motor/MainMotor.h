#ifndef MAIN_MOTOR_H
#define MAIN_MOTOR_H

#include "../../common/common.h"
#include "../Device.h"

#include <devices.h>

class MainMotor : public Device {
private:
  handle_t pwm;
  double frequency;
  uint32_t forwardChannel;
  uint32_t backwardChannel;

public:
  MainMotor(const char *deviceName);
  void setPwm(const handle_t pwm);
  void setFrequency(const double frequency);
  void setForwardChannel(const uint32_t forwardChannel);
  void setBackwardChannel(const uint32_t backwardChannel);
  void begin(void);
  virtual ~MainMotor(void);
};

#endif