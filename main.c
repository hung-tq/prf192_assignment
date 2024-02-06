#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <time.h>
#include <unistd.h>

#define MAX 1000

// Main program
int main() {
    // Item database arrays
    int items = 5;
    int item_no[MAX] = {1, 2, 3, 4, 5};
    char* item_name[MAX] = {"Chicken", "Apple", "Banana", "Beef", "Pineapple"};
    int item_quantity[MAX] = {1, 2, 3, 4, 5};
    int item_price[MAX] = {1000, 2000, 3000, 4000, 5000};
    char* item_manufactoring_date[MAX] = {"22/10/2023", "23/10/2023", "24/10/2023", "25/10/2023", "26/10/2023"};
    char* item_expiry_date[MAX] = {"22/10/2024", "23/10/2024", "24/10/2024", "25/10/2024", "26/10/2024"};

    // Loop 
    while (1) {
        int choice;
        main_menu_display();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char choice_1;
                display_all_items(item_no, item_name, item_quantity, item_price, item_manufactoring_date, item_expiry_date, items);
                scanf("%s", &choice_1);
                printf("\n                          Enter any keys to return to main menu:     ");
            }
            case 2: {
                display_all_items(item_no, item_name, item_quantity, item_price, item_manufactoring_date, item_expiry_date, items);
                add_an_item(item_no, item_name, item_quantity, item_price, item_manufactoring_date, item_expiry_date, items);
                
            }
            case 9:
                break;
            default: {
                printf("Enter a valid option!");
                sleep(1);
            }

        }
        if (choice == 9) {
            printf("Exiting...");
            sleep(1);
            break;
        }   
    }


    return 0;
}

// Function definitions
void banner() {

}

void main_menu_display() {
    system("cls");
    printf("*******************************************************************************************\n");
    printf("*                                       Mini Market                                       *\n");
    printf("*******************************************************************************************\n");
    printf("*                                                                                         *\n");
    printf("*                                  1. Display all items.                                  *\n");
    printf("*                                  2. Add an item.                                        *\n");
    printf("*                                  3. Sort all items.                                     *\n");
    printf("*                                  4. Look for an item.                                   *\n");
    printf("*                                  5. Export data to a text file.                         *\n");
    printf("*                                  6. Delete matched item.                                *\n");
    printf("*                                  7. Delete all items.                                   *\n");
    printf("*                                  8. Delete all items.                                   *\n");
    printf("*                                  9. Quit.                                               *\n");
    printf("*                                                                                         *\n");
    printf("*******************************************************************************************\n");
    printf("\n                                  Enter your choice:     ");
}

int main_menu_choice() {
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > 9)
        return -1;
    return choice;
}

void display_all_items(int item_no[], char* item_name[], int item_quantity[], int item_price[], char* item_manufactoring_date[], char* item_expiry_date[], int items) {
    system("cls");
    printf("**************************************************************************************************\n");
    printf("*                                       All Items                                                *\n");
    printf("**************************************************************************************************\n");
    printf("*                                                                                                *\n");
    printf("*   No.  |   Name           |  Quantity  |   Price   |   Manufactoring Date   |   Expiry Date    *\n");
    printf("*                                                                                                *\n");
    for (int i = 0; i < items; i++) {
        printf("*   %-1d    |   %-10s     |   %-1d        |   %-2d    |   %s           |   %s     *\n", item_no[i], item_name[i], item_quantity[i], item_price[i], item_manufactoring_date[i], item_expiry_date[i]);
    }
    printf("*                                                                                                *\n");
    printf("**************************************************************************************************\n");
}

void add_an_item(int item_no[], char* item_name[], int item_quantity[], int item_price[], char* item_manufactoring_date[], char* item_expiry_date[], int items) {
    printf("Enter an item name: ");
    items++;
    scanf("%s", item_name[items]);
    // if (is_duplicate(item_name, items, item_name[items])) {
    //     printf("1");
    // } else {
    //     printf("0");
    // }
    printf("0");
    
}

// char* lowercase(char str[]) {
//     int lower_str[MAX];
//     for (int i = 0; str[i]; i++) {
//         lower_str[i] = tolower(str[i]);
//     }
//     return lower_str[];
// }

int is_duplicate(char* item_name[], int items, char* name) {
    for (int i = 0; i < items; i++) {
        if (strcmp(item_name[i], name) == 0) {
            return 1; // Duplicate found
        }
    }
    return 0; // No duplicate found

}

void product_menu() {

}

void customer_menu() {

}
