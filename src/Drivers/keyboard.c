#include "keyboard.h"


void outportb(uint16_t port, uint8_t value)
{
	__asm("mov dx, %0"::"r" (port) : );
	__asm("mov al, %0"::"r" (value) : );
	__asm("out dx, al");
}
uint8_t inportb(uint16_t port)
{
    uint8_t r;
	__asm("mov dx, %0"::"r" (port) : );
	__asm("in al, dx");
	__asm("mov %0, al":"=r" (r)::);
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
	}
    return key_code;
}

