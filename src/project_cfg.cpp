#include <project_cfg.h>

const fpioa_cfg_t g_fpioa_cfg =
    {
        .version = PIN_CFG_VERSION,
        .functions_count = 5,
        .functions =
            {
                {LED_PIN, PIN_FUNCTION(LED_PIN)},
                {LEFT_PIN_FORWARD, LEFT_FUNCTION_FORWARD},
                {LEFT_PIN_BACK, LEFT_FUNCTION_BACK},
                {RIGHT_PIN_FORWARD, RIGHT_FUNCTION_FORWARD},
                {RIGHT_PIN_BACK, RIGHT_FUNCTION_BACK}}};

const pin_cfg_t g_pin_cfg =
    {
        .version = PIN_CFG_VERSION,
        .set_spi0_dvp_data = 1};