/*
 * app_ccid.c
 *
 *  Created on: 23 мая 2017 г.
 *      Author: RLeonov
 */


#include "app_private.h"
#include "../rexos/userspace/io.h"
#include "../rexos/userspace/stdio.h"
#include "../rexos/userspace/ccid.h"
#include "../rexos/userspace/usb.h"
#include "../rexos/userspace/error.h"
#include "app_ccid.h"
#include "config.h"
#include "leds.h"


const uint8_t __CCID_ATR[] = {
        0x3B, 0xDC, 0x18, 0xFF, 0x81, 0x91, 0xFE, 0x1F,
        0xC3, 0x80, 0x73, 0xC8, 0x21, 0x13, 0x66, 0x01,
        0x06, 0x11, 0x59, 0x00, 0x01, 0x28
};

const CCID_T1_PARAMS __T1_PARAMS = {
    0x11,                                                   /* bmFindexDindex */
    0x10,                                                   /* bmTCCKST1 */
    0x00,                                                   /* bGuardTimeT1 */
    0x45,                                                   /* bmWaitingIntegersT1 */
    0x00,                                                   /* bClockStop */
    0xFE,                                                   /* bIFSC */
    0x00                                                    /* bNadValue */
};

static inline void app_ccid_power_on(APP* app, IO* io)
{
    io_data_write(io, &__CCID_ATR, sizeof(__CCID_ATR));
#if (APP_DEBUG_CCID)
    printf("CCID power on\n");
#endif
}

static inline void app_ccid_power_off(APP* app, IO* io)
{
#if (APP_DEBUG_CCID)
    printf("CCID power off\n");
#endif
}

static inline void app_ccid_get_params(APP* app, unsigned int cmd, HANDLE handle, IO* io)
{
    io_data_write(io, &__T1_PARAMS, sizeof(CCID_T1_PARAMS));
#if (APP_DEBUG_CCID)
    printf("CCID parameters request\n");
#endif
    io_complete_ex(app->usbd, cmd, handle, io, CCID_T_1);
    error(ERROR_SYNC);
}

static void app_ccid_apdu(APP* app, IO* io)
{
    uint8_t *data = io_data(io);

    if(data[0] == 0x80 && data[1] == 0x12 && data[2] == 0x34)
    {
#if (APP_DEBUG_CCID)
        printf("apdu sleep %u sec\n", data[3]);
#endif
        sleep_ms(data[3] * 1000);
        ((uint8_t*)io_data(io))[0] = 0x90;
        ((uint8_t*)io_data(io))[1] = 0x00;
    }
    else
    {
        ((uint8_t*)io_data(io))[0] = 0x6A;
        ((uint8_t*)io_data(io))[1] = 0x82;
    }
    io->data_size = 2;
}

void app_ccid_notify_slot_change(APP* app, unsigned int state)
{
    ipc_post_inline(app->usbd, HAL_CMD(HAL_USBD_IFACE, state), USBD_IFACE(USB_CCID_INTERFACE, 0), 0, 0);
}

void app_ccid_request(APP* app, IPC* ipc)
{
    switch (HAL_ITEM(ipc->cmd))
    {
    case USB_CCID_APDU:
        app_ccid_apdu(app, (IO*)ipc->param2);
        break;
    case USB_CCID_POWER_ON:
        app_ccid_power_on(app, (IO*)ipc->param2);
        break;
    case USB_CCID_POWER_OFF:
        app_ccid_power_off(app, (IO*)ipc->param2);
        break;
    case USB_CCID_GET_PARAMS:
    case USB_CCID_SET_PARAMS:
    case USB_CCID_RESET_PARAMS:
        //protocol number on set/reset is ignored
        app_ccid_get_params(app, ipc->cmd & ~HAL_REQ_FLAG, ipc->param1, (IO*)ipc->param2);
        break;
    default:
        error(ERROR_NOT_SUPPORTED);
    }
}
