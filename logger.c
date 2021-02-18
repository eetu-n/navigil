#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "logger.h"

void print_log(const char* tag, const char* message, ...) {
    va_list args;
    va_start(args, message);
    time_t now;
    time(&now);

    printf("%s [%s] ", ctime(&now), tag);
    vprintf(message, args);
    va_end(args);
    printf("\n");
}
