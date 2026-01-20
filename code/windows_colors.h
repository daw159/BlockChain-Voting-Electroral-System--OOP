#ifndef WINDOWS_COLORS_H
#define WINDOWS_COLORS_H

// Enable ANSI colors for Windows CMD
#ifdef _WIN32
#include <windows.h>
void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#else
void enableANSI() {} // Do nothing on Linux/Mac
#endif

#endif
