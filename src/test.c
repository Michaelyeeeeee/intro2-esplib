#include "test.h"

/** @brief initializes bus and adds device to bus
 *
 *  @param handle1 - handle of device to add to bus
 */
void init(spi_device_handle_t *handle1, gpio_num_t cs_pin, gpio_num_t miso, gpio_num_t mosi, gpio_num_t sclk)
{
    spi_bus_config_t bus = {
        // verify numbers
        .mosi_io_num = mosi,
        .miso_io_num = miso,
        .sclk_io_num = sclk,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 1024, // need to readjust, can probably cap at 32 bits
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

    reset(cs_pin);
}

/** @brief resets cs pin
 *
 *  @param cs_pin - cs pin to reset
 *  @return true
 */
bool reset(gpio_num_t cs_pin)
{
    gpio_set_level(cs_pin, 0);
    gpio_set_level(cs_pin, 1);
    return true;
}

/** @brief sends 4 8 bit inputs into multiplier
 *
 *  @param spi - spi device sending data
 *  @param data - data to send
 *  @param length - length of data to send
 *  @return true for successful transaction, otherwise false
 */
bool send_spi_data(spi_device_handle_t spi, const uint32_t *data, size_t length)
{
    spi_transaction_t send = {
        .tx_buffer = data,
        .length = length};
    // don't need polling for transmit b/c only send one data packet
    if (spi_device_transmit(spi, &send) != ESP_OK)
    {
        fprintf(stderr, "Failed to transmit message\n");
        return false;
    }

    return true;
}

/** @brief receives 4 8 bit inputs from multiplier
 *
 *  @param spi - spi device receiving data
 *  @param data - buffer to store received data
 *  @param length - length of data to receive
 *  @return true for successful transaction, otherwise false
 */
bool receive_spi_data(spi_device_handle_t spi, uint32_t *buffer, size_t length)
{
    spi_transaction_t receive = {
        .rx_buffer = buffer,
        .rxlength = length,
        .length = length,
    };

    if (spi_device_polling_transmit(spi, &receive) != ESP_OK)
    {
        fprintf(stderr, "Failed to receive message\n");
        return false;
    }

    return true;
}