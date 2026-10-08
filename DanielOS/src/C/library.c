#include "library.h"
int cursorx = 0;
int cursory = 0;
char characters[1920];         
char *ptr_char = characters;  //It's like &characters[0];
int count = 0;
void printf_hex8(uint8_t val){
    char hex_chars[] = "0123456789ABCDEF";
    char buffer[5];
    buffer[0] = '0';
    buffer[1] = 'x';
    buffer[2] = hex_chars[(val >> 4) & 0x0F];
    buffer[3] = hex_chars[val & 0x0F];
    buffer[4] = '\0';
    printf(buffer);

}
void printf_hex32(uint32_t val)
{
    char hex_chars[] = "0123456789ABCDEF";
    char buffer[11];

    buffer[0] = '0';
    buffer[1] = 'x';

    for (int i = 0; i < 8; i++)
    {
        int shift = 28 - i * 4;
        buffer[2 + i] = hex_chars[(val >> shift) & 0xF];
    }

    buffer[10] = '\0';

    printf(buffer);
}
void printf_hex64(uint64_t val)
{
    char hex_chars[] = "0123456789ABCDEF";
    char buffer[19];

    buffer[0] = '0';
    buffer[1] = 'x';

    for (int i = 0; i < 16; i++)
    {
        int shift = 60 - i * 4;
        buffer[2 + i] = hex_chars[(val >> shift) & 0xF];
    }

    buffer[18] = '\0';

    printf(buffer);
}
void printf_int64(uint64_t val){
    int rest;
    int number = val;
    char buffer[8];
    int i = 0;
    while(number > 0){
        rest = number % 10;
        buffer[i] = '0' + rest;
        number = number / 10;
        i++;

    }
    buffer[i + 1] = '\0';
    printf(buffer);

}



void printf_letter(uint8_t scancode){
    char kbd_de[128] = {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'ß', '´', '\b',
        '\t', 'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', '#', '+', '\n',
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'ö', 'ä', '^', 0, '<',
        'y', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0,
        0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0
    };   
    char ascii_char = kbd_de[scancode];
    if (ascii_char != 0) {
        char buffer[2];
        buffer[0] = ascii_char;
        buffer[1] = '\0';
        printf(buffer);
    }
    *ptr_char = ascii_char;
    ptr_char++;
    *ptr_char = '\0';
    count++;

        


}
void print_input(void) {
    char *video_memory = (char *)0xB8000;
    int offset = ((cursory + 5) * 80 + cursorx) * 2;

    for (int i = 0; characters[i] != '\0'; i++) {
        video_memory[offset + i * 2]     = characters[i];
        video_memory[offset + i * 2 + 1] = 0x0F;  // Farbe
    }
}
void printf_letters_shift(uint8_t scancode){
    char kbd_de_shift[128] = {
        0,  0,  '!', '"', '§', '$', '%', '&', '/', '(', ')', '=', '?', '`', 0,
        0,  'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', 'Ü', '*', 0,
        0,  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Ö', 'Ä', '\'', 0,
        '>', 'Y', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', 0, '*', 0, ' ', 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    char ascii_char = kbd_de_shift[scancode];
    if (ascii_char != 0) {
        char buffer[2];
        buffer[0] = ascii_char;
        buffer[1] = '\0';
        printf(buffer);
        }
    *ptr_char = ascii_char;
    ptr_char++;
    *ptr_char = '\0';
    count++;
}

int length(char *text)
{
    int j = 0;

    while (*text != '\0')
    {
        text++;
        j++;
    }

    return j;
}

void title(void){
    char *video_memory = (char *)0xB8000;
    int offset = ((cursory) * 80) * 2;
    char username[] = "$daniel$";
    for (int x = 0; x < length("$daniel$");x++){
        video_memory[offset + 2*x] = username[x];
        video_memory[offset + 2 * x + 1] = 0x02;
    }
}

void clear_screen(void)
{
    char *video_memory = (char *)0xB8000;
    cursorx = 0;
    cursory = 0;

    for (int i = 0; i < 80 * 25; i++)
    {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = 0x07;
    }
}

void printf(char word[])
{
    int offset = (cursory * 80 + (cursorx + 10)) * 2;
    char *video_memory = (char *)0xB8000;
    for (int x = 0; x < length(word); x++)
    {
        if (word[x] != '\n'){
            video_memory[offset + 2 * x] = word[x];
            video_memory[offset + 2 * x + 1] = 0x02;
            cursorx++;
        }
        else {
            cursorx = 0;
            cursory++;
        }

    
    }

        
    if (cursorx >= 80){
        cursorx = 0;
        cursory++;
    }
    
}

void *memset(void *word, int value, size_t times)
{
    unsigned char *ptr = word;

    for (size_t i = 0; i < times; i++)
    {
        *ptr = (unsigned char)value;
        ptr++;
    }

    return word;
}

//COMMANDSCMD
void check_range_array(char array[], int start, int end, char word[]){
    for (int i = start; i < end; i++){
        if (array[i] == word[0]){
            printf("Found some stuff here");
        }
    }

}

void printf_output(char word[])
{
    int offset = (cursory * 80 + (cursorx)) * 2;
    char *video_memory = (char *)0xB8000;
    for (int x = 0; x < length(word); x++)
    {
        if (word[x] != '\n'){
            video_memory[offset + 2 * x] = word[x];
            video_memory[offset + 2 * x + 1] = 0x02;

        }
        else {
            cursorx = 0;
            cursory++;
        }

    
    }

        
    if (cursorx >= 80){
        cursorx = 0;
        cursory++;
    }
    
}

void cmd_commands(void)
{
    if (count == 0)
        return;

    // echo
    if (count >= 4 &&
        characters[0] == 'e' &&
        characters[1] == 'c' &&
        characters[2] == 'h' &&
        characters[3] == 'o')
    {
        cursorx = 0;
        printf_output("Hello");
        printf("\n");
        return;
    }

    // about
    if (count >= 5 &&
        characters[0] == 'a' &&
        characters[1] == 'b' &&
        characters[2] == 'o' &&
        characters[3] == 'u' &&
        characters[4] == 't')
    {
        cursorx = 0;
        printf_output("This is an OS made by Daniel");
        printf("\n");
        return;
    }
    if (count >= 5 &&
        characters[0] == 'c' &&
        characters[1] == 'l' &&
        characters[2] == 'e' &&
        characters[3] == 'a' &&
        characters[4] == 'r')
    {
        clear_screen();
        return;
    }
    if (count >= 7
        && characters[0] == 'r' 
        && characters[1] == 'a' 
        && characters[2] == 'm' 
        && characters[3] == ' ' 
        && characters[4] == 'f'
         && characters[5] == 'r'
         && characters[6] == 'e' 
        && characters[7] == 'e'){
            uint64_t available_memory(uint32_t multiboot_addr);
            return;
        }


    cursorx = 0;
    printf_output("This command does not exist");
    printf("\n");
}