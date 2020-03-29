#ifndef ALL_MODULES_H
#define ALL_MODULES_H

#include "camera/CameraModule.h"
#include "circular_queue/CircularQueue.h"
#include "cmd/CommandModule.h"
#include "moving/MovingModule.h"

/* Modules */
extern CircularQueue<MovingModuleInterface> movingModuleCommands;
extern CommandModule commandModule;
extern MovingModule movingModule;
extern CameraModule cameraModule;

extern Module *MODULES_100MS[];

extern const uint8_t NUM_OF_MODULES_100MS;

#endif