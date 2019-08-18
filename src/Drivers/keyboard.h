#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern void keyboard_init();
extern uint8_t keyboard_enabled();
extern char keyboard_get_key();
extern uint8_t keyboard_to_ascii(uint8_t key);