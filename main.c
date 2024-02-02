#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// Main program
int main() {
    main_menu_display();
    int choice = main_menu_choice();

    return 0;
}

// Function definitions
void banner() {

}

void main_menu_display() {
    printf("*******************************************************************************************\n");
    printf("*                                       Mini Market                                       *\n");
    printf("*******************************************************************************************\n");
    printf("*                                                                                         *\n");
    printf("*                                  1. Display all items.                                   *\n");
    printf("*                                  2. Add an item.                                         *\n");
    printf("*                                  3. Sort all items.                                      *\n");
    printf("*                                  4. Look for an item.                                    *\n");
    printf("*                                  5. Export data to a text file.                          *\n");
    printf("*                                  6. Delete matched item.                                 *\n");
    printf("*                                  7. Delete all items.                                    *\n");
    printf("*                                  8. Delete all items.                                    *\n");
    printf("********************************************************************************************\n");
    printf("\n                          Enter your choice:     ");
}

int main_menu_choice() {
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > 8)
        return -1;
    return choice;
}

void product_menu() {

}

void customer_menu() {

}
