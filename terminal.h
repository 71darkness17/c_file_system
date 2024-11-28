#ifndef TERMINAL_H
#define TERMINAL_H
#include <Windows.h>
#include <stdio.h>

// структурка для задания цвета
enum Color {
    RED, BLUE, GREEN, CYAN, WHITE
};

void set_cursor(int a, int b);
void print_brackets(Folder * fd, int index);
void remove_brackets(Folder * fd, int index);
void set_console_color(enum Color clr);
void set_cursor_end(Folder * fd);
#endif