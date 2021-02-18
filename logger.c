#include <time.h>
#include <stdio.h>

#include "logger.h"

void print_log(const char* tag, const char* message, ...) {
    va_list args;
    time_t now;
    time(&now);

    printf("%s [%s] ", ctime(&now), tag);
    printf(message, args);
    printf("\n");
}