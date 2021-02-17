#include <stdint.h>
#include <errno.h>

#include "led_and_button_controller.h"
#include "external.h"
#include "light_wrapper.h"

#ifdef DEBUG
#include "logger.h"
#endif

static int8_t handle_button_press(int id){
    if(button_timers[id] < TIMER_THRESH_0){
        #if DEBUG >= 3
        if (button_timers[id] <= 0)
            print_log("DEBUG",
                "Button %d released with time = %d ms, under threshold 0 (%d ms)", 
                id,
                button_timers[id] * TIMER_RATE,
                TIMER_THRESH_0);
        #endif
        return 0;
    } else if(button_timers[id] >= TIMER_THRESH_0 && button_timers[id] < TIMER_THRESH_1) {
        led_toggle(id);
        #if DEBUG >= 3
        print_log("DEBUG",
            "Button %d released with time = %d ms, between thresholds 0, 1 (%d, %d ms), toggling light",
            id,
            button_timers[id] * TIMER_RATE,
            TIMER_THRESH_0 * TIMER_RATE,
            TIMER_THRESH_1 * TIMER_RATE);
        #endif
        return 0;
    } else {
        led_start_blinking(id);
        #if DEBUG >= 3
        print_log("DEBUG",
            "Button %d released with time = %d ms, above threshold 1(%d ms), starting blink cycle",
            id,
            button_timers[id] * TIMER_RATE,
            TIMER_THRESH_1 * TIMER_RATE);
        #endif
        return 0;
    }
}

void init(void){
    for(int i = 1; i <= LED_AMOUNT; i++){
        #if DEBUG >= 2
        print_log("INFO", "Initializing");
        #endif
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
            #if DEBUG >= 3
            print_log("DEBUG", "Button %d is pressed", id);
            #endif
            button_timers[i]++;
        } else {
            #if DEBUG >= 3
            print_log("DEBUG", "Button %d is not pressed", id);
            #endif
            handle_button_press(i);
            button_timers[i] = 0;
        }
    }
}