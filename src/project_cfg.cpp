#include <project_cfg.h>

const fpioa_cfg_t g_fpioa_cfg =
    {
        .version = PIN_CFG_VERSION,
        .functions_count = 1,
        .functions =
            {
                {LED_PIN, PIN_FUNCTION(LED_PIN)}}};

const pin_cfg_t g_pin_cfg =
    {
        .version = PIN_CFG_VERSION,
        .set_spi0_dvp_data = 1};