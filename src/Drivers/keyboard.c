#include "keyboard.h"
#include "../common.h"

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

// working on it (preview in kernel)

/*char* input(){
    uint8_t key = 0;
    int c = 0;
    while(c < 1023 && key != 0x1C){
        while(!(key = keyboard_read_key())) {}
        if(ktoc(key) == 0){
            outportb(0x3F8, '/');
            continue;
        }
        outportb(0x3F8, ktoc(key));
        inp[c++] = ktoc(key);
        terminal_writestr(&inp[c-1]);

    }
    inp[c] = '\0';
    return inp;
}*/
