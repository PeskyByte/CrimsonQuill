#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "error.h"
void panic(const char *errorType){
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    perror(errorType);
    exit(1);
}