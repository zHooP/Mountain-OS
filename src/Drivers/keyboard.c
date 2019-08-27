#include "keyboard.h"
#include "../common.h"
#include "VGA.h"

void outportb(uint16_t port, uint8_t value)
{
	asm("mov dx, %0"::"r" (port) : );
	asm("mov al, %0"::"r" (value) : );
	asm("out dx, al");
}
uint8_t inportb(uint16_t port)
{
	asm("mov dx, %0"::"r" (port) : );
	asm("in al, dx");
	register uint8_t r asm("al");
    return r;
}

void keyboard_send_key(uint8_t b){
    outportb(0x64, b);
}

uint8_t keyboard_read_key()
{
    uint8_t key_code = 0;
	if (inportb(0x64) & 1){
        key_code = inportb(0x60);
        while(key_code==0){}
        return key_code;
	}
    return 0;
}
uint8_t input_key(){
    uint8_t key;
    while(!(key = keyboard_read_key())) {}
    return key;
}
char input_char(){
    uint8_t key;
    while(!(key = keyboard_read_key())) {}
    return ktoc(key);
}

char* input(){
    uint8_t key = 0;
    int c = 0;
    while(key != 0x1C){
        while(!(key = keyboard_read_key())) {}
        if(key == 0xE && c > 0){
            inp[c--] = '\0';
            terminal_putcharbehind('\0');
            continue;
        }
        if(key == 0)
        if(key == 0x2A){
            while(true){
                while(!(key = keyboard_read_key())) {}
                if(key == 0xAA)
                    break;
                if(key == 0xE && c > 0){
                    inp[c--] = '\0';
                    terminal_putcharbehind('\0');
                    continue;
                }
                if(ktocSHIFT(key) == 0){
                    continue;
                }
                inp[c++] = ktocSHIFT(key);
                terminal_putchar(ktocSHIFT(key));
            }
        }
        if(ktoc(key) == 0){
            continue;
        }
        inp[c++] = ktoc(key);
        terminal_putchar(ktoc(key));


    }
    inp[c] = '\0';
    return inp;
}
