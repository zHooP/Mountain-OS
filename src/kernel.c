#include "common.h"
#include "Drivers/VGA.h"
#include "Drivers/keyboard.h"


#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with i686"
#endif


void kernel_main(void)
{
	terminal_initialize();
	terminal_writestr_c("                ooooo      ssss\n", 0xC);
    terminal_writestr_c("              oo     oo   ss   \n", 0x7);
    terminal_writestr_c("mm  mm  mm    oo     oo    sss \n", 0x9);
    terminal_writestr_c("mmmm  mm  mm  oo     oo      ss\n", 0xD);
    terminal_writestr_c("mm    mm  mm  oo     oo     ss \n", 0xC);
    terminal_writestr_c("mm    mm  mm  oo     oo  ssss  \n", 0x7);
    terminal_writestr_c("mm    mm  mm    ooooo          \n\n", 0xF);
    terminal_writestr("Welcome! Wilkommen! Bun venit! Dobro dosli!\n");

    // this is a test

    char inp[1024];
    char c;
    uint8_t key = 0;
    int i = 0;
    while(true){
        while(true){
            key = keyboard_read_key();
            terminal_writestr(itoa(key,10));
            if(key != 0)
                break;
        }
        if(key == 0x1C)
            break;
        c = ktoc(key);
        inp[i++] = (char)c;
        key = 0;
    }
    inp[i++] = '\0';
    terminal_writestr(inp);

}
