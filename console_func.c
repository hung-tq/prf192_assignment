#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void goToXY(int columns, int rows) 
{
    COORD cursorPos;
    cursorPos.X = columns;
    cursorPos.Y = rows;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
}