#include <unistd.h>
#include "cursor.h"

void moveCursorToTopLeft(){
    write(STDOUT_FILENO, "\x1b[H", 3);
}