/*
 * pn532.c
 *
 *  Created on: 19 рту. 2017 у.
 *      Author: RomaJam
 */

#include "../rexos/userspace/stm32/stm32_driver.h"
#include "../rexos/userspace/spi.h"
#include "../rexos/userspace/pin.h"
#include "../rexos/userspace/gpio.h"
#include "../rexos/userspace/stdio.h"
#include "pn532.h"

#define PN532_FRAME()       ((PN532_START_FRAME*)io_data(pn532->io))
#define PN532_FRAME_DATA()  ((uint8_t*)(io_data(pn532->io) + sizeof(PN532_START_FRAME)))
#define PN532_DATA()        ((uint8_t*)(io_data(pn532->io) + sizeof(PN532_START_FRAME) - sizeof(PN532_DATA)))
#define PN532_POSTAMBULE()  ((PN532_STOP_FRAME*)(io_data(pn532->io) + \
                                                 sizeof(PN532_START_FRAME) +  \
                                                 pn532_extract_data_size(pn532) - \
                                                 sizeof(PN532_DATA)))


void pn532_dump(uint8_t* data, uint32_t size, char* S)
{
    printf("%s:\n", S);
    for(uint32_t i = 0; i < size; i++)
        printf("%02X ", data[i]);
    printf("\n");
}

static inline void pn532_power_on(PN532* pn532)
{
    gpio_set_pin(PN_RST_PIN);
    sleep_ms(99);
    pn532->state = PN532_STATE_IDLE;
}

static inline void pn532_power_off(PN532* pn532)
{
    gpio_reset_pin(PN_RST_PIN);
    sleep_ms(99);
    pn532->state = PN532_STATE_OFF;
}

static inline void pn532_data_line_on()
{
    gpio_reset_pin(PN_NSS_PIN);
}

static inline void pn532_data_line_off()
{
    gpio_set_pin(PN_NSS_PIN);
}

static inline void pn532_put_data_size(PN532* pn532, unsigned int data_size)
{
    /*  Length = TxLength + ADataLength + PN_MAX_TFI_PD0_SIZE
     *  TxLength        - Length from HOST (by CCID)
     *  ADataLength     - Length from Service CmdBuf (only if ADataLength > 1)
     */
    data_size += sizeof(uint8_t) << 1;
    PN532_FRAME()->data_size_hi = (uint8_t)(data_size >> 8);
    PN532_FRAME()->data_size_lo = (uint8_t)(data_size);
    PN532_FRAME()->LCS = -((uint8_t)(data_size >> 8) + (uint8_t)(data_size));
}

static inline uint16_t pn532_extract_data_size(PN532* pn532)
{
    return ((PN532_FRAME()->data_size_hi << 8) | (PN532_FRAME()->data_size_lo));
}

static inline void pn532_calculate_dcs(PN532* pn532)
{
    PN532_POSTAMBULE()->DCS = 0;
    for(int i = 0; i < pn532_extract_data_size(pn532); i++)
        PN532_POSTAMBULE()->DCS += PN532_DATA()[i];
    PN532_POSTAMBULE()->DCS = -PN532_POSTAMBULE()->DCS;
    PN532_POSTAMBULE()->stop_byte = 0x00;
}

static inline void pn532_prepare_frame(PN532* pn532, uint8_t code, unsigned int data_size)
{
    PN532_FRAME()->cmd_type = PN_CMD_TYPE_DATA_WRITE;
    PN532_FRAME()->start_byte = 0x00;
    PN532_FRAME()->sopCH = 0x00;
    PN532_FRAME()->sopCL = 0xFF;
    PN532_FRAME()->NPLC = 0xFF;
    PN532_FRAME()->NPL = 0xFF;
    // prepare data
    pn532_put_data_size(pn532, data_size);
    PN532_FRAME()->data.TFI = PN_FRAME_TFI_TRANSMIT;
    PN532_FRAME()->data.PD0 = code;
    // fill postamble
    pn532_calculate_dcs(pn532);
}

