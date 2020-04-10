#include "CommandModule.h"

CommandModule::CommandModule(const char *moduleName, CircularQueue<MovingModuleInterface> &movingModuleCmds) : Module(moduleName), movingModuleCommands(movingModuleCmds) {
}

ErrorCode CommandModule::initModule(void) {
  ErrorCode errorCode;
  errorCode = E_OK;

  return errorCode;
}

void CommandModule::mainFunction(void) {
  /* TODO:  */
}

CommandModule::~CommandModule(void) {
}