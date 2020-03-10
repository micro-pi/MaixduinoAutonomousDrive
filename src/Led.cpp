#include "Led.h"

Led::Led(handle_t gpio, int pin) {
  this->gpio = gpio;
  this->pin = pin;
  this->value = GPIO_PV_HIGH;
}

Led::~Led() {
}

void Led::begin(void) {
  gpio_set_drive_mode(this->gpio, this->pin, GPIO_DM_OUTPUT);
  on();
}

void Led::on(void) {
  setValue(GPIO_PV_HIGH);
}

void Led::off(void) {
  setValue(GPIO_PV_LOW);
}

void Led::blink(void) {
  if (isOn()) {
    off();
  } else {
    on();
  }
}

bool Led::isOn(void) {
  return this->value == GPIO_PV_HIGH;
}

void Led::setValue(gpio_pin_value_t value) {
  this->value = value;
  gpio_set_pin_value(this->gpio, this->pin, this->value);
}