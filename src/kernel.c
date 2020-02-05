
#include "common.h"
#include "all_drivers.h"
#include "Drivers/mouse.h"
unsigned int terminal_start;






void kernel_main(void)
{
    gdt_install();
    idt_install();
    irq_install();
    __asm__ __volatile__ ("sti");
	terminal_initialize();
    //isrs_install();
    timer_install(1000);
    //mouse_installer();
    timer_wait(1000);
	terminal_writestr_c("                ooooo      ssss\n", 0xC); timer_wait(128);
    terminal_writestr_c("              oo     oo   ss   \n", 0x7); timer_wait(128);
    terminal_writestr_c("mm  mm  mm    oo     oo    sss \n", 0x9); timer_wait(128);
    terminal_writestr_c("mmmm  mm  mm  oo     oo      ss\n", 0xD); timer_wait(128);
    terminal_writestr_c("mm    mm  mm  oo     oo     ss \n", 0xC); timer_wait(128);
    terminal_writestr_c("mm    mm  mm  oo     oo  ssss  \n", 0x7); timer_wait(128);
    terminal_writestr_c("mm    mm  mm    ooooo          \n\n", 0xF); timer_wait(128);
    char* cmd;
    
    int sec = 1;
    terminal_writestr("Welcome! ");
    terminal_writestr("Wilkommen! ");
    terminal_writestr("Bun venit! ");
    terminal_writestr("Dobro dosli!\n");
    
    timer_wait(2000);
    while(true){
        terminal_writestr("mountainOS> ");
        char* cmd = input();
        terminal_writestr("\n");
        if(strequ(cmd, "hi")){
            terminal_writestr("Hi!\n");
        } else
        if(strequ(cmd, "hello")){
            terminal_writestr("Hi!\n");
        } else
        if(strequ(cmd, "findkey")){
            while(true){
                terminal_writestr(itoa(input_key(), 10));
                terminal_writestr("\n");
            }
        }else
        
        if(strequ(cmd, "crash")){
            itoa(32 / 0, 10);
        } else
        if(strequ(cmd, "shellcodetest")){
            
            void (*ret)() = (int(*)())"\xC7\x05\x00\x80\x0B\x00\x48\x07\x69\x07\xC3";
	        ret();
        } else
        if(strequ(cmd, "timer")){
            while(true){
                terminal_writestr("\n");
				terminal_writestr(itoa(sec, 10));
                timer_wait(1000);
                sec++;
            }
        } else 
        {
            terminal_writestr_c("\ncmd: command not found\n", 0x4F);
        }
    }

}
