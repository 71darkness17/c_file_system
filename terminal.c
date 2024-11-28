#include "terminal.h"
#include "interface.h"
// установка цвета печати в консоли
void set_console_color(enum Color clr) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (clr) {
        case (WHITE): {
            SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); break;
        }
        case (RED): {
            SetConsoleTextAttribute(handle, FOREGROUND_RED); break;
        }
        case (BLUE): {
            SetConsoleTextAttribute(handle, FOREGROUND_BLUE); break;
        }
        case (GREEN): {
            SetConsoleTextAttribute(handle, FOREGROUND_GREEN); break;
        }
        case (CYAN): {
            SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN); break;
        }
    }
}


void set_cursor(int a, int b) {
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = b;
    coordinates.Y = a;
    SetConsoleCursorPosition(handle, coordinates);
}


void print_brackets(Folder * fd, int index) {
    set_cursor(index, 0);
    set_console_color(CYAN);
    printf("[");
    set_cursor(index, (fd->files + index)->name_length + 1);
    printf("]");
    set_console_color(WHITE);
    set_cursor_end(fd);
}

void remove_brackets(Folder * fd, int index) {
    set_cursor(index, 0);
    printf(" ");
    set_cursor(index, (fd->files + index)->name_length + 1);
    printf(" ");
    set_cursor_end(fd);
}

void set_cursor_end(Folder * fd) {
    if (fd->superuser == 1) set_cursor(fd->su_files_counter, 0);
    else set_cursor(fd->loh_files_counter, 0);
}