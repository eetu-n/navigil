#include <stdint.h>

#ifndef LIGHT_WRAPPER_H
#define LIGHT_WRAPPER_H
#pragma once

// At most 15
#ifndef LED_AMOUNT
#define LED_AMOUNT 10
#endif

#ifndef TIMER_THRESH_0
#define TIMER_THRESH_0 5
#endif
#ifndef TIMER_THRESH_1
#define TIMER_THRESH_1 20
#endif
#ifndef TIMER_BLINK_RATE
#define TIMER_BLINK_RATE 5
#endif
#ifndef TIMER_BLINK_TIME
#define TIMER_BLINK_TIME 300
#endif
#ifndef TIMER_RATE
#define TIMER_RATE 100
#endif

#define IS_VALID_ID(id) (id >= 1 && id <= LED_AMOUNT)

uint16_t led_timers[LED_AMOUNT];
uint16_t button_timers[LED_AMOUNT];

int8_t set_led_on(int id);
int8_t set_led_off(int id);
int8_t led_toggle(int id);
int8_t led_start_blinking(int id);
int8_t led_stop_blinking(int id);
int8_t is_led_blinking(int id);

#endif