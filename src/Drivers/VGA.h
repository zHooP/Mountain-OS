#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static inline uint8_t vga_entry_color(uint8_t fg, uint8_t bg);
static inline uint16_t vga_entry(unsigned char uc, uint8_t color);
void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestr(const char* data);
void terminal_writestr_c(const char* data, uint8_t color);