#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "main_with_arrays_outside.h"
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX 1000

int items = 4;
char catalogue[6][20] = {"No.", "Name", "Quantity", "Price", "Manufactoring Date", "Expiry Date"};
int item_no[MAX] = {1, 2, 3, 4, 5};
char item_name[MAX][MAX] = {"Chicken", "Apple", "Banana", "Beef", "Pineapple"};
// char item_name[MAX][MAX] = {};
int item_quantity[MAX] = {1, 2, 3, 4, 5};
int item_price[MAX] = {1000, 2000, 3000, 4000, 5000};
char item_manufactoring_date[MAX][MAX] = {"22/10/2023", "23/10/2023", "24/10/2023", "25/10/2023", "26/10/2023"};
char item_expiry_date[MAX][MAX] = {"22/10/2024", "23/10/2024", "24/10/2024", "25/10/2024", "26/10/2024"};

// Main program
int main() {
    // Loop 
    while (1) {
        int choice;
        main_menu_display();
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Display all items
                display_all_items();
                printf("\n                          Enter any keys to return to main menu     ");
                getchar();
                getchar();
                break;
            }
            case 2: { // Add an item
                display_all_items();
                add_an_item();
                printf("\n");
                printf("                  Press R to refresh the list, any other key to return to main menu:    ");
                char choice_2;
                scanf("%s", &choice_2);
                if (choice_2 == 'R' || choice_2 == 'r') {
                    display_all_items();
                    printf("\n                          Enter any keys to return to main menu     ");
                    getchar();
                    getchar();
                }
                else {
                    printf("Returning to main menu...");
                    sleep(2);
                }
                break;
                
            }
            case 3: { // Sort items by fields
                display_all_items();
                int choice_3;
                printf("\n                          1.     Name     ");
                printf("\n                          2.     Quantity     ");
                printf("\n                          3.     Price     ");
                printf("\n                          4.     Manufactoring Date     ");
                printf("\n                          5.     Expiry Date     ");
                printf("\n");
                printf("\n                          Which field do you want to sort:     ");
                scanf("%d", &choice_3);

                sort_by_field(choice_3);
                
                printf("\n                          Enter any keys to return to main menu     ");
                getchar();
                getchar();
                break;
            }
            case 4: {
                display_all_items();
                int choice_4;
                printf("\n                          1.     Name     ");
                printf("\n                          2.     Quantity     ");
                printf("\n                          3.     Price     ");
                printf("\n                          4.     Manufactoring Date     ");
                printf("\n                          5.     Expiry Date     ");
                printf("\n");
                printf("\n                          Which field do you want to search:     ");
                scanf("%d", &choice_4);

                search_by_field(choice_4);

            }
            case 9:
                break;
            default: {
                printf("Enter a valid option!");
                sleep(1);
                break;
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

void display_all_items() {
    system("cls");
    printf("**********************************************************************************************************\n");
    printf("*                                              All Items                                                 *\n");
    printf("**********************************************************************************************************\n");
    printf("*                                                                                                        *\n");
    printf("*   No.  |   Name              |  Quantity    |   Price      |   Manufactoring Date   |   Expiry Date    *\n");
    printf("*                                                                                                        *\n");
    for (int i = 0; i <= items; i++) {
        printf("*   %-1d    |   %-13s     |   %-3d        |   %-7d    |   %s           |   %s     *\n", item_no[i], item_name[i], item_quantity[i], item_price[i], item_manufactoring_date[i], item_expiry_date[i]);
    }
    printf("*                                                                                                        *\n");
    printf("**********************************************************************************************************\n");
}

void add_an_item() {
    items++;
    item_no[items] = items + 1;
    printf("\n");
    printf("                  Enter an item name: ");
    scanf("%s", item_name[items]);
    printf("                  Enter an item quantity: ");
    scanf("%d", &item_quantity[items]);
    printf("                  Enter an item price: ");
    scanf("%d", &item_price[items]);
    printf("                  Enter an item manufactoring date: ");
    scanf("%s", item_manufactoring_date[items]);
    printf("                  Enter an item expiry date: ");
    scanf("%s", item_expiry_date[items]);
    printf("\n");
    printf("                  Item added successfully!");    
    sleep(2);    
}

void swap_sort(int i, int j) {
    char temp_item_name[MAX];
    strcpy(temp_item_name, item_name[i]);
    strcpy(item_name[i], item_name[j]);
    strcpy(item_name[j], temp_item_name);

    int temp_item_quantity;
    temp_item_quantity = item_quantity[i];
    item_quantity[i] = item_quantity[j];
    item_quantity[j] = temp_item_quantity;

    int temp_item_price;
    temp_item_price = item_price[i];
    item_price[i] = item_price[j];
    item_price[j] = temp_item_price;

    char temp_item_manufactoring_date[MAX];
    strcpy(temp_item_manufactoring_date, item_manufactoring_date[i]);
    strcpy(item_manufactoring_date[i], item_manufactoring_date[j]);
    strcpy(item_manufactoring_date[j], temp_item_manufactoring_date);           

    char temp_item_expiry_date[MAX];
    strcpy(temp_item_expiry_date, item_expiry_date[i]);
    strcpy(item_expiry_date[i], item_expiry_date[j]);
    strcpy(item_expiry_date[j], temp_item_expiry_date);   
}

void sort_by_field(int choice_3) {
    for (int i = 0; i <= items; i++) {
        for (int j = i + 1; j <= items; j++) {
            switch (choice_3) {
                case 1:
                    if (strcmp(item_name[i], item_name[j]) > 0) 
                        swap_sort(i, j);
                    break;
                case 2:
                    if (item_quantity[i] > item_quantity[j])
                        swap_sort(i, j);
                    break;
                case 3:
                    if (item_price[i] > item_price[j])
                        swap_sort(i, j);
                    break;
                case 4:
                    if (strcmp(item_manufactoring_date[i], item_manufactoring_date[j]) > 0) 
                        swap_sort(i, j);       
                    break;
                case 5:
                    if (strcmp(item_expiry_date[i], item_expiry_date[j]) > 0) 
                        swap_sort(i, j);       
                    break;                    
                default:
                    break;
            }
        }            
    }
    printf("\n                          Sort by %s completed!", catalogue[choice_3]);
}

void search_by_field(int choice_4) {
    char search_word[MAX];
    printf("Enter a name or a number to search:    ");
    scanf("%s", search_word);
    int int_search = atoi(search_word);
    for (int i = 0; i <= items; i++) {
        switch (expression) {
        
        }
    }
}