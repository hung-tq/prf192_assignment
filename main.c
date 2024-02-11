#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "product_menu.c"
#include "customer_menu.c"

int main() {
    while (1) {
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