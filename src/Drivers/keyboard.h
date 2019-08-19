#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern void keyboard_send_key(uint8_t byt);
extern uint8_t keyboard_read_key();
