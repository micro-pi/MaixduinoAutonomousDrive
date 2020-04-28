#ifndef __ITG3200_H__
#define __ITG3200_H__

/* https://github.com/Seeed-Studio/Grove_3_Axis_Digital_Gyro */

#define GYRO_ADDRESS 0x68
/* ITG3200 Register Defines */
#define ITG3200_WHO 0x00
#define ITG3200_SMPL 0x15
#define ITG3200_DLPF 0x16
#define ITG3200_INT_C 0x17
#define ITG3200_INT_S 0x1A
#define ITG3200_TMP_H 0x1B
#define ITG3200_TMP_L 0x1C
#define ITG3200_GX_H 0x1D
#define ITG3200_GX_L 0x1E
#define ITG3200_GY_H 0x1F
#define ITG3200_GY_L 0x20
#define ITG3200_GZ_H 0x21
#define ITG3200_GZ_L 0x22
#define ITG3200_PWR_M 0x3E

/*  Interrupt Configuration  */
#define RAW_RDY_EN_BIT ((uint8_t)0U)
#define RAW_RDY_EN_MASK ((uint8_t)(1U << RAW_RDY_EN_BIT))
#define ITG_RDY_EN_BIT ((uint8_t)2U)
#define ITG_RDY_EN_MASK ((uint8_t)(1U << ITG_RDY_EN_BIT))
#define INT_ANYRD_2CLEAR_BIT ((uint8_t)4U)
#define INT_ANYRD_2CLEAR_MASK ((uint8_t)(1U << INT_ANYRD_2CLEAR_BIT))
#define LATCH_INT_EN_BIT ((uint8_t)5U)
#define LATCH_INT_EN_MASK ((uint8_t)(1U << LATCH_INT_EN_BIT))
#define OPEN_BIT ((uint8_t)6U)
#define OPEN_MASK ((uint8_t)(1U << OPEN_BIT))
#define ACTL_BIT ((uint8_t)7U)
#define ACTL_MASK ((uint8_t)(1U << ACTL_BIT))

/* Interrupt Status */
#define RAW_DATA_RDY_BIT ((uint8_t)0U)
#define RAW_DATA_RDY_MASK ((uint8_t)(1U << RAW_DATA_RDY_BIT))
#define ITG_RDY_BIT ((uint8_t)2U)
#define ITG_RDY_MASK ((uint8_t)(1U << ITG_RDY_BIT))

#define FS_SEL_BIT ((uint8_t)3U)
#define FS_SEL_MASK ((uint8_t)(0b11U << FS_SEL_BIT))
#define DLPF_CFG_BIT ((uint8_t)0U)
#define DLPF_CFG_MASK ((uint8_t)(0b111U << DLPF_CFG_BIT))

/* Power Management */
#define H_RESET_BIT ((uint8_t)7U)
#define H_RESET_MASK ((uint8_t)(1U << H_RESET_BIT))
#define SLEEP_BIT ((uint8_t)6U)
#define SLEEP_MASK ((uint8_t)(1U << SLEEP_BIT))
#define STBY_XG_BIT ((uint8_t)5U)
#define STBY_XG_MASK ((uint8_t)(1U << STBY_XG_BIT))
#define STBY_YG_BIT ((uint8_t)4U)
#define STBY_YG_MASK ((uint8_t)(1U << STBY_YG_BIT))
#define STBY_ZG_BIT ((uint8_t)3U)
#define STBY_ZG_MASK ((uint8_t)(1U << STBY_ZG_BIT))
#define CLK_SEL_BIT ((uint8_t)0U)
#define CLK_SEL_MASK ((uint8_t)(0b111U << CLK_SEL_BIT))

#include "../Device.h"
#include <osdefs.h>

typedef enum {
  RANGE_2000_DEG_PER_SEC = 0x03u
} FullScaleRange;

typedef enum {
  BANDWIDTH_256HZ_RATE_8KHZ = 0x00u,
  BANDWIDTH_188HZ_RATE_1KHZ = 0x01u,
  BANDWIDTH_98HZ_RATE_1KHZ = 0x02u,
  BANDWIDTH_42HZ_RATE_1KHZ = 0x03u,
  BANDWIDTH_20HZ_RATE_1KHZ = 0x04u,
  BANDWIDTH_10HZ_RATE_1KHZ = 0x05u,
  BANDWIDTH_5HZ_RATE_1KHZ = 0x06u
} LowPassFilter;

typedef enum {
  LOGIC_LEVEL_ACTIVE_HIGH = 0x00u,
  LOGIC_LEVEL_ACTIVE_LOW = 0x01u
} LogicLevelIntOutputPin;

typedef enum {
  DRIVE_TYPE_PUSH_PULL = 0x00u,
  DRIVE_TYPE_OPEN_DRAIN = 0x01u
} DriveTypeIntOutputPin;

typedef enum {
  LATCH_MODE_50US_PULSE = 0x00u,
  LATCH_MODE_LATCH_INT_CLEARED = 0x01u
} LatchMode;

