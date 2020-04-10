#include "K210ESP32Communication.h"
#include <string.h>
#include <syslog.h>

static const char *TAG = "KECM_K210";

K210ESP32Communication::K210ESP32Communication(const char *moduleName) : Module(moduleName) {
  this->movingModuleCommandsQueue = nullptr;
  this->esp32 = nullptr;
}

ErrorCode K210ESP32Communication::initModule(void) {
  ErrorCode errorCode;
  errorCode = E_OK;

  return errorCode;
}

void K210ESP32Communication::setMovingModuleCommandsQueue(xQueueHandle movingModuleCommandsQueue) {
  this->movingModuleCommandsQueue = movingModuleCommandsQueue;
}

void K210ESP32Communication::setEsp32Device(ESP32 &esp32) {
  this->esp32 = &esp32;
}

void K210ESP32Communication::mainFunction(void) {
  portBASE_TYPE xStatus;
  int rxBytes;
  uint16_t crc;

  if (esp32 != nullptr) {
    memset(spi0Esp32TxBuffer.data, 0, sizeof(spi0Esp32TxBuffer.data));
    spi0Esp32TxBuffer.type = EMPTY;
    spi0Esp32TxBuffer.id = (uint8_t)2;
    spi0Esp32TxBuffer.size = 0;

    rxBytes = esp32->transferFullDuplex(spi0Esp32TxBuffer, spi0Esp32RxBuffer);
    if (rxBytes > 0) {
      crc = k210Esp32DataCrc16(spi0Esp32RxBuffer);
      if (spi0Esp32RxBuffer.crc == crc) {
        switch (spi0Esp32RxBuffer.type) {
          case EMPTY:
            break;

          case STRING:
            /* Used for tests */
            // LOGI(TAG, "Rx.id  : %d ", spi0Esp32RxBuffer.id);
            // LOGI(TAG, "Rx.type: %d ", spi0Esp32RxBuffer.type);
            // LOGI(TAG, "Rx.size: %d ", spi0Esp32RxBuffer.size);
            // LOGI(TAG, "Rx.data: %s ", (char *)spi0Esp32RxBuffer.data);
            // LOGI(TAG, "Rx.crc : %04X ", spi0Esp32RxBuffer.crc);
            // LOGI(TAG, "   crc : %04X ", crc);
            break;

          case MOVING_CMD:
            if (movingModuleCommandsQueue != nullptr) {
              /* Get CMD from data array */
              memcpy(&movingModuleInterface, spi0Esp32RxBuffer.data, sizeof(MovingModuleInterface));
              /* Add CMD to xQueue */
              xStatus = xQueueSendToBack(movingModuleCommandsQueue, (void *)&movingModuleInterface, 0);
              /* Print warning message in case if the xQueue is full */
              if (xStatus == pdFAIL) {
                LOGW(TAG, "Could not send to the CMD queue.");
              }
            }
            break;

          case BYTES:
            /* code */
            break;

          default:
            LOGW(TAG, "Unknown type '%d'", spi0Esp32RxBuffer.type);
            break;
        }
      } else {
        LOGW(TAG, "CRC ERR: RX(%d) != CRC(%d)", spi0Esp32RxBuffer.crc, crc);
      }
    }
  }
}

K210ESP32Communication::~K210ESP32Communication(void) {
}