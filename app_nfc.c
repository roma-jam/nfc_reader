/*
 * app_nfc.c
 *
 *  Created on: 18 рту. 2017 у.
 *      Author: RLeonov
 */

//#include "../rexos/userspace/spi.h"
#include "../rexos/userspace/io.h"
#include "../rexos/userspace/stdio.h"
#include "config.h"
#include "app_private.h"
#include "app_nfc.h"

void app_nfc_init(APP *app)
{
#if (APP_DEBUG_NFC)
    printf("NFC init\n");
#endif // APP_NFC_DEBUG
}
