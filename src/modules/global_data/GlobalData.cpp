#include "GlobalData.h"
#include <syslog.h>

static const char *TAG = "KECM_GDM";

GlobalData::GlobalData(const char *moduleName) : Module(moduleName) {
  sonarsData.sonar1 = -1;
  sonarsData.sonar2 = -1;
  sonarsData.sonar3 = -1;
  sonarsData.sonar4 = -1;
  sonarsData.sonar5 = -1;
  sonarsData.sonar6 = -1;

  gyroData.absoluteX = 0;
  gyroData.absoluteY = 0;
  gyroData.absoluteZ = 0;
}

ErrorCode GlobalData::initModule(void) {
  return E_OK;
}

void GlobalData::mainFunction(void) {
  // LOGI(TAG, "Axe X [%.4f]", (double)gyroData.absoluteX / 1000000);
  // LOGI(TAG, "Axe Y [%.4f]", (double)gyroData.absoluteY / 1000000);
  // LOGI(TAG, "Axe Z [%.4f]", (double)gyroData.absoluteZ / 1000000);
  LOGI(TAG, "Axes: X:[%.4f] Y:[%.4f] Z:[%.4f]", (double)gyroData.absoluteX / 1000000, (double)gyroData.absoluteY / 1000000, (double)gyroData.absoluteZ / 1000000);
  LOGI(TAG, "Distance F: %d mm", sonarsData.sonar1);
  LOGI(TAG, "Distance R: %d mm", sonarsData.sonar2);
  LOGI(TAG, "Distance L: %d mm", sonarsData.sonar3);
  LOGI(TAG, "Distance B: %d mm", sonarsData.sonar4);
}

void GlobalData::setSonarsData(SonarsData &sonarsData) {
  this->sonarsData = sonarsData;
}

void GlobalData::setGyroData(GyroData &gyroData) {
  this->gyroData = gyroData;
}

GlobalData::~GlobalData(void) {
}