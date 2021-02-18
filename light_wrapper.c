#include <stdint.h>
#include <errno.h>

#include "external.h"
#include "light_wrapper.h"

#ifdef DEBUG
#include "logger.h"
#endif

static int16_t led_states = 0x0;
static int16_t led_blink_states = 0x0;
static int16_t led_pre_blink_states = 0x0;

static int16_t get_led_state_mask(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        #ifdef DEBUG
        print_log("FATAL", "IO Error in get_led_state_mask: got %d, expected in range 1-%d\n", id, LED_AMOUNT);
        #endif
        return -1;
    }

    return 1 << (id - 1);
}

int8_t is_led_on(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        #ifdef DEBUG
        print_log("FATAL", "IO Error in is_led_on: got %d, expected in range 1-%d\n", id, LED_AMOUNT);
        #endif
        return -1;
    }

    return (int8_t) (led_states & get_led_state_mask(id)) >> (id - 1);
}

static int8_t was_led_on(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        #ifdef DEBUG
        print_log("FATAL", "IO Error in was_led_on: got %d, expected in range 1-%d\n", id, LED_AMOUNT);
        #endif
        return -1;
    }

    return (int8_t) (led_pre_blink_states & get_led_state_mask(id)) >> (id - 1);
}

int8_t is_led_blinking(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        #ifdef DEBUG
        print_log("FATAL", "IO Error in is_led_blinking: got %d, expected in range 1-%d\n", id, LED_AMOUNT);
        #endif
        return -1;
    }

    return (int8_t) (led_blink_states & get_led_state_mask(id)) >> (id - 1);
}

int8_t set_led_on(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        #ifdef DEBUG
        print_log("FATAL", "IO Error in set_led_on: got %d, expected in range 1-%d\n", id, LED_AMOUNT);
        #endif
        return -1;
    }

    light_on(id);
    led_states = led_states | get_led_state_mask(id);
    return 0;
}

int8_t set_led_off(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        #ifdef DEBUG
        print_log("FATAL", "IO Error in set_led_off: got %d, expected in range 1-%d\n", id, LED_AMOUNT);
        #endif
        return -1;
    }

    #if DEBUG >= 3
    print_log("DEBUG", "Setting LED %d off", id);
    #endif

    light_off(id);
    led_states = led_states & ~ get_led_state_mask(id);
    return 0;
}

int8_t led_toggle(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        #ifdef DEBUG
        print_log("FATAL", "IO Error in led_toggle: got %d, expected in range 1-%d\n", id, LED_AMOUNT);
        #endif
        return -1;
    }

    if (is_led_on(id)){
        return set_led_off(id);
    } else {
        return set_led_on(id);
    }
}

int8_t led_start_blinking(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        #ifdef DEBUG
        printf("IO Error in led_start_blinking: got %d, expected in range 1-%d\n", id, LED_AMOUNT);
        #endif
        return -1;
    }

    led_timers[id] = 0;
    led_pre_blink_states = led_pre_blink_states | (get_led_state_mask(id) & led_states);
    led_blink_states = led_blink_states | get_led_state_mask(id);
    return 0;
}

int8_t led_stop_blinking(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        #ifdef DEBUG
        printf("IO Error in led_stop_blinking: got %d, expected in range 1-%d\n", id, LED_AMOUNT);
        #endif
        return -1;
    }

    led_blink_states = led_blink_states & ~ get_led_state_mask(id);
    was_led_on(id) ? set_led_on(id) : set_led_off(id);

    return 0;
}