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

void app_nfc_init(APP *app);
void app_nfc_request(APP* app, IO* io);

#endif /* APP_NFC_H_ */
