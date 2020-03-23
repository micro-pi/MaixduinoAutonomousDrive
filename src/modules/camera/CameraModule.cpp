#include "CameraModule.h"

CameraModule::CameraModule(const char *moduleName) : Module(moduleName) {
}

ErrorCode CameraModule::init(void) {

  return E_OK;
}

void CameraModule::mainFunction(void) {
}

CameraModule::~CameraModule(void) {
}