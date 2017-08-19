/*
 * pn532.h
 *
 *  Created on: 19 рту. 2017 у.
 *      Author: RomaJam
 */

#ifndef PN532_H_
#define PN532_H_

#include "../app.h"
#include "../rexos/userspace/io.h"
#include "pn532_config.h"

typedef enum {
    PN532_STATE_OFF = 0,
    PN532_STATE_IDLE,
    PN532_STATE_ACK,
    PN532_STATE_DATA,
    //PN532_STATE_SLEEP,
    //PN532_STATE_RX,
    //PN532_STATE_TX
} PN532_STATE;

typedef struct {
    IO* io;
    HANDLE handle, user;
    PN532_STATE state;
} PN532;

unsigned int pn532_open_hw(PN532* pn532);
unsigned int pn532_close_hw(PN532* pn532);


#endif /* PN532_H_ */
