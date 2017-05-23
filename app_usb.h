/*
 * app_usb.h
 *
 *  Created on: 23 мая 2017 г.
 *      Author: RLeonov
 */

#ifndef APP_USB_H_
#define APP_USB_H_

#include "app.h"
#include "../rexos/userspace/ipc.h"

void app_usb_init(APP* app);
void app_usb_request(APP* app, IPC* ipc);

#endif /* APP_USB_H_ */
