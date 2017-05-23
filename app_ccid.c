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


static inline void app_ccid_power_on(APP* app, IO* io)
{
//    io_data_write(io, &__CCID_ATR, CCID_ATR_SIZE);
#if (APP_DEBUG_CCID)
    printf("CCID power on\n");
#endif

//    if(!scard_power_on(app))
//    {
//#if (APP_DEBUG_ERRORS)
//        printf("SC power on failure\n");
//#endif
//    }
}

static inline void app_ccid_power_off(APP* app, IO* io)
{
#if (APP_DEBUG_CCID)
    printf("CCID power off\n");
#endif
//    scard_power_off(app);
}

static inline void app_ccid_get_params(APP* app, unsigned int cmd, HANDLE handle, IO* io)
{
    //io_data_write(io, &__T1_PARAMS, sizeof(CCID_T1_PARAMS));
#if (APP_DEBUG_CCID)
    printf("CCID parameters request\n");
#endif
//    io_complete_ex(app->usbd, cmd, handle, io, CCID_T_1);
//    error(ERROR_SYNC);
}

static void app_ccid_apdu(APP* app, IO* io)
{
#if (APP_DEBUG_CCID)
    printf("CCID apdu\n");
#endif
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
