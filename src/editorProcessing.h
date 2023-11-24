#pragma once
#include <unistd.h>
#include "error.h"
#include "define.h"
char readKey(){
    char c;
    int read_stat;
    while((read_stat = read(STDIN_FILENO, &c, 1)) != 1){
        if(read_stat == -1 && errno != EAGAIN)
            panic("read");
    }
    return c;
}
void processKey(){
    char c = readKey();
    switch(int(c)){
        case CTRL_Q:
            exit(0);
            break;        
    }
}