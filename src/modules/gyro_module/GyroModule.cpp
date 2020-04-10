#include "GyroModule.h"
#include <syslog.h>

static const char *TAG = "KECM_GYM";

GyroModule::GyroModule(const char *moduleName) : Module(moduleName) {
  this->itg3200 = nullptr;
  this->movingModuleCommandsQueue = nullptr;
}

ErrorCode GyroModule::initModule(void) {
  ErrorCode errorCode;
  errorCode = E_OK;

  return errorCode;
}

void GyroModule::setITG3200(ITG3200 &itg3200) {
  this->itg3200 = &itg3200;
}

void GyroModule::setMovingModuleCommandsQueue(xQueueHandle movingModuleCommandsQueue) {
  this->movingModuleCommandsQueue = movingModuleCommandsQueue;
}

void GyroModule::mainFunction(void) {
}

GyroModule::~GyroModule() {
}