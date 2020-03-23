#include "common.h"

/***** crc16.c *****/

uint16_t crc16(uint16_t crcValue, uint8_t newByte) {
  uint8_t i;
  for (i = 0; i < 8; i++) {
    if (((crcValue & 0x8000) >> 8) ^ (newByte & 0x80)) {
      crcValue = (crcValue << 1) ^ POLYNOM;
    } else {
      crcValue = (crcValue << 1);
    }
    newByte <<= 1;
  }
  return crcValue;
}

/***** EXAMPLE *****/

uint16_t arrayCrc16(uint8_t *data, uint8_t len) {
  uint16_t crc;
  uint8_t aux = 0;
  crc = 0x0000; //Initialization of crc to 0x0000 for DNP
  //crc = 0xFFFF; //Initialization of crc to 0xFFFF for CCITT
  while (aux < len) {
    crc = crc16(crc, data[aux]);
    aux++;
  }
  return (~crc); //The crc value for DNP it is obtained by NOT operation
  //return crc; //The crc value for CCITT
}
