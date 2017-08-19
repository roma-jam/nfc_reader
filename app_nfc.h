/*
 * app_nfc.h
 *
 *  Created on: 18 рту. 2017 у.
 *      Author: RLeonov
 */

#ifndef APP_NFC_H_
#define APP_NFC_H_

#include "app.h"
#include "../rexos/userspace/io.h"
#include "../rexos/userspace/stdio.h"
#include "../rexos/userspace/error.h"
#include "../rexos/userspace/process.h"

typedef enum {
    NFC_RESET = IPC_USER,
    NFC_FIELD_ON,
    NFC_FIELD_OFF,
    NFC_DATA_EXCHANGE
} NFC_IPCS;

void app_nfc_init(APP *app);
//void app_nfc_request(APP* app, IO* io);

#endif /* APP_NFC_H_ */
