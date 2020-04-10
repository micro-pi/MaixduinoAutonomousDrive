#ifndef ALL_DEVICES_H
#define ALL_DEVICES_H

#include "esp32/ESP32.h"
#include "itg3200/ITG3200.h"
#include "led/Led.h"
#include "main_motor/MainMotor.h"

extern Led powerLed;
extern ESP32 esp32;
extern ITG3200 itg3200;
extern MainMotor mainMotorLeft;
extern MainMotor mainMotorRight;

extern Device *DEVICES[];

extern const uint8_t NUM_OF_DEVICES;

#endif