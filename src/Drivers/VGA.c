#include "../all_drivers.h"

inline uint8_t vga_entry_color(uint8_t fg, uint8_t bg)
{
	return fg | bg << 4;
}

inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t)uc | (uint16_t)color << 8;
}


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
	update_cursor(terminal_column, terminal_row);
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*)0xB8000;
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
	if (c == '\n') {
        terminal_row++;
        terminal_column = -1;
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    }
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT){
			terminal_row = 0;
			terminal_initialize();
		}
	}
	if(terminal_row == VGA_HEIGHT){
        terminal_row = 0;
        terminal_initialize();
	}
	update_cursor(terminal_column, terminal_row);
}
void terminal_putcharbehind(char c)
{
    if (c == '\n') {
        terminal_row++;
        terminal_column = -1;
    } else {
        terminal_putentryat(c, terminal_color, terminal_column - 1, terminal_row);
    }
	if (--terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (--terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
	update_cursor(terminal_column, terminal_row);
}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
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

