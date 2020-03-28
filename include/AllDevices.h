#ifndef ALL_DEVICES_H
#define ALL_DEVICES_H

#include "devices/esp32/ESP32.h"
#include "devices/itg3200/ITG3200.h"
#include "devices/led/Led.h"
#include "devices/main_motor/MainMotor.h"

extern Led powerLed;
extern ESP32 esp32;
extern ITG3200 gyro;
extern MainMotor mainMotorLeft;
extern MainMotor mainMotorRight;

#endif