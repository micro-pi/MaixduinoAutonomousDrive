#include "AutonomusModule.h"

AutonomusModule::AutonomusModule(const char *moduleName) : Module(moduleName) {
  globalData = nullptr;
}

ErrorCode AutonomusModule::initModule(void) {
  return E_OK;
}

void AutonomusModule::mainFunction(void) {}

void AutonomusModule::setGlobalData(GlobalData &globalData) {
  this->globalData = &globalData;
}

AutonomusModule::~AutonomusModule(void) {
  MovingModuleInterface movingModuleInterface;
  SonarsData sonarsData;
  if (globalData != nullptr) {
    movingModuleInterface = globalData->getMovingModuleInterface();
    if ((movingModuleInterface.command == MOVING_MODULE_COMMAND_MOVE) &&
        (movingModuleInterface.commandAttribute = MOVING_MODULE_COMMAND_ATTRIBUTE_ALL)) {
      sonarsData = globalData->getSonarsData();
      switch (movingModuleInterface.movingDirection) {
        case MOVING_MODULE_DIRECTION_FORWARD:
          if ((sonarsData.sonar1 >= 0) && (sonarsData.sonar1 <= 100)) {
            /* TODO: send stop */
          }
          break;

        case MOVING_MODULE_DIRECTION_BACK:
          if ((sonarsData.sonar4 >= 0) && (sonarsData.sonar4 <= 100)) {
            /* TODO: send stop */
          }
          break;

        default:
          break;
      }
    }
  }
}