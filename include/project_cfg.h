#ifndef PROJECT_CFG_H
#define PROJECT_CFG_H

#include <pin_cfg.h>

#define PIN_FUNCTION(PIN) (static_cast<fpioa_function_t>(FUNC_GPIOHS0 + PIN))
#define LED_PIN (14)

#define CORE_0 (0)
#define CORE_1 (1)

#endif
