#include "common.h"
#include "Drivers/VGA.h"
#include "Drivers/keyboard.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with i686"
#endif

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void update_cursor(uint16_t x, uint16_t y)
{
	__asm("mov bx, %0\n"
		"mov ax, %1\n"
		"mov dl, 80\n"
		"mul dl\n"
		"add bx, ax\n"
		"mov dx, 0x03D4\n"
		"mov al, 0x0F\n"
		"out dx, al\n"
		"inc dl\n"
		"mov al, bl\n"
		"out dx, al\n"
		"dec dl\n"
		"mov al, 0x0E\n"
		"out dx, al\n"
		"inc dl\n"
		"mov al, bh\n"
		"out dx, al\n"
		"ret\n"
		:
		: "r" (x), "r" (y)
		: );
}
}

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
}
