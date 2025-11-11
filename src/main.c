#include <main.h>

/**
 * @brief Task for microcontroller SPI communication
 *
 * @param pvParameters Task parameters (not used)
 */
void microcontroller_task(void *pvParameters)
{
    spi_device_handle_t spi;
    init(&spi, MC_CSPIN, MC_MISO, MC_MOSI, MC_SCLK);

    const uint32_t data_to_send = {0x12, 0x34, 0x56, 0x78}; // [144 188; 222 240] in decimal

    while (1)
    {
        if (!send_spi_data(spi, &data_to_send, 32))
        {
            fprintf(stderr, "Failed to send SPI data\n");
        }
        else
        {
            fprintf(stdout, "Microcontroller sent data successfully\n");
        }

        vTaskDelay(portMAX_DELAY); // Delay indefinitely
    }
}

/**
 * @brief Task for FPGA SPI communication
 *
 * @param pvParameters Task parameters (not used)
 */
void FPGA_task(void *pvParameters)
{
    spi_device_handle_t spi;
    init(&spi, FPGA_CSPIN, FPGA_MISO, FPGA_MOSI, FPGA_SCLK);

    uint32_t received_data;

    while (1)
    {
        if (!receive_spi_data(spi, &received_data, 32))
        {
            fprintf(stderr, "Failed to receive SPI data\n");
        }
        else
        {
            fprintf(stdout, "FPGA received data successfully\n");
        }
    }
}

void app_main()
{
    xTaskCreate(microcontroller_task, "Microcontroller Task", 4096, NULL, 5, NULL);
    xTaskCreate(FPGA_task, "FPGA Task", 4096, NULL, 5, NULL);
}