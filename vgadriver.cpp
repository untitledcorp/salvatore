#include "header/vgadriver.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000
#define VGA_COLOR(fg, bg) ((bg << 4) | (fg))

volatile char *vga_buffer = (volatile char *)VGA_MEMORY;
unsigned int cursor_x = 0;
unsigned int cursor_y = 0;

void vga_clear_screen() {
    unsigned int size = VGA_WIDTH * VGA_HEIGHT;
    for (unsigned int i = 0; i < size; i++) {
        vga_buffer[i * 2] = ' ';
        vga_buffer[i * 2 + 1] = VGA_COLOR(7, 0);
    }
    cursor_x = cursor_y = 0;
}

void vga_print_char(char c, unsigned char color) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        unsigned int index = (cursor_y * VGA_WIDTH + cursor_x) * 2;
        vga_buffer[index] = c;
        vga_buffer[index + 1] = color;
        cursor_x++;
    }

    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= VGA_HEIGHT) {
        cursor_y = 0;
    }
}

void vga_print(const char *str) {
    while (*str) {
        vga_print_char(*str++, VGA_COLOR(7, 0));
    }
}
