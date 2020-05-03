#include "SonarsModule.h"
#include <syslog.h>

// static const char *TAG = "KSM_GYM";

SonarsModule::SonarsModule(const char *moduleName) : Module(moduleName) {
  this->globalData = nullptr;
  this->sonars = nullptr;
}

ErrorCode SonarsModule::initModule(void) {
  return E_OK;
}

void SonarsModule::setGlobalData(GlobalData &globalData) {
  this->globalData = &globalData;
}

void SonarsModule::setSonars(Sonars &sonars) {
  this->sonars = &sonars;
}

void SonarsModule::mainFunction(void) {
  static uint16_t initCounter = 0;
  // static uint16_t logCounter = 0;
  SonarsData sonarsData = {0, 0, 0, 0, 0, 0};
  if (initCounter < 150) {
    if ((this->globalData != nullptr) && (this->sonars != nullptr) && (this->sonars->getErrorCode() == E_OK)) {
      sonars->getAllDistances(sonarsData.sonar1, sonarsData.sonar2, sonarsData.sonar3, sonarsData.sonar4, sonarsData.sonar5, sonarsData.sonar6);
      globalData->setSonarsData(sonarsData);
      // if (logCounter % 50 == 0) {
      // LOGI(TAG, "Distances : %d, %d, %d, %d", sonarsData.sonar1, sonarsData.sonar2, sonarsData.sonar3, sonarsData.sonar4);
      // }
    }
  } else {
    initCounter++;
  }
  // logCounter++;
}

SonarsModule::~SonarsModule(void) {
}