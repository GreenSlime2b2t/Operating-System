#ifndef LIBRARY_H
#define LIBRARY_H
extern int cursorx;
extern int cursory;
extern char characters[1920];
extern char *ptr_char;
extern int count;
typedef unsigned char      uint8_t;   // 8 Bit  (0–255)
typedef unsigned short     uint16_t;  // 16 Bit (0–65535)
typedef unsigned int       uint32_t;  // 32 Bit
typedef unsigned long long uint64_t;  // 64 Bit

typedef signed char        int8_t;
typedef signed short       int16_t;
typedef signed int         int32_t;
typedef signed long long   int64_t;   

typedef unsigned int size_t;
void print_input(void);
void printf_hex8(uint8_t val);
void printf_hex32(uint32_t val);
void printf_hex64(uint64_t val);
void printf_int64(uint64_t val);
void check_range_array(char array[], int start, int end, char word[]);
void cmd_commands(void);
void printf_output(char word[]);

int length(char *text);

void printf(char word[]);

void *memset(void *word, int value, size_t times);
void printf_letters_shift(uint8_t scancode);
void printf_letter(uint8_t scancode);

void clear_screen(void);

void title(void);


#endif