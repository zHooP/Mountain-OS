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
    // request input
    uint8_t key;
    int c;
    while(true){
        key = 0;
        c = 0;
        while(c < 1023 && key != 0x1C){
            while(!(key = keyboard_read_key())) {}
            if(key == 0xE && c > 0){
                inp[c--] = '\0';
                terminal_putcharbehind('\0');
                continue;
            }
            if(ktoc(key) == 0){
                continue;
            }
            inp[c++] = ktoc(key);
            terminal_putchar(ktoc(key));

        }
        inp[c] = '\0';
        terminal_writestr("\n");
        if(strequ(inp, "mountain") == true)
            terminal_writestr("agreed");
    }

}
