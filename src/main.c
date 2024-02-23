#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "terminalMode.h"
#include "editor.h"

int main() {

    atexit(disableRawMode);
    enableRawMode();

    while(1){
        refreshScreen();
        processKey();  
    }
    return 0;
}