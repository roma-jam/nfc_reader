/*
 * app_ccid.h
 *
 *  Created on: 23 мая 2017 г.
 *      Author: RLeonov
 */

#ifndef APP_CCID_H_
#define APP_CCID_H_


#include "app.h"
#include "../rexos/userspace/ipc.h"
#include "sys_config.h"

void app_ccid_request(APP* app, IPC* ipc);
void app_ccid_response(APP* app, IPC* ipc);
void app_ccid_notify_slot_change(APP* app, unsigned int state);


#endif /* APP_CCID_H_ */
