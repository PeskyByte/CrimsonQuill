#include <unistd.h>
#include <termios.h>
#include "terminalMode.h"
#include "error.h"
struct termios originalConfig;

/* Enbale terminal raw mode */
void enableRawMode(){
    if(tcgetattr(STDIN_FILENO, &originalConfig) == -1) 
        panic("tcgetattr"); 
    
    struct termios rawConfig = originalConfig;

    rawConfig.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    rawConfig.c_oflag &= ~(OPOST);
    rawConfig.c_cflag |= (CS8); //set the char size to 8 bits, this is prob a default
    rawConfig.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); 
    /* clearing specific bits from bitset c_lflag, we want to do the processing for these shortcuts
       ISIG -> ctrl-c, ctrl-z
       IXON -> ctrl-s, ctrl-q;
       IEXTEN -> ctrl-v
       ICRNL -> ctrl-m, turns off translation of carriage return to new line
       OPOST -> \n != \r\n
       INPCK -> parity checking, prob off by default
    */
    rawConfig.c_cc[VMIN] = 0; // set minimum number of bytes of input needed before read() can return.
    rawConfig.c_cc[VTIME] = 1; // set the maximum amount of time to wait before read() returns. It is in tenths of a second.

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawConfig) == -1)
        panic("tcsetattr"); /* apply terminal attr to it
     TCSAFLUSH --> to apply changes after writing all pending output, ignore leftover */

}

/* Returns terminal attributes to default */
void disableRawMode(){
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalConfig) == -1)
        panic("tcsetattr");
}