#include "AllModules.h"

/* Modules */
CircularQueue<MovingModuleInterface> movingModuleCommands(10);

CommandModule commandModule("Command Module", movingModuleCommands);
MovingModule movingModule("Moving Module");
CameraModule cameraModule("Camera Module");
K210ESP32Communication k210Esp32Communication("K210/ESP32 Communication");

Module *MODULES_100MS[] = {
    &commandModule,
    &movingModule,
    &cameraModule,
};

Module *MODULES_1000MS[] = {
    &k210Esp32Communication,
};

const uint8_t NUM_OF_MODULES_100MS = ((uint8_t)(sizeof(MODULES_100MS) / sizeof(Module *)));
const uint8_t NUM_OF_MODULES_1000MS = ((uint8_t)(sizeof(MODULES_1000MS) / sizeof(Module *)));