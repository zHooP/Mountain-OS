#include "keyboard.h"


void outportb(uint16_t port, uint8_t value)
{
	asm("mov dx, %0"::"r" (port) : );
	asm("mov al, %0"::"r" (value) : );
	asm("out dx, al");
}
uint8_t inportb(uint16_t port)
{
    uint8_t r;
	asm("mov dx, %0"::"r" (port) : );
	asm("in al, dx");
	asm("mov %0, al":"=r" (r)::);
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

char* input(){
    char* input = NULL;
    uint8_t key = 0;
    int i = 0;
    while(key != 0x1C){
        while(key == 0){
            key = keyboard_read_key();
        }
        input[i++] = ktoc(key);
        key = 0;
    }
    input[i++] = '\0';
    return input;
}
