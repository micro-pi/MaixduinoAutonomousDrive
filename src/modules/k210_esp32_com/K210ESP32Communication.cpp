#include "K210ESP32Communication.h"

K210ESP32Communication::K210ESP32Communication(const char *moduleName, CircularQueue<MovingModuleInterface> &movingModuleCmds) : Module(moduleName), movingModuleCommands(movingModuleCmds) {
}

ErrorCode K210ESP32Communication::init(void) {
  ErrorCode errorCode;
  errorCode = E_OK;

  return errorCode;
}

void K210ESP32Communication::mainFunction(void) {
  /* TODO:  */
}

K210ESP32Communication::~K210ESP32Communication(void) {
}