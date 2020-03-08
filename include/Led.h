#ifndef LED_H
#define LED_H

#include <Device.h>
#include <devices.h>
#include <osdefs.h>

/**
 * LED class
 */
class Led : public Device {
private:
  int pin;
  gpio_pin_value_t value;
  handle_t gpio;

public:
  Led(handle_t gpio, int pin);
  virtual ~Led();

  virtual void begin(void) override;

  /**
   * @brief Turn on LED
   */
  virtual void on(void);

  /**
   * @brief Turn off LED
   */
  virtual void off(void);

  /**
   * Blink LED
   */
  virtual void blink(void);

  /**
   * @brief Check if the LED is on
   * 
   * @return true if the LED is on or false otherwise
   */
  virtual bool isOn(void);

private:
  /**
   * @brief Set pin value
   * 
   * @param value[in] gpio pin value
   */
  void setValue(gpio_pin_value_t value);
};

#endif