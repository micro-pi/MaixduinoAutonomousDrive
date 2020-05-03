#include "GyroModule.h"
#include <stdlib.h>
#include <syslog.h>

// static const char *TAG = "KECM_GYM";

GyroModule::GyroModule(const char *moduleName) : Module(moduleName) {
  this->itg3200 = nullptr;
  this->globalData = nullptr;
  this->movingModule = nullptr;
  this->movingModuleCommandsQueue = nullptr;

  this->gyroData.absoluteX = 0;
  this->gyroData.absoluteY = 0;
  this->gyroData.absoluteZ = 0;
}

ErrorCode GyroModule::initModule(void) {
  ErrorCode errorCode;
  errorCode = E_OK;

  return errorCode;
}

void GyroModule::setITG3200(ITG3200 &itg3200) {
  this->itg3200 = &itg3200;
}

void GyroModule::setGlobalData(GlobalData &globalData) {
  this->globalData = &globalData;
}

void GyroModule::setMovingModule(MovingModule &movingModule) {
  this->movingModule = &movingModule;
}

void GyroModule::setMovingModuleCommandsQueue(xQueueHandle movingModuleCommandsQueue) {
  this->movingModuleCommandsQueue = movingModuleCommandsQueue;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int32_t adjustAngle(int32_t angle) {
  if (angle >= (180 * 1000000)) {
    angle = (-180 * 1000000) + (angle - (180 * 1000000));
  } else if (angle <= -(180 * 1000000)) {
    angle = (180 * 1000000) + (angle + (180 * 1000000));
  }
  return angle;
}

void GyroModule::mainFunction(void) {
  static int32_t refAbsoluteZ;
  static bool refAbsoluteFlag = false;
  static uint8_t k = 0;
  static uint8_t n = 0;
  GyroData gyroDataCopy;
  int16_t x;
  int16_t y;
  int16_t z;

  if ((movingModuleCommandsQueue != nullptr) && (itg3200 != nullptr) && (itg3200->getErrorCode() == E_OK)) {
    if (itg3200->getInterruptStatus().status.rawDataReady == true) {
      itg3200->getXYZ(x, y, z);
      // LOGI(TAG, "[%05d] [%05d] [%05d]", x, y, z);

      if (k >= 10) {
        /* (14.375 / 0.02) == 718.75 */
        gyroData.absoluteX += (int32_t)((x * 1000000) / (718.75));
        gyroData.absoluteY += (int32_t)((y * 1000000) / (718.75));
        gyroData.absoluteZ += (int32_t)((z * 1000000) / (718.75));
        gyroData.absoluteX = adjustAngle(gyroData.absoluteX);
        gyroData.absoluteY = adjustAngle(gyroData.absoluteY);
        gyroData.absoluteZ = adjustAngle(gyroData.absoluteZ);

        if (globalData != nullptr) {
          gyroDataCopy = gyroData;
          globalData->setGyroData(gyroDataCopy);
        }

        if (movingModule != nullptr) {
          MovingModuleCommands lastMovingModuleCommand = movingModule->getLastMovingModuleCommands();
          MovingModuleCommandAttribute lastMovingModuleCommandAttribute = movingModule->getLastMovingModuleCommandAttribute();
          MovingModuleDirection lastMovingModuleDirection = movingModule->getLastMovingModuleDirection();
          uint16_t lastLastPwmValue = movingModule->getLastPwmValue();

          if ((lastMovingModuleCommand == MOVING_MODULE_COMMAND_MOVE) &&
              (lastMovingModuleCommandAttribute == MOVING_MODULE_COMMAND_ATTRIBUTE_ALL)) {
            if (refAbsoluteFlag == false) {
              refAbsoluteZ = gyroData.absoluteZ;
            }
            int32_t diff = adjustAngle(refAbsoluteZ - gyroData.absoluteZ);
            if (((diff > 0) && (lastMovingModuleDirection == MOVING_MODULE_DIRECTION_FORWARD)) ||
                ((diff < 0) && (lastMovingModuleDirection == MOVING_MODULE_DIRECTION_BACK))) {
              /* If Go right */
              diff = abs(diff);
              if (diff > (90 * 1000000)) {
                diff = (90 * 1000000);
              }
              /* Resolution 0.001 */
              uint16_t rightPwmValue = 0;
              uint16_t leftPwmValue = 0;

              if (lastLastPwmValue < 1000) {
                rightPwmValue = map(diff, 0, 90 * 1000000, 0, 1000 - lastLastPwmValue);
              }
              if (lastLastPwmValue > 0) {
                leftPwmValue = map(diff, 0, 90 * 1000000, 0, lastLastPwmValue);
              }

              movingModule->pwmCommand(MOVING_MODULE_COMMAND_ATTRIBUTE_RIGHT, lastLastPwmValue + rightPwmValue);
              movingModule->pwmCommand(MOVING_MODULE_COMMAND_ATTRIBUTE_LEFT, lastLastPwmValue - leftPwmValue);
            } else if (((diff < 0) && (lastMovingModuleDirection == MOVING_MODULE_DIRECTION_FORWARD)) ||
                       ((diff > 0) && (lastMovingModuleDirection == MOVING_MODULE_DIRECTION_BACK))) {
              /* If Go left */
              /* Resolution 0.001 */
              diff = abs(diff);
              if (diff > (90 * 1000000)) {
                diff = (90 * 1000000);
              }
              uint16_t rightPwmValue = 0;
              uint16_t leftPwmValue = 0;

              if (lastLastPwmValue < 1000) {
                leftPwmValue = map(diff, 0, 90 * 1000000, 0, 1000 - lastLastPwmValue);
              }
              if (lastLastPwmValue > 0) {
                rightPwmValue = map(diff, 0, 90 * 1000000, 0, lastLastPwmValue);
              }

              movingModule->pwmCommand(MOVING_MODULE_COMMAND_ATTRIBUTE_LEFT, lastLastPwmValue + leftPwmValue);
              movingModule->pwmCommand(MOVING_MODULE_COMMAND_ATTRIBUTE_RIGHT, lastLastPwmValue - rightPwmValue);
            } else {
            }

            refAbsoluteFlag = true;
          } else {
            refAbsoluteFlag = false;
          }
        }

        if (n >= 10) {
          n = 0;
          // LOGI(TAG, "[%.4f] [%.4f] [%.4f]", gyroData.absoluteX * 0.000001, gyroData.absoluteY * 0.000001, gyroData.absoluteZ * 0.000001);
        } else {
          n++;
        }
      } else {
        k++;
      }
    } else {
      // LOGI(TAG, "--------------------");
    }
  }
}

GyroModule::~GyroModule() {
}