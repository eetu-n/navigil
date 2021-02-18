#include <stdbool.h>
#include <stdint.h>

#include "external.h"
#include "light_wrapper.h"

bool lights[LED_AMOUNT];
bool buttons[LED_AMOUNT];

void light_on(int id){
    lights[id - 1] = true;
}

void light_off(int id){
    lights[id - 1] = false;
}

bool is_button_pressed(int id){
    return buttons[id - 1];
}

void button_on(int id){
    buttons[id - 1] = true;
}

void button_off(int id){
    buttons[id - 1] = false;
}