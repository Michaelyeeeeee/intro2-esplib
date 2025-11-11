#include "test.h"

/* @brief initializes bus and adds device to bus
 *
 * @param handle1 - handle of device to add to bus
 */
void init(spi_device_handle_t *handle1, gpio_num_t cs_pin)
{
    spi_bus_config_t bus = {
        // verify numbers
        .mosi_io_num = 23,
        .miso_io_num = 19,
        .sclk_io_num = 18,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096, // need to readjust
    };
    if (spi_bus_initialize(SPI2_HOST, &bus, SPI_DMA_DISABLED) != ESP_OK)
    {
        fprintf(stderr, "Failed to initialize SPI bus\n");
        return;
    }
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = BAUDRATE,
        .mode = 0,
        .spics_io_num = cs_pin,
    };

    if (spi_bus_add_device(SPI2_HOST, &devcfg, handle1) != ESP_OK)
    {
        fprintf(stderr, "Failed to add device to bus\n");
        return;
    }
}

bool reset(gpio_num_t cs_pin)
{
    gpio_set_level(cs_pin, 0);
}

bool send_spi_data(spi_device_handle_t spi, const uint8_t *data, size_t length)
{
}

bool receive_spi_data(spi_device_handle_t spi, uint8_t *buffer, size_t length)
{
}