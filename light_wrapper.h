#include <stdint.h>

#ifndef LIGHT_WRAPPER_H
#define LIGHT_WRAPPER_H
#pragma once

// At most 15
#define LED_AMOUNT 10

#define TIMER_THRESH_0 5
#define TIMER_THRESH_1 20
#define TIMER_BLINK_RATE 5
#define TIMER_BLINK_TIME 300

#define IS_VALID_ID(id) (id >= 1 && id <= LED_AMOUNT)

uint16_t led_timers[LED_AMOUNT];
uint16_t button_timers[LED_AMOUNT];

int8_t set_led_on(int id);
int8_t set_led_off(int id);
int8_t led_toggle(int id);
int8_t led_start_blinking(int id);
int8_t led_stop_blinking(int id);
int16_t is_led_blinking(int id);

#endif