#ifndef DRIVER_H
#define DRIVER_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000
#define VGA_COLOR(fg, bg) ((bg << 4) | (fg))

extern volatile char *vga_buffer;

extern unsigned int cursor_x;
extern unsigned int cursor_y;

void vga_clear_screen(void);
void vga_print_char(char c, unsigned char color);
void vga_print(const char *str);

#endif
