#include "rawmode.h"
#include "define.h"
#include "editorProcessing.h"
int main(){
    enableRawMode();

    while(1){
        processKey();
    }
    atexit(disableRawMode);
    return 0;
}