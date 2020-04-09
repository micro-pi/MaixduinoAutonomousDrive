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

ErrorCode MainMotor::initDevice() {
  ErrorCode errorCode;
  if (this->pwm == 0) {
    errorCode = E_NOK;
  } else {
    pwm_set_frequency(this->pwm, this->frequency);
    pwm_set_enable(this->pwm, this->forwardChannel, false);
    pwm_set_enable(this->pwm, this->backwardChannel, false);
    errorCode = E_OK;
  }

  return errorCode;
}

void MainMotor::goForward(const double dutyCyclePercentage) {
  pwm_set_enable(this->pwm, this->backwardChannel, false);
  pwm_set_active_duty_cycle_percentage(this->pwm, this->forwardChannel, calcDutyCyclePercentage(dutyCyclePercentage));
  pwm_set_enable(this->pwm, this->forwardChannel, true);
}

void MainMotor::goBackward(const double dutyCyclePercentage) {
  pwm_set_enable(this->pwm, this->forwardChannel, false);
  pwm_set_active_duty_cycle_percentage(this->pwm, this->backwardChannel, calcDutyCyclePercentage(dutyCyclePercentage));
  pwm_set_enable(this->pwm, this->backwardChannel, true);
}

void MainMotor::setDutyCycleForward(const double dutyCyclePercentage) {
  pwm_set_active_duty_cycle_percentage(this->pwm, this->forwardChannel, calcDutyCyclePercentage(dutyCyclePercentage));
}

void MainMotor::setDutyCycleBackward(const double dutyCyclePercentage) {
  pwm_set_active_duty_cycle_percentage(this->pwm, this->backwardChannel, calcDutyCyclePercentage(dutyCyclePercentage));
}

void MainMotor::stop() {
  pwm_set_active_duty_cycle_percentage(this->pwm, this->forwardChannel, 0.0);
  pwm_set_enable(this->pwm, this->forwardChannel, false);
  pwm_set_enable(this->pwm, this->backwardChannel, false);
}

double MainMotor::calcDutyCyclePercentage(const double dutyCyclePercentage) {
  if (dutyCyclePercentage < 0.0) {
    return 0.0;
  } else if (dutyCyclePercentage > 1.0) {
    return 1.0;
  }
  return dutyCyclePercentage;
}

MainMotor::~MainMotor() {
}