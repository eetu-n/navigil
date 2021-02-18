#ifndef EXTERNAL_H
#define EXTERNAL_H
#pragma once

#include <stdbool.h>

void light_on(int id);
void light_off(int id);

bool is_button_pressed(int id);


//For testing
void button_on(int id);
void button_off(int id);

#endif