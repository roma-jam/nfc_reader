/*
    RExOS - embedded RTOS
    Copyright (c) 2011-2016, Alexey Kramarenko
    All rights reserved.
*/

#ifndef APP_PRIVATE_H
#define APP_PRIVATE_H

#include "app.h"
#include "../rexos/userspace/types.h"
#include "../rexos/userspace/ipc.h"
#include "leds.h"

typedef enum {
    HAL_NFC = HAL_APP
} HAL_APP_GROUPS;

typedef struct _APP {
    HANDLE usbd;
    bool usb_started;

    HANDLE nfc;

    LEDS leds;
} APP;

#endif // APP_PRIVATE_H
