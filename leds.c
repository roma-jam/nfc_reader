/*
 * leds.c
 *
 *  Created on: 22 мая 2017 г.
 *      Author: RLeonov
 */

#include "../rexos/userspace/stm32/stm32_driver.h"
#include "../rexos/userspace/pin.h"
#include "../rexos/userspace/htimer.h"
#include "../rexos/userspace/irq.h"
#include "../rexos/userspace/stdio.h"
#include "app_private.h"
#include "leds.h"

void led_iset_value(uint8_t channel, uint8_t value)
{
    switch (channel) {
        case LED_RED_CHANNEL:
            LED_TIM_REG->CCR2 = value;
            break;

        case LED_BLUE_CHANNEL:
            LED_TIM_REG->CCR3 = value;
            break;

        case LED_ORANGE_CHANNEL:
            LED_TIM_REG->CCR4 = value;
            break;
        default:
            break;
    }
}

void led_itoggle(LEDS* leds, uint8_t channel)
{
    if(leds->led[channel].is_on)
        led_iset_value(channel, 0x00);
    else
        led_iset_value(channel, LED_MAX_BRIGHT);

    leds->led[channel].is_on = !leds->led[channel].is_on;
}

static inline void led_irq(int vector, void* param)
{
    LEDS* leds = (LEDS*)param;

    for(uint8_t i = 0; i < LED_COUNT; i++)
    {
        if(leds->led[i].mode == LED_MODE_BLINK)
        {
            if(leds->led[i].blink_times-- > 0)
                led_itoggle(leds, i);
            else
            {
                leds->led[i].mode = LED_MODE_ON;
                // disable blinking htimer
                LED_BLINK_TIM_REG->CR1 &= ~TIM_CR1_CEN;
                LED_BLINK_TIM_REG->SR &= ~TIM_SR_UIF;
            }
        }
    }
    LED_BLINK_TIM_REG->SR &= ~TIM_SR_UIF;
}


void leds_init(APP* app)
{
    pin_enable(LED_RED_PIN, STM32_GPIO_MODE_AF, AF1);
    pin_enable(LED_BLUE_PIN, STM32_GPIO_MODE_AF, AF1);
    pin_enable(LED_ORANGE_PIN, STM32_GPIO_MODE_AF, AF1);

    htimer_open(LED_TIM, 0);
    htimer_setup_channel(LED_TIM, LED_RED_CHANNEL, TIMER_CHANNEL_PWM, 0x00);
    htimer_setup_channel(LED_TIM, LED_BLUE_CHANNEL, TIMER_CHANNEL_PWM, 0x00);
    htimer_setup_channel(LED_TIM, LED_ORANGE_CHANNEL, TIMER_CHANNEL_PWM, 0x00);
    htimer_start(LED_TIM, TIMER_VALUE_US, 8);

    htimer_open(LED_BLINK_TIM, TIMER_IRQ_ENABLE);
    htimer_setup_channel(LED_BLINK_TIM, LED_BLINK_TIM_CHANNEL, TIMER_CHANNEL_GENERAL, 0);

    irq_register(LED_BLINK_IRQ_VECTOR, led_irq, (void*)&app->leds);

    for(uint8_t i = 0; i < LED_COUNT; i++)
    {
        app->leds.led[i].mode = LED_MODE_OFF;
        app->leds.led[i].is_on = false;
        app->leds.led[i].curr_bright = 0x00;
    }
}

void leds_set(APP* app, uint8_t led_channel, LED_MODE mode)
{
    if(led_channel < LED_RED_CHANNEL && led_channel > LED_ORANGE_CHANNEL)
        return;

    switch(mode)
    {
        case LED_MODE_BLINK:
            app->leds.led[led_channel].mode = LED_MODE_BLINK;
            app->leds.led[led_channel].blink_times = (LED_BLINK_TIMES << 1);
            htimer_start(LED_BLINK_TIM, TIMER_VALUE_HZ, LED_BLINK_FREQ_HZ);
            break;

        case LED_MODE_ON:
            app->leds.led[led_channel].mode = LED_MODE_ON;
            app->leds.led[led_channel].is_on = true;
            led_iset_value(led_channel, LED_MAX_BRIGHT);
            break;

        default:
            break;
    }
}
