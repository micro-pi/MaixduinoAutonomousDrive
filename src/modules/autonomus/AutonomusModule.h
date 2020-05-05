#ifndef AUTONOMUS_MODULE_H
#define AUTONOMUS_MODULE_H

#include "../Module.h"
#include "../global_data/GlobalData.h"

class AutonomusModule : public Module {
private:
  GlobalData *globalData;

public:
  AutonomusModule(const char *moduleName);
  ErrorCode initModule(void);
  void mainFunction(void);
  void setGlobalData(GlobalData &globalData);
  virtual ~AutonomusModule(void);
};

#endif
