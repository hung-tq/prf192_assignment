#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


#include "main.h"
#include "product_menu.c"
#include "customer_menu.c"

#define LOOP while(1)

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

int main() {
    int columns, rows;

    system("cls");
    // hidecursor();

    LOOP {
        system("cls");
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        printf("Columns: %d\n", columns);
        printf("Rows: %d\n", rows);

        if (columns == 120 && rows == 30) 
            break;

        printf("Please set the terminal to 120x30 (column x row) for the program to work correctly!");
        printf("\nPress any key to recheck after resizing or q to quit");
        char isQuit = getch();
        if (isQuit == 'q') 
            return 0;
    }

    LOOP {
        main_menu_display();
        int choice_main_menu = getch() - '0';
        switch (choice_main_menu) {
            case 1:
                product_menu();
                break;
            case 2:
                customer_menu();
                break;
            case 3: {
                printf("\n\n                                     Goodbye!\n\n");
                sleep(1);
                return 0;
            }
            default:
                printf("\n\n                                     Invalid choice. Please try again.");
                sleep(1);
                break;
        }
    }
}

void main_menu_display() {
    system("cls"); // Clear the terminal
    printf("***************************************************************************************************************\n");
    printf("*                                               Control menu                                                  *\n");
    printf("***************************************************************************************************************\n");
    printf("*                                                                                                             *\n");
    printf("*                                         1. Product menu.                                                    *\n");
    printf("*                                         2. Customer.                                                        *\n");
    printf("*                                         3. Quit.                                                            *\n");
    printf("*                                                                                                             *\n");
    printf("***************************************************************************************************************\n");
    printf("\n                                     Press a number to process         ");
}