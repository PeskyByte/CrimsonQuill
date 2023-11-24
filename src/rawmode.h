#pragma once
#include <unistd.h>  // syscalls
#include <termios.h> // terminal I/O interface
#include "error.h"

struct termios original_termios;

/* Enbale terminal raw mode */
void enableRawMode(){
    if(tcgetattr(STDIN_FILENO, &original_termios) == -1) 
        panic("tcgetattr"); 
    
    struct termios raw = original_termios;

    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8); //set the char size to 8 bits, this is prob a default
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); 
    /* clearing specific bits from bitset c_lflag, we want to do the processing for these shortcuts
       ISIG -> ctrl-c, ctrl-z
       IXON -> ctrl-s, ctrl-q;
       IEXTEN -> ctrl-v
       ICRNL -> ctrl-m, turns off translation of carriage return to new line
       OPOST -> \n != \r\n
       INPCK -> parity checking, prob off by default
    */
    raw.c_cc[VMIN] = 0; // set minimum number of bytes of input needed before read() can return.
    raw.c_cc[VTIME] = 1; // set the maximum amount of time to wait before read() returns. It is in tenths of a second.

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        panic("tcsetattr"); /* apply terminal attr to it
     TCSAFLUSH --> to apply changes after writing all pending output, ignore leftover */

}

/* Returns terminal attributes to default */
void disableRawMode(){
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios) == -1)
        panic("tcsetattr");
}