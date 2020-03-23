#include "MainMotor.h"
MainMotor::MainMotor(const char *deviceName) : Device(deviceName) {
  this->pwm = 0;
  this->frequency = 1000;
  this->forwardChannel = 0;
  this->backwardChannel = 0;
}

void MainMotor::setPwm(const handle_t pwm) {
  this->pwm = pwm;
}

void MainMotor::setFrequency(const double frequency) {
  this->frequency = frequency;
}

void MainMotor::setForwardChannel(const uint32_t forwardChannel) {
  this->forwardChannel = forwardChannel;
}

void MainMotor::setBackwardChannel(const uint32_t backwardChannel) {
  this->backwardChannel = backwardChannel;
}

void MainMotor::begin() {
  // ErrorCode errorCode;
  if (this->pwm == 0) {
    // errorCode = E_NOK;
  } else {
    pwm_set_frequency(this->pwm, this->frequency);
    pwm_set_enable(this->pwm, this->forwardChannel, false);
    pwm_set_enable(this->pwm, this->backwardChannel, false);
    // errorCode = E_OK;
  }

  // return errorCode;
}

MainMotor::~MainMotor() {
}