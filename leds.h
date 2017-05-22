/*
 * leds.h
 *
 *  Created on: 22 мая 2017 г.
 *      Author: RLeonov
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "app.h"
#include "../rexos/userspace/types.h"
#include "config.h"

typedef enum {
    LED_MODE_OFF,
    LED_MODE_BLINK,
    LED_MODE_ON,
    LED_MODE_SMOOTHLY_ON,
    LED_MODE_SMOOTHLY_OFF
} LED_MODE;

typedef struct {
    bool is_on;
    LED_MODE mode;
    int     blink_times;
    uint8_t curr_bright;
    uint8_t need_bright;
} LED;

typedef struct {
    LED led[LED_COUNT];
} LEDS;

void leds_init(APP* app);
void leds_set(APP* app, uint8_t led_channel, LED_MODE mode);



#endif /* LEDS_H_ */
