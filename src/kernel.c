#include "Drivers/multiboot.h"
#include "common.h"
#include "all_drivers.h"
unsigned int terminal_start;

//

 








//

void kernel_main(multiboot_info_t* mbd, unsigned int magic)
{
    terminal_initialize();
    gdt_install();
    idt_install();
    irq_install();
    __asm__ __volatile__ ("sti");
	
    isrs_install();
    timer_install(1000);
    mouse_install(); // only used to stop OS from hanging at mouse input
    initAcpi();
    
	print_c("                ooooo      ssss\n", 0xC); timer_wait(128);
    print_c("              oo     oo   ss   \n", 0x7); timer_wait(128);
    print_c("mm  mm  mm    oo     oo    sss \n", 0x9); timer_wait(128);
    print_c("mmmm  mm  mm  oo     oo      ss\n", 0xD); timer_wait(128);
    print_c("mm    mm  mm  oo     oo      ss \n", 0xC); timer_wait(128);
    print_c("mm    mm  mm  oo     oo  ssss  \n", 0x7); timer_wait(128);
    print_c("mm    mm  mm    ooooo          \n\n", 0xF); timer_wait(128);
    bootbeep();
    char* cmd;
    int sec = 1;
    print("Welcome!");
    print("Wilkommen! ");
    print("Bun venit! ");
    print("Dobro dosli!\n");
    
    timer_wait(500);
    while(true){
        print("mountainOS> ");

        char* cmd = input();
        print("\n");
        if(strequ(cmd, "hi")){
            print("Hi!\n");
        } else
        if(strequ(cmd, "hello")){
            print("Hi!\n");
        } else
        if(strequ(cmd, "findkey")){
            while(true){
                print(itoa(input_key(), 10));
                print("\n");
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
            print("you are now going to play texteater.\n");
            print("eat as much text as you can from the screen to get points.\n");
            print("move with arrow keys and press esc to exit.\n");
            sleep(1000);
            int x=0;
            int y=0;
            
            while(true){

                
                uint8_t key = input_key();
                //print_at(itoa(x,10),2,10);
                //print_at(itoa(y,10),2,11);
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
        if(strequ(cmd, "sysinfo")){
            //


            //
            print("\nSeconds since boot: ");
            print(itoa(get_timer_ticks()/1000,10));
            print("\nACPI Shutdown available: ");
            if(shutdownSupported()){
                print("yes");
            } else {
                print("no");
            }
            print("\nTotal memory: ");
            print(itoa(mbd->mmap_addr,10));
            print(" KiB\n");
            print("Time and date: ");
            rtc_print_formatted_time();
            print("\n\n");
            
        }else
        if(strequ(cmd, "rtc")||strequ(cmd, "time")||strequ(cmd, "date")){
            
            rtc_print_formatted_time();
            print("\n\n");


        }else
        if(strequ(cmd, "timer")){
            while(true){
                uint8_t key = keyboard_read_key();
                if(key==1){
                    sec=0;
                    break;
                }
                
				print(itoa(sec, 10));
                print("\n");
                timer_wait(1000);
                sec++;
            }
        } else 
        {
            print_c("\ncmd: command not found\n", 0x4F);
        }
    }

}
