#include "common.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with i686"
#endif

/* Hardware text mode color constants. */

#define VGA_COLOR_BLACK 0
#define VGA_COLOR_BLUE 1
#define VGA_COLOR_GREEN 2
#define VGA_COLOR_CYAN 3
#define VGA_COLOR_RED 4
#define VGA_COLOR_MAGENTA 5
#define VGA_COLOR_BROWN 6
#define VGA_COLOR_LIGHT_GREY 7
#define VGA_COLOR_DARK_GREY 8
#define VGA_COLOR_LIGHT_BLUE 9
#define VGA_COLOR_LIGHT_GREEN 10
#define VGA_COLOR_LIGHT_CYAN 11
#define VGA_COLOR_LIGHT_RED 12
#define VGA_COLOR_LIGHT_MAGENTA 13
#define VGA_COLOR_LIGHT_BROWN 14
#define VGA_COLOR_WHITE 15


static inline uint8_t vga_entry_color(uint8_t fg, uint8_t bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}


static const uint8_t VGA_WIDTH = 80;
static const uint8_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;



void update_cursor(uint16_t x, uint16_t y)
{
	asm("mov bx, %0\n"
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
		:);
}



void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		if(data[i] == '\n'){
			terminal_row++;
			terminal_column = 0;
		}
		else{
			terminal_putchar(data[i]);
		}
}

void terminal_writestr(const char* data)
{
	terminal_write(data, strlen(data));
	update_cursor(terminal_column, terminal_row);
}
void terminal_writestr_c(const char* data, uint8_t color)
{
	terminal_color = color;
	terminal_write(data, strlen(data));
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	update_cursor(terminal_column, terminal_row);
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
    terminal_writestr("Welcome! Wilkommen! Bun venit! Dobro dosli!");

}
