#include "GlobalData.h"

GlobalData::GlobalData(const char *moduleName) : Module(moduleName) {
  sonarsData.sonar1 = -1;
  sonarsData.sonar2 = -1;
  sonarsData.sonar3 = -1;
  sonarsData.sonar4 = -1;
  sonarsData.sonar5 = -1;
  sonarsData.sonar6 = -1;
}

ErrorCode GlobalData::initModule(void) {
  return E_OK;
}

void GlobalData::mainFunction(void) {
}

void GlobalData::setSonarsData(SonarsData &sonarsData) {
  this->sonarsData = sonarsData;
}

GlobalData::~GlobalData(void) {
}