#pragma once

#include "test.h"
#define MC_CSPIN GPIO_NUM_10
#define MC_MISO GPIO_NUM_13
#define MC_MOSI GPIO_NUM_11
#define MC_SCLK GPIO_NUM_12

#define FPGA_CSPIN GPIO_NUM_34
#define FPGA_MISO GPIO_NUM_37
#define FPGA_MOSI GPIO_NUM_35
#define FPGA_SCLK GPIO_NUM_36

// thread for microcontroller
void microcontroller_task(void *pvParameters);

// test thread for FPGA (will not be used after integration)
void FPGA_task(void *pvParameters);