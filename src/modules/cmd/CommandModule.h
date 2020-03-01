#ifndef COMMAND_MODULE_H
#define COMMAND_MODULE_H

#include "../Module.h"

class CommandModule : public Module {
public:
  /**
   * @brief Default constructor
   */
  CommandModule(void);
  ErrorCode init(void);
  void mainFunction(void);
  ~CommandModule(void);
};

#endif