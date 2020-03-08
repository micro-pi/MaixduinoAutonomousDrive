#ifndef COMMAND_MODULE_H
#define COMMAND_MODULE_H

#include "../Module.h"
#include "../circular_queue/CircularQueue.h"

class CommandModule : public Module {
private:
  CircularQueue<MovingModuleInterface> &movingModuleCommands;

public:
  /**
   * @brief Default constructor
   */
  CommandModule(const char *moduleName, CircularQueue<MovingModuleInterface> &movingModuleCmds);
  ErrorCode init(void);
  void mainFunction(void);
  ~CommandModule(void);
};

#endif