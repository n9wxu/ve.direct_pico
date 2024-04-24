#include "pico/stdlib.h"
#include <cstdio>

#include "leds.hpp"

#include <cstdlib>

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "nlohmann/json.hpp"

#include "uart_rx.pio.h"

#define LED_S2 2
#define LED_S1 3
#define LED_D1 4
#define LED_D2 5
#define LED_BUS 6
#define LED_VE4 11
#define LED_VE3 12
#define LED_VE2 13
#define LED_VE1 14

#define RX_VE4 7
#define RX_VE3 8
#define RX_VE2 9
#define RX_VE1 10

#define TX_485 16
#define RX_485 17
#define OUT_485 18

ledOut<LED_S2> led_s2;
ledOut<LED_S1> led_s1;
ledOut<LED_D1> led_d1;
ledOut<LED_D2> led_d2;
ledOut<LED_BUS> led_bus;
ledOut<LED_VE4> led_ve4;
ledOut<LED_VE3> led_ve3;
ledOut<LED_VE2> led_ve2;
ledOut<LED_VE1> led_ve1;

#define VE_DIRECT_BAUD 19200

void blink(void *p) {

  gpio_init(RX_VE1);
  gpio_set_dir(RX_VE1, GPIO_IN);
  gpio_init(RX_VE2);
  gpio_set_dir(RX_VE2, GPIO_IN);
  gpio_init(RX_VE3);
  gpio_set_dir(RX_VE3, GPIO_IN);
  gpio_init(RX_VE4);
  gpio_set_dir(RX_VE4, GPIO_IN);

  // Set up the state machine we're going to use to receive them.
  // PIO pio = pio0;
  // uint sm = 0;
  // uint offset = pio_add_program(pio, &uart_rx_program);
  // uart_rx_program_init(pio, sm, offset, RX_VE4, VE_DIRECT_BAUD);

  for (;;) {
    // if (uart_rx_program_dataReady(pio, sm)) {
    //   led_s2.put(true);
    //   char c = uart_rx_program_getc(pio, sm);
    //   putchar(c);
    //   led_s2.put(false);
    // }
    led_ve1.put(gpio_get(RX_VE1));
    led_ve2.put(gpio_get(RX_VE2));
    led_ve3.put(gpio_get(RX_VE3));
    led_ve4.put(gpio_get(RX_VE4));
  }
}

int main() {
  stdio_init_all();

  xTaskCreate(blink, "blinker", 500, NULL, 5, NULL);

  vTaskStartScheduler();
}
