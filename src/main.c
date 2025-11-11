#include "main.h"

void microcontroller_task(void *pvParameters)
{
    spi_device_handle_t spi;
    init(&spi, CSPIN, GPIO_NUM_19, GPIO_NUM_23, GPIO_NUM_18);

    const uint32_t data_to_send[4] = {0x12, 0x34, 0x56, 0x78};
    uint32_t received_data[4] = {0};

    while (1)
    {
        if (!send_spi_data(spi, data_to_send, 4))
        {
            fprintf(stderr, "Failed to send SPI data\n");
        }

        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

void FPGA_task(void *pvParameters)
{
    spi_device_handle_t spi;
    init(&spi, FPGA_CSPIN, GPIO_NUM_19, GPIO_NUM_23, GPIO_NUM_18);

    const uint32_t data_to_send[4] = {0x9A, 0xBC, 0xDE, 0xF0};
    uint32_t received_data[4] = {0};

    while (1)
    {
        if (!send_spi_data(spi, data_to_send, 4))
        {
            fprintf(stderr, "Failed to send SPI data\n");
        }

        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

void app_main()
{
    xTaskCreate(microcontroller_task, "Microcontroller Task", 4096, NULL, 5, NULL);
    xTaskCreate(FPGA_task, "FPGA Task", 4096, NULL, 5, NULL);
}