#include "common.h"
size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int16_t charInStr(char val, char *arr){
	int16_t size = sizeof(*arr) / sizeof(char);
    for (int16_t i=0; i < size; i++) {
        if (arr[i] == val)
            return i;
    }
    return -1;
}

void swap(char *x, char *y){
    char temp = *x;
    *x = *y;
    *y = temp;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(str+start, str+end);
        start++;
        end--;
    }
}

// Implementation of itoa()
char* itoa(int num, int base)
{
    char* str = NULL;
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '\0';
        str[i] = '0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}
bool strequ(char* s1, char* s2){
    if(strlen(s1) != strlen(s2))
        return false;
    for(size_t i = 0; i < strlen(s1); i++){
        if(s1[i] != s2[i])
            return false;
    }
    return true;
}
bool strcontains(char* s, char* key){
    if(strlen(key) > strlen(s))
        return false;

    for (int i = 0; i < strlen(s); i++){
        int j = 0;
        // If the first characters match
        if(s[i] == key[j]){
            int k = i;
            while (s[i] == key[j] && j < strlen(key)){
                j++;
                i++;
            }
            if (j == strlen(key))
                return true;
            else // Re-initialize i to its original value
                i = k;
        }
    }
    return false;
}
void strcpy(char *src, char *dest) {
    int size = strlen(src);
    if (size > 0) {
        int i;
        for (i = 0; i < size - 1 && src[i]; i++) {
             dest[i] = src[i];
        }
        dest[i+1] = '\0';
    }
}


char ktoc(uint8_t key){
    char c = 0;
    uint8_t dict[2][94] = {
        {57,40,51,12,52,53,11,2 ,3, 4, 5, 6, 7, 8, 9, 10,39,13,26,43,27,41,30,48,46,32, 18, 33, 34, 35, 23, 36, 37, 38, 50, 49, 24, 25, 16, 19, 31, 20, 22, 47, 17, 45, 21, 44},
        {32,39,44,45,46,47,48,49,50,51,52,53,54,55,56,57,59,61,91,92,93,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122}
    };
    for(int i = 0; i < 94; i++){
        if(dict[0][i]==key){
            c = (char)dict[1][i];
        }
    }
    return c;
}

char ktocSHIFT(uint8_t key){
    char c = 0;
    uint8_t dict[2][94] = {
        {41, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,26, 27, 43, 39,40,51,52,53,30,48,46,32,18,33,34,35,23,36,37,38,50,49,24,25,16,19,31,20,22,47,17,45,21,44,57},
        {126,33,64,35,36,37,94,38,42,40,41,95,43,123,125,124,58,34,60,62,63,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,32}
    };
    for(int i = 0; i < 94; i++){
        if(dict[0][i]==key){
            c = (char)dict[1][i];
        }
    }
    return c;
}
