#include <stdint.h>
#include <errno.h>

#include "external.h"
#include "light_wrapper.h"

static int16_t led_states = 0x0;
static int16_t led_blink_states = 0x0;
static int16_t led_pre_blink_states = 0x0;

static int16_t get_led_state_mask(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        return -1;
    }

    return 1 << id - 1;
}

//TODO: Redo
static int16_t is_led_on(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        return -1;
    }

    return led_states & get_led_state_mask(id);
}

static int16_t was_led_on(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        return -1;
    }

    return led_pre_blink_states & get_led_state_mask(id);
}

int16_t is_led_blinking(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        return -1;
    }

    return led_blink_states & get_led_state_mask(id);
}

int8_t set_led_on(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        return -1;
    }

    light_on(id);
    led_states = led_states | get_led_state_mask(id);
    return 0;
}

int8_t set_led_off(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        return -1;
    }

    light_off(id);
    led_states = led_states & ~ get_led_state_mask(id);
    return 0;
}

int8_t led_toggle(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
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
        return -1;
    }

    led_blink_states = led_blink_states & ~ get_led_state_mask(id);
    was_led_on(id) ? set_led_on(id) : set_led_off(id);

    return 0;
}