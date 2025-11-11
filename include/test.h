#pragma once

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include <stdbool.h>

#define BAUDRATE 1000000
#define CSPIN 5

// initializes spi and gpio
void init(spi_device_handle_t *handle, gpio_num_t cs_pin);

// resets cs pin
bool reset(gpio_num_t cs_pin);

// sends data over spi
bool send_spi_data(spi_device_handle_t spi, const uint8_t *data, size_t length);

// receives data over spi
bool receive_spi_data(spi_device_handle_t spi, uint8_t *buffer, size_t length);