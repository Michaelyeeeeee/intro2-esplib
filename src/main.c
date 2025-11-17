#include <main.h>

TaskHandle_t mc;
TaskHandle_t fpga;

/**
 * @brief Task for microcontroller SPI communication
 *
 * @param pvParameters Task parameters (not used)
 */
void microcontroller_task(void *pvParameters)
{
    spi_device_handle_t spi;
    init(&spi, MC_CSPIN, MC_MISO, MC_MOSI, MC_SCLK);

    const uint32_t data_to_send = 0xFFFFFFFF;

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
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main()
{
    // Microcontroller task pinned to core 0
    xTaskCreatePinnedToCore(
        microcontroller_task,
        "Microcontroller Task",
        4096,
        NULL,
        1,
        &mc,
        0);

    // FPGA task pinned to core 1
    xTaskCreatePinnedToCore(
        FPGA_task,
        "FPGA Task",
        4096,
        NULL,
        1,
        &fpga,
        1);
}