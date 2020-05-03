#ifndef ALL_MODULES_H
#define ALL_MODULES_H

#include "camera/CameraModule.h"
#include "circular_queue/CircularQueue.h"
#include "cmd/CommandModule.h"
#include "global_data/GlobalData.h"
#include "gyro_module/GyroModule.h"
#include "k210_esp32_com/K210ESP32Communication.h"
#include "moving/MovingModule.h"
#include "sonars/SonarsModule.h"

/* Modules */
extern GlobalData globalData;
extern CircularQueue<MovingModuleInterface> movingModuleCommands;
extern CommandModule commandModule;
extern MovingModule movingModule;
extern CameraModule cameraModule;
extern K210ESP32Communication k210Esp32Communication;
extern GyroModule gyroModule;
extern SonarsModule sonarsModule;

extern Module *MODULES_10MS[];
extern Module *MODULES_10MS2[];
extern Module *MODULES_20MS[];
extern Module *MODULES_100MS[];
extern Module *MODULES_1000MS[];

extern const uint8_t NUM_OF_MODULES_10MS;
extern const uint8_t NUM_OF_MODULES_10MS2;
extern const uint8_t NUM_OF_MODULES_20MS;
extern const uint8_t NUM_OF_MODULES_100MS;
extern const uint8_t NUM_OF_MODULES_1000MS;

#endif