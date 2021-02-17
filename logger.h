#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

void print_log(const char* tag, const char* message, va_list args);

#endif