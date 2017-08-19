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


unsigned int pn532_open_hw(PN532* pn532)
{
#if (PN_DEBUG)
    printf("PN532 open\n");
#endif // PN_DEBUG
    pn532->io = io_create(sizeof(PN532_FRAME));
    if(pn532->io == NULL)
    {
        return 1;
    }


    gpio_enable_pin(PN_IRQ_PIN, GPIO_MODE_IN_FLOAT);
    gpio_enable_pin(PN_RST_PIN, GPIO_MODE_OUT);
    gpio_reset_pin(PN_RST_PIN);
    gpio_enable_pin(PN_NSS_PIN, GPIO_MODE_OUT);
    gpio_set_pin(PN_NSS_PIN);
    pin_enable(PN_SCK_PIN, STM32_GPIO_MODE_AF, AF5);
    pin_enable(PN_MISO_PIN, STM32_GPIO_MODE_AF, AF5);
    pin_enable(PN_MOSI_PIN, STM32_GPIO_MODE_AF, AF5);

    spi_open(PN_SPI, SPI_MODE_MASTER| SPI_SSI_ON | SPI_DATA_BO_LSB | SPI_NSS_SOFTWARE);

    pn532_power_on(pn532);

    return 0;
}

unsigned int pn532_reset(PN532* pn532)
{
#if (PN_DEBUG)
    printf("PN532 reset\n");
#endif // PN_DEBUG
    pn532_power_off();
    pn532_power_on();
}

unsigned int pn532_close_hw(PN532* pn532)
{
#if (PN_DEBUG)
    printf("PN532 close\n");
#endif // PN_DEBUG
    spi_close(PN_SPI);
    return 0;
}
