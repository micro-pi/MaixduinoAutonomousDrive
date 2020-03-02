#ifndef MODULE_H
#define MODULE_H

#include "ModuleTypes.h"

class Module {
public:
  /**
   * @brief Initialisation function
   * @return E_OK if initialization was successful, otherwise returns E_NOK 
   */
  virtual ErrorCode init(void) = 0;
  virtual void mainFunction(void) = 0;
  virtual ~Module(void);
};

#endif
