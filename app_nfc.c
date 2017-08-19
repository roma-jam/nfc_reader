/*
 * app_nfc.c
 *
 *  Created on: 18 рту. 2017 у.
 *      Author: RLeonov
 */

#include "../rexos/userspace/sys.h"
#include "../rexos/userspace/spi.h"
#include "config.h"
#include "app_private.h"
#include "app_nfc.h"
#include "pn532/pn532.h"

void nfc();

const REX __NFC = {
    //name
    "NFC",
    //size
    600,
    //priority
    201,
    //flags
    PROCESS_FLAGS_ACTIVE | REX_FLAG_PERSISTENT_NAME,
    //function
    nfc
};

void app_nfc_init(APP *app)
{
#if (APP_DEBUG_NFC)
    printf("NFC init\n");
#endif // APP_NFC_DEBUG

    app->nfc = process_create(&__NFC);
    if(app->nfc == INVALID_HANDLE)
        return;

    ack(app->nfc, HAL_REQ(HAL_NFC, IPC_OPEN), 0, 0, 0);
    ack(app->nfc, HAL_REQ(HAL_NFC, NFC_RESET), 0, 0, 0);
}

static void app_nfc_request(PN532* pn532, IPC* ipc)
{
    switch (HAL_ITEM(ipc->cmd))
    {
        case IPC_OPEN:
            pn532_open_hw(pn532);
            break;
        case IPC_CLOSE:
            pn532_close_hw(pn532);
            break;
        case NFC_RESET:
            printf("NFC: reset\n");
            break;
        case NFC_FIELD_ON:
            printf("NFC: field on\n");
            break;
        case NFC_FIELD_OFF:
            printf("NFC: field off\n");
            break;
        case NFC_DATA_EXCHANGE:
            printf("NFC: data exchange\n");
            break;
        default:
            error(ERROR_NOT_SUPPORTED);
            break;
    }
}


void nfc()
{
    PN532 pn532;
    IPC ipc;

#if (APP_DEBUG_NFC)
    open_stdout();
#endif // APP_DEBUG_NFC

    for (;;)
    {
        ipc_read(&ipc);
        switch (HAL_GROUP(ipc.cmd))
        {
        case HAL_NFC:
            app_nfc_request(&pn532, &ipc);
            break;
        default:
#if (APP_DEBUG_NFC)
            printf("NFC: Unhandled ipc\n");
#endif // APP_RADIO_DEBUG
            error(ERROR_NOT_SUPPORTED);
            break;
        }
        ipc_write(&ipc);
    }

}