typedef enum {
  LATCH_2CLEAN_STATUS_REGISTER_READ_ONLY = 0x00u,
  LATCH_2CLEAN_ANY_REGISTER_READ = 0x01u
} LatchClearMethod;

typedef enum {
  INTERNAL_OSCILLATOR = 0,
  PLL_X_GYRO_REFERENCE = 1,
  PLL_Y_GYRO_REFERENCE = 2,
  PLL_Z_GYRO_REFERENCE = 3,
  PLL_EXTERNAL_32_768KHZ_REFERENCE = 4,
  PLL_EXTERNAL_19_2KHZ_REFERENCE = 5
} ClockSource;

#pragma pack(1)
typedef union {
  uint8_t value;
#pragma pack(1)
  struct {
    /**
     * The DLPF_CFG parameter sets the digital low pass filter configuration.
     * It also determines the internal sampling rate used by the device.
     * Bit0 - Bit2
     */
    LowPassFilter lowPassFilter : 3;
    /**
     * The FS_SEL parameter allows setting the full-scale range of the gyro sensors.
     * The power-on-reset value of FS_SEL is 00h. Set to 03h for proper operation.
     * Bit3 - Bit4
     */
    FullScaleRange fullScaleRange : 2;
    /**
     * Must be zero
     * Bit5 - Bit7
     */
    uint8_t zero765 : 3;
  } config;
} ITG3200DlpfFsConfig;

#pragma pack(1)
typedef union {
  uint8_t value;
#pragma pack(1)
  struct {
    /**
     * RAW_RDY_EN - Enable interrupt when data is available
     * Bit0
     */
    bool rawDataReadyEnabled : 1;
    /**
     * Must be zero
     * Bit1
     */
    uint8_t zero1 : 1;
    /**
     * ITG_RDY_EN - Enable interrupt when device is ready (PLL ready after changing clock source)
     * Bit2
     */
    bool interruptEnabled : 1;
    /**
     * Must be zero
     * Bit3
     */
    uint8_t zero3 : 1;
    /**
    * INT_ANYRD_2CLEAR - Latch clear method: 1=any register read, 0=status register read only
    * Bit4
    */
    LatchClearMethod latchClearMethod : 1;
    /**
     * LATCH_INT_EN - Latch mode: 1=latch until interrupt is cleared, 0=50us pulse
     * Bit5
     */
    LatchMode latchMode : 1;
    /**
     * OPEN - Drive type for INT output pin: 1=open drain, 0=push-pull
     * Bit6
     */
    DriveTypeIntOutputPin driveTypeIntOutputPin : 1;
    /**
     * ACTL - Logic level for INT output pin: 1=active low, 0=active high
     * Bit7
     */
    LogicLevelIntOutputPin logicLevelIntOutputPin : 1;
  } config;
} ITG3200InterruptConfig;

class ITG3200 : public Device {
private:
  uint8_t writeBuffer[8];
  uint8_t readBuffer[8];
  handle_t i2c;
  handle_t device;
  int16_t xOffset;
  int16_t yOffset;
  int16_t zOffset;

public:
  ITG3200(const char *deviceName);
  void setI2c(const handle_t i2c);
  ErrorCode initDevice(void);
  double getTemperature(void);
  void getXYZ(int16_t &x, int16_t &y, int16_t &z);
  void getAngularVelocity(float &ax, float &ay, float &az);
  void zeroCalibrate(unsigned int samples, unsigned int sampleDelayMS);
  void setXoffset(const int16_t xOffset);
  void setYoffset(const int16_t yOffset);
  void setZoffset(const int16_t zOffset);
  int16_t getXoffset(void);
  int16_t getYoffset(void);
  int16_t getZoffset(void);

  uint8_t whoAmI(void);

  uint8_t getSampleRateDivider(void);
  void setSampleRateDivider(const uint8_t sampleRateDivider);

  void setDlpfFsConfig(const ITG3200DlpfFsConfig dlpfFsConfig);
  ITG3200DlpfFsConfig getDlpfFsConfig(void);

  void setInterruptConfig(const ITG3200InterruptConfig interruptConfig);
  ITG3200InterruptConfig getInterruptConfig(void);

  bool isPllReady(void);
  bool isRawDataReady(void);

  int resetDevice(void);

  bool isSleepMode(void);
  void setSleepMode(bool enable);

  bool isStandbyModeX(void);
  void setStandbyModeX(bool enable);

  bool isStandbyModeY(void);
  void setStandbyModeY(bool enable);

  bool isStandbyModeZ(void);
  void setStandbyModeZ(bool enable);

  ClockSource getClockSource(void);
  void setClockSource(ClockSource clockSource);

  int8_t read(uint8_t reg);
  int write(uint8_t reg, uint8_t data);

private:
  int16_t read16(uint8_t reg);
  void readData(void);
  uint8_t getRegisterValue(uint8_t reg, uint8_t mask, uint8_t bit);
  int setRegisterBitsValue(uint8_t reg, uint8_t mask, uint8_t bit, uint8_t value);
  int setRegisterBits(uint8_t reg, uint8_t mask, uint8_t bit);
  int clearRegisterBits(uint8_t reg, uint8_t mask, uint8_t bit);
};

#endif
