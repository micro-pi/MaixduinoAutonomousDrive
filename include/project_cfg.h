#ifndef PROJECT_CFG_H
#define PROJECT_CFG_H

#include <pin_cfg.h>

#define PIN_FUNCTION(PIN) (static_cast<fpioa_function_t>(FUNC_GPIOHS0 + PIN))
#define POWER_LED_PIN (14)

#define LEFT_PIN_FORWARD (21)
#define LEFT_PIN_BACK (22)
#define RIGHT_PIN_FORWARD (23)
#define RIGHT_PIN_BACK (24)
#define LEFT_FUNCTION_FORWARD FUNC_TIMER0_TOGGLE1
#define LEFT_FUNCTION_BACK FUNC_TIMER0_TOGGLE2
#define RIGHT_FUNCTION_FORWARD FUNC_TIMER0_TOGGLE3
#define RIGHT_FUNCTION_BACK FUNC_TIMER0_TOGGLE4
#define LEFT_CHANNEL_FORWARD (0)
#define LEFT_CHANNEL_BACK (1)
#define RIGHT_CHANNEL_FORWARD (2)
#define RIGHT_CHANNEL_BACK (3)

#define MOVING_PWM_FREQUENCY (1000)

/* I2C0 */
#define I2C0_SDA_PIN (31)
#define I2C0_SCLK_PIN (30)

/* SPI0 Pins */
#define SPI_SLAVE_SELECT (0)
/**
 * ESP32 Chip Select
 */
#define SPI_MASTER_CS_PIN (25)
/**
 * Master In Slave Out
 */
#define SPI_MASTER_MISO_PIN (26)
/**
 * Serial Clock
 */
#define SPI_MASTER_SCLK_PIN (27)
/**
 * Master Out Slave In
 */
#define SPI_MASTER_MOSI_PIN (28)
/**
 * Master Clock Rate
 */
#define SPI_MASTER_CLOCK_RATE (8000000)

#define CORE_0 (0)
#define CORE_1 (1)

#endif
