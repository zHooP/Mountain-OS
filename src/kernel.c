
#include "common.h"
#include "all_drivers.h"
unsigned int terminal_start;






void kernel_main(void)
{
    terminal_initialize();
    gdt_install();
    idt_install();
    irq_install();
    __asm__ __volatile__ ("sti");
	
    isrs_install();
    timer_install(1000);
    mouse_install();
    initAcpi();
    
	terminal_writestr_c("                ooooo      ssss\n", 0xC); timer_wait(128);
    terminal_writestr_c("              oo     oo   ss   \n", 0x7); timer_wait(128);
    terminal_writestr_c("mm  mm  mm    oo     oo    sss \n", 0x9); timer_wait(128);
    terminal_writestr_c("mmmm  mm  mm  oo     oo      ss\n", 0xD); timer_wait(128);
    terminal_writestr_c("mm    mm  mm  oo     oo     ss \n", 0xC); timer_wait(128);
    terminal_writestr_c("mm    mm  mm  oo     oo  ssss  \n", 0x7); timer_wait(128);
    terminal_writestr_c("mm    mm  mm    ooooo          \n\n", 0xF); timer_wait(128);
    bootbeep();
    char* cmd;
    int sec = 1;
    terminal_writestr("Welcome!");
    terminal_writestr("Wilkommen! ");
    terminal_writestr("Bun venit! ");
    terminal_writestr("Dobro dosli!\n");
    
    timer_wait(500);
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
        if(strequ(cmd, "reboot")){
            uint8_t good = 0x02;
            while (good & 0x02)
                good = inportb(0x64);
            outportb(0x64, 0xFE);
            asm("hlt");
            
        } else
        if(strequ(cmd, "shutdown")){
            acpiPowerOff();
            
        } else
        if(strequ(cmd, "crash")){
            itoa(32 / 0, 10);
        } else
        if(strequ(cmd, "shellcodetest")){
            
            void (*ret)() = (int(*)())"\xC7\x05\x00\x80\x0B\x00\x48\x07\x69\x07\xC3";
	        ret();
        } else
        if(strequ(cmd, "texteater")){
            terminal_writestr("you are now going to play texteater.\n");
            terminal_writestr("eat as much text as you can from the screen to get points.\n");
            terminal_writestr("move with arrow keys and press esc to exit.\n");
            sleep(1000);
            int x=0;
            int y=0;
            
            while(true){

                
                uint8_t key = input_key();
                //terminal_writestr_at(itoa(x,10),2,10);
                //terminal_writestr_at(itoa(y,10),2,11);
                if(key==1){
                    terminal_initialize();
                    break;
                }
                
                if(key==72){
                    
                    y--;
                    terminal_putentryat(' ', 0x00, x,y+1);
                    terminal_putentryat(254, 0x0F, x,y);
                    beep(750,50);
                }
                
                if(key==75){
                    x--;
                    outportb(0x3F8, x);
                    outportb(0x3F8, '\n');
                    terminal_putentryat(' ', 0x00, x+1,y);
                    terminal_putentryat(254, 0x0F, x,y);
                    beep(750,50);
                }
                if(key==80){
                    y++;
                    terminal_putentryat(' ', 0x00, x,y-1);
                    terminal_putentryat(254, 0x0F, x,y);
                    beep(750,50);
                }
                
                if(key==77){
                    x++;
                    outportb(0x3F8, x+'0');
                    outportb(0x3F8, '\n');
                    terminal_putentryat(' ', 0x00, x-1,y);
                    terminal_putentryat(254, 0x0F, x,y);
                    beep(750,50);
                }
                
                
            }
        } else
        if(strequ(cmd, "ascii")||strequ(cmd, "asciitable")){
            terminal_putchar(10);
            for(int i = 0; i<256;i++){
                terminal_putcharnoex(i);
            }
            terminal_putchar(10);
            terminal_putchar(10);
        }else
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
