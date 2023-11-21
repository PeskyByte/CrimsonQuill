#include <iostream>
#include "rawmode.h"

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
        if(int(c) == 24){
            break;
        }
    }
    std::cout<<"bye bye\n";
    atexit(disableRawMode);
    return 0;
}