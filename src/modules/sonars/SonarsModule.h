#ifndef SONARS_MODULE_H
#define SONARS_MODULE_H

#include "../../devices/sonars/Sonars.h"
#include "../Module.h"
#include "../global_data/GlobalData.h"

class SonarsModule : public Module {
private:
  GlobalData *globalData;
  Sonars *sonars;

public:
  /**
   * @brief Default constructor
   */
  SonarsModule(const char *moduleName);
  ErrorCode initModule(void);
  void setGlobalData(GlobalData &globalData);
  void setSonars(Sonars &sonars);
  void mainFunction(void);
  ~SonarsModule(void);
};

#endif