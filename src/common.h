#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

int16_t charInStr(char val, char *arr);
void swap(char *x, char *y);
void reverse(char str[], int length);
char* itoa(int num, int base);
char ktoc(uint8_t key);
char ktocSHIFT(uint8_t key);
bool strequ(char* s1, char* s2);
bool strcontains(char* s, char* key);
void strcpy(char *dest, char *src);
