#include <stdint.h>
#include <errno.h>

#define MASK_ERR 0xff
#define STATE_ERR 0xf

#define TIMER_THRESH_0 5
#define TIMER_THRESH_1 20
#define TIMER_BLINK_RATE 5
#define TIMER_BLINK_TIME 300

#define IS_VALID_ID(id) (id >= 1 && id <= 10)

static uint16_t led_states = 0x0;

static uint16_t get_led_state_mask(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        return MASK_ERR;
    }

    uint16_t result = 1 << id - 1;
    return result;
}

static uint8_t is_led_on(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        return STATE_ERR;
    }

    return led_states & get_led_state_mask(id);
}

static uint8_t set_led_on(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        return 0;
    }

    light_on(id);
    led_states = led_states | get_led_state_mask(id);
    return 1;
}

static uint8_t set_led_off(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        return 0;
    }

    light_off(id);
    led_states = led_states & ~ get_led_state_mask(id);
    return 1;
}

static uint8_t led_toggle(int id){
    if(!IS_VALID_ID(id)){
        errno = EIO;
        return 0;
    }

    if (is_led_set(id)){
        return set_led_off(id);
    } else {
        return set_led_on(id);
    }
}

void init(void){
}

void timer(void){
}