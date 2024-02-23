#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cursor.h"
#include "error.h"
void panic(const char *errorType){
    write(STDOUT_FILENO, "\x1b[2J", 4); // Clear screen
    moveCursorToTopLeft();
    perror(errorType);
    exit(1);
}