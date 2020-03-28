#include <project_cfg.h>

const fpioa_cfg_t g_fpioa_cfg =
    {
        .version = PIN_CFG_VERSION,
        .functions_count = (1 + 4 + 2 + 4),
        .functions =
            {
                /* LED */
                {POWER_LED_PIN, PIN_FUNCTION(POWER_LED_PIN)},
                /* MOVEMENT */
                {LEFT_PIN_FORWARD, LEFT_FUNCTION_FORWARD},
                {LEFT_PIN_BACK, LEFT_FUNCTION_BACK},
                {RIGHT_PIN_FORWARD, RIGHT_FUNCTION_FORWARD},
                {RIGHT_PIN_BACK, RIGHT_FUNCTION_BACK},
                /* I2C */
                {I2C0_SDA_PIN, FUNC_I2C0_SDA},
                {I2C0_SCLK_PIN, FUNC_I2C0_SCLK},
                /* SPI */
                {SPI_MASTER_SCLK_PIN, FUNC_SPI0_SCLK},
                {SPI_MASTER_MOSI_PIN, FUNC_SPI0_D0},
                {SPI_MASTER_MISO_PIN, FUNC_SPI0_D1},
                {SPI_MASTER_CS_PIN, static_cast<fpioa_function_t>(FUNC_SPI0_SS0 + SPI_SLAVE_SELECT)},
            }};

const pin_cfg_t g_pin_cfg =
    {
        .version = PIN_CFG_VERSION,
        .set_spi0_dvp_data = false};