static inline void pn532_cmd(PN532* pn532, uint8_t code, unsigned int data_size, ...)
{
    if (data_size)
    {
        va_list arg;
        va_start(arg, data_size);
        for(int i = 0; i < data_size; i++)
            PN532_FRAME_DATA()[i] = (uint8_t)va_arg(arg, int);
        va_end(arg);
    }
    pn532_prepare_frame(pn532, code, data_size);
    pn532->io->data_size = sizeof(PN532_START_FRAME) + sizeof(PN532_STOP_FRAME) + data_size;
#if (PN_DEBUG_DATA_EXCHANGE)
    pn532_dump(io_data(pn532->io), pn532->io->data_size, "PN532");
#endif // PN_DEBUG_DATA_EXCHANGE

    pn532_data_line_on();
    spi_write_data(PN_SPI, pn532->io);
    pn532_data_line_off();

    pn532->state = PN532_STATE_ACK;
}

unsigned int pn532_open_hw(PN532* pn532)
{
#if (PN_DEBUG)
    printf("PN532 open\n");
#endif // PN_DEBUG
    pn532->io = io_create(PN_MAX_CMD_SIZE);
    if(pn532->io == NULL)
        return 1;

    io_reset(pn532->io);

    gpio_enable_pin(PN_IRQ_PIN, GPIO_MODE_IN_FLOAT);
    gpio_enable_pin(PN_NSS_PIN, GPIO_MODE_OUT);
    gpio_enable_pin(PN_RST_PIN, GPIO_MODE_OUT);
    pn532_power_off(pn532);

    pin_enable(PN_SCK_PIN, STM32_GPIO_MODE_AF, AF5);
    pin_enable(PN_MISO_PIN, STM32_GPIO_MODE_AF, AF5);
    pin_enable(PN_MOSI_PIN, STM32_GPIO_MODE_AF, AF5);

    spi_open(PN_SPI, SPI_MODE_MASTER | SPI_SSI_ON | SPI_DATA_BO_LSB | SPI_NSS_SOFTWARE | SPI_BAUDRATE_DIV8);

    pn532_data_line_off();
    pn532_power_on(pn532);

    pn532_cmd(pn532, PN_CMD_GET_FIRMWARE_VERSION, 0);                          // First Cmds will be discarted
    pn532_cmd(pn532, PN_CMD_GET_FIRMWARE_VERSION, 0);

    pn532_cmd(pn532, PN_CMD_SAM_CONFIGURATION, 1, 0x01);                       // Disable SAM to calm PN: Normal mode, the SAM is not used
    pn532_cmd(pn532, PN_CMD_RF_CONFIGURATION, 4, 0x05, 0x02, 0x01, 0x05);      // Setup RF config: One retry, ATR: once, PSL: once, Activation: once
    pn532_cmd(pn532, PN_CMD_RF_CONFIGURATION, 4, 0x02, 0x00, 0x0B, 0x10);      // Setup RtrTimout: 0x0B - ATR_Res timeOut; 0x10 - TimeOutAnswer
    pn532_cmd(pn532, PN_CMD_RF_CONFIGURATION, 2, 0x04, 0x00);                  // Setup RtrTimeOut: 0x00 - One Retry; 0xFF - Eternally
    pn532_cmd(pn532, PN_CMD_RF_CONFIGURATION, 2, 0x01, 0x01);

    return 0;
}

unsigned int pn532_reset(PN532* pn532)
{
#if (PN_DEBUG)
    printf("PN532 reset\n");
#endif // PN_DEBUG
    pn532_power_off(pn532);
    pn532_power_on(pn532);
    return 0;
}

unsigned int pn532_close_hw(PN532* pn532)
{
#if (PN_DEBUG)
    printf("PN532 close\n");
#endif // PN_DEBUG
    spi_close(PN_SPI);
    return 0;
}
