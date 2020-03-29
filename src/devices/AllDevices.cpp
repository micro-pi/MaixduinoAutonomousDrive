#include "AllDevices.h"

/* Devices */
Led powerLed("Power LED");
ESP32 esp32("ESP32");
ITG3200 gyro("ITG3205");
MainMotor mainMotorLeft("Left Main Motor");
MainMotor mainMotorRight("Right Main Motor");

Device *DEVICES[] = {
    &powerLed,
    &esp32,
    &gyro,
    &mainMotorLeft,
    &mainMotorRight,
};

const uint8_t NUM_OF_DEVICES = ((uint8_t)(sizeof(DEVICES) / sizeof(Device *)));