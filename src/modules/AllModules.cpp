#include "AllModules.h"

/* Modules */
CircularQueue<MovingModuleInterface> movingModuleCommands(10);

CommandModule commandModule("Command Module", movingModuleCommands);
MovingModule movingModule("Moving Module");
CameraModule cameraModule("Camera Module");

Module *MODULES_100MS[] = {
    &commandModule,
    &movingModule,
    &cameraModule,
};

const uint8_t NUM_OF_MODULES_100MS = ((uint8_t)(sizeof(MODULES_100MS) / sizeof(Module *)));