#pragma once

#include <hardware/gpio.h>
#include <stdbool.h>

template <int pin> struct ledOut {
  void put(bool v) { gpio_put(pin, v); }

  ledOut() {
    gpio_init(pin);
    gpio_set_dir(pin, true);
  }

  ~ledOut(){};
};
