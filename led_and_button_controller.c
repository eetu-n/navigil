#include <stdint.h>
#include <errno.h>

#include "external.h"
#include "light_wrapper.h"

static int8_t handle_button_press(int id){
    if(button_timers[id] < TIMER_THRESH_0){
        return 0;
    } else if(button_timers[id] >= TIMER_THRESH_0 && button_timers[id] < TIMER_THRESH_1) {
        led_toggle(id);
        return 0;
    } else {
        led_start_blinking(id);
        return 0;
    }
}

void init(void){
    for(int i = 1; i <= LED_AMOUNT; i++){
        led_stop_blinking(i);
        set_led_off(i);
        led_timers[i] = 0;
        button_timers[i] = 0;
    }
}

void timer(void){
    for(int i = 1; i <= LED_AMOUNT; i++){
        if(is_led_blinking(i)){
            led_timers[i]++;
            if(led_timers[i] % TIMER_BLINK_RATE == 0) led_toggle(i);
            if(led_timers[i] >= TIMER_BLINK_TIME) led_stop_blinking(i);
            continue;
        }

        if(is_button_pressed(i)){
            button_timers[i]++;
        } else {
            handle_button_press(i);
            button_timers[i] = 0;
        }
    }
}