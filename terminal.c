#include "terminal.h"

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