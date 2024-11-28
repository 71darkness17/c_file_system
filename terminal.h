#ifndef TERMINAL_H
#define TERMINAL_H
#include <Windows.h>
#include <stdio.h>

// структурка для задания цвета
enum Color {
    RED, BLUE, GREEN, CYAN, WHITE
};

void set_console_color(enum Color clr);
#endif