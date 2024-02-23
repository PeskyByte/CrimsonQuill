#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "editor.h"
#include "cursor.h"

#include "define.h"

#include "error.h"

char readKey(){
    int nread;
    char c;
    while((nread = read(STDIN_FILENO, &c, 1)) != 1){
        if(nread == -1 && errno != EAGAIN)
            panic("read");
    }
    return c;
}

void processKey(){
    char c = readKey();
    switch(c){
        case CTRL_Q:
            write(STDOUT_FILENO, "\x1b[2J", 4);
            moveCursorToTopLeft();
            exit(0);
            break;
    }
}

void drawRows(){
    for(int y = 0; y < 24;y++){
        write(STDOUT_FILENO, "~\r\n", 3);
    }
}

void refreshScreen(){
    // Because I hate curses

    write(STDOUT_FILENO, "\x1b[2J", 4);
    // \x1b -> escape char (27), [ -> escape sequence, J -> command to clear screen
    // 2 -> argument for J to clear entire screen

    moveCursorToTopLeft();

    drawRows();
    moveCursorToTopLeft();
}