#ifndef ALL_MODULES_H
#define ALL_MODULES_H

#include "camera/CameraModule.h"
#include "circular_queue/CircularQueue.h"
#include "cmd/CommandModule.h"
#include "k210_esp32_com/K210ESP32Communication.h"
#include "moving/MovingModule.h"

/* Modules */
extern CircularQueue<MovingModuleInterface> movingModuleCommands;
extern CommandModule commandModule;
extern MovingModule movingModule;
extern CameraModule cameraModule;
extern K210ESP32Communication k210Esp32Communication;

extern Module *MODULES_100MS[];
extern Module *MODULES_1000MS[];

extern const uint8_t NUM_OF_MODULES_100MS;
extern const uint8_t NUM_OF_MODULES_1000MS;

#endif