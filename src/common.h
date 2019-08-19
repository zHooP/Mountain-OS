#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

int16_t charInStr(char val, char *arr);

void swap(char *x, char *y);

void reverse(char str[], int length);

char* itoa(int num, int base);
