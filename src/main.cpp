#include <iostream>
#include "rawmode.h"
#include "define.h"
int main(){
    enableRawMode();

    while(1){ //read 1 byte form std input until there is no more bytes
        char c = '\0'; 
        if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
            panic("read");

        if(iscntrl(c)){
            std::cout << int(c) << "\r\n";
        }
        else{
            std::cout << int(c) << " (" << c << ")" << "\r\n";
        }
        if(int(c) == CTRL_X){
            break;
        }
    }
    atexit(disableRawMode);
    return 0;
}