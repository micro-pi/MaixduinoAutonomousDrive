#include "CommandModule.h"

CommandModule::CommandModule(CircularQueue<MovingModuleInterface> &movingModuleCmds) : movingModuleCommands(movingModuleCmds) {
}

ErrorCode CommandModule::init(void) {
  ErrorCode errorCode;
  errorCode = E_OK;

  return errorCode;
}

void CommandModule::mainFunction(void) {
  /* TODO:  */
}

CommandModule::~CommandModule(void) {
}