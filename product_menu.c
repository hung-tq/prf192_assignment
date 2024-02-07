#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "product_menu.h"
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

#define MAX 1000

int items = 4;
char catalogue[6][20] = {"No.", "Name", "Quantity", "Price", "Manufactoring Date", "Expiry Date"};
int item_no[MAX] = {1, 2, 3, 4, 5};
char item_name[MAX][MAX] = {"Chicken", "Apple", "Banana", "Beef", "Pineapple"};
int item_quantity[MAX] = {1, 2, 3, 4, 5};
int item_price[MAX] = {1000, 2000, 3000, 44000, 5000};
char item_manufactoring_date[MAX][MAX] = {"22/10/2023", "23/10/2023", "24/10/2023", "25/10/2023", "26/10/2023"};
char item_expiry_date[MAX][MAX] = {"22/10/2024", "23/10/2024", "24/10/2024", "25/10/2024", "26/10/2024"};
char search_result[MAX];
int count = 0;


// Main program
int main() {
    // Loop 
    while (1) {
        main_menu_display();
        int choice = getch() - '0';

        switch (choice) {
            case 1: { // Display all items
                display_all_items(item_name, item_quantity, item_price, item_manufactoring_date, item_expiry_date);
                printf("\n                          Press any keys to return to main menu     ");
                getch();
                break;
            }
            case 2: { // Add an item
                display_all_items(item_name, item_quantity, item_price, item_manufactoring_date, item_expiry_date);
                add_an_item();
                printf("\n");
                printf("                  Press r to refresh the list, any other key to return to main menu:    ");
                char choice_2 = getch();
                if (choice_2 == 'R' || choice_2 == 'r') {
                    display_all_items(item_name, item_quantity, item_price, item_manufactoring_date, item_expiry_date);
                    printf("\n                          Press any keys to return to main menu     ");
                    getch();
                }
                else {
                    printf("\n");
                    printf("Returning to main menu...");
                    sleep(2);
                }
                break;
                
            }
            case 3: { // Sort items by fields
                display_all_items(item_name, item_quantity, item_price, item_manufactoring_date, item_expiry_date);
                printf("\n                          1.     Name     ");
                printf("\n                          2.     Quantity     ");
                printf("\n                          3.     Price     ");
                printf("\n                          4.     Manufactoring Date     ");
                printf("\n                          5.     Expiry Date     ");
                printf("\n");
                printf("\n                          Which field do you want to sort (Press a listed number)    ");
                int choice_3 = getch() - '0';               
                
                printf("     \n");
                sort_by_field(choice_3);
                printf("     \n");
                
                printf("\n                          Press any keys to return to main menu     ");
                getch();
                break;
            }
            case 4: { // Search by fields
                while (1) {
                    display_all_items(item_name, item_quantity, item_price, item_manufactoring_date, item_expiry_date);
                    printf("\n                          1.     Name     ");
                    printf("\n                          2.     Quantity     ");
                    printf("\n                          3.     Price     ");
                    printf("\n                          4.     Manufactoring Date     ");
                    printf("\n                          5.     Expiry Date     ");
                    printf("\n");
                    printf("\n                          Which field do you want to search (Press a listed number)     ");
                    int choice_4 = getch() - '0'; 
                    strcpy(search_result, "");

                    search_by_field(choice_4);
                    display_result_list();

                    printf("\n                          Press b to search again or Enter to return to main menu     ");
                    char choice_4_1 = getch();
                    if (choice_4_1 != 'B' && choice_4_1 != 'b') {
                        break;
                    }
                }
                break;

            }
            case 5: { // Print all the data to a text file
                printf("     \n");
                export_data_to_file();
                printf("     \n");

                printf("\n                                  Press o to open file or Enter to return to main menu    ");
                char choice_5 = getch();
                if (choice_5 == 'O' || choice_5 == 'o') {
                    open_file();
                }
                else {
                    printf("Returning to main menu...");
                    sleep(2);
                }
                break;
            }
            case 6: { // Delete the found item
                while (1) {
                    display_all_items(item_name, item_quantity, item_price, item_manufactoring_date, item_expiry_date);
                    printf("\n                          1.     Name     ");
                    printf("\n                          2.     Quantity     ");
                    printf("\n                          3.     Price     ");
                    printf("\n                          4.     Manufactoring Date     ");
                    printf("\n                          5.     Expiry Date     ");
                    printf("\n");
                    printf("\n                  Which field do you want an item to delete in  (Press a listed number)     ");
                    int choice_6 = getch() - '0';

                    delete_found_item(choice_6);
                    printf(" \n");

                    printf("\n                     Press r to continue delete or Enter to return to main menu     ");
                    char choice_6_1 = getch();
                    if (choice_6_1 != 'B' && choice_6_1 != 'b') {
                        break;
                    }                    
                }
                break;
            }
            case 7: { // Delete all data
                display_all_items(item_name, item_quantity, item_price, item_manufactoring_date, item_expiry_date);
                delete_all_data();

                printf(" \n");
                printf("\n                          Press any keys to return to main menu     ");
                getch();
                break;
            }
            case 8:
                break;
            default: {
                printf("\n                                Enter a valid option!");
                sleep(1);
                break;
            }

        }
        if (choice == 8) {
            printf("\nExiting...");
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
    printf("*                                  8. Quit.                                               *\n");
    printf("*                                                                                         *\n");
    printf("*******************************************************************************************\n");
    printf("\n                                Press a number to process      ");
}

void display_all_items(char item_name[MAX][MAX], int item_quantity[MAX], int item_price[MAX], char item_manufactoring_date[MAX][MAX], char item_expiry_date[MAX][MAX]) {
    int j = 1;
    system("cls");
    printf("**********************************************************************************************************\n");
    printf("*                                              All Items                                                 *\n");
    printf("**********************************************************************************************************\n");
    printf("*                                                                                                        *\n");
    printf("*   No.  |   Name              |  Quantity    |   Price      |   Manufactoring Date   |   Expiry Date    *\n");
    printf("*                                                                                                        *\n");
    for (int i = 0; i <= items; i++) {
        if (item_name[i][0] != '\0') {
            printf("*   %-1d    |   %-13s     |   %-3d        |   %-7d    |   %s           |   %s     *\n", j, item_name[i], item_quantity[i], item_price[i], item_manufactoring_date[i], item_expiry_date[i]);
            j++;
        }
    }
    printf("*                                                                                                        *\n");
    printf("**********************************************************************************************************\n");
}

void add_an_item() {
    items++;
    item_no[items] = items + 1;
    printf("\n");
    printf("                  Enter an item name (string): ");
    scanf("%s", item_name[items]);
    printf("                  Enter an item quantity (number): ");
    scanf("%d", &item_quantity[items]);
    printf("                  Enter an item price (number): ");
    scanf("%d", &item_price[items]);
    printf("                  Enter an item manufactoring date (string): ");
    scanf("%s", item_manufactoring_date[items]);
    printf("                  Enter an item expiry date (string): ");
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
    strcpy(search_result, "");
    count = 0;
    switch (choice_4) {
        case 1: {
            char search_name[MAX];
            printf("     \n");
            printf("\n                          Enter the name:     ");
            scanf("%s", search_name);
            for (int i = 0; i <= items; i++) {
                if (strcmp(search_name, item_name[i]) == 0) {
                    search_result[i] = 1;
                    count++;
                }
            }
            break;
        }
        case 2: {
            int search_quantity;
            printf("     \n");
            printf("\n                          Enter the quantity:     ");
            scanf("%d", &search_quantity);
            for (int i = 0; i <= items; i++) {
                if (search_quantity == item_quantity[i]) {
                    search_result[i] = 1;
                    count++;
                }
            }
            break;
        }
        case 3: {
            int search_price;
            printf("     \n");
            printf("\n                          Enter the price:     ");
            scanf("%d", &search_price);
            for (int i = 0; i <= items; i++) {
                if (search_price == item_price[i]) {
                    search_result[i] = 1;
                    count++;
                }
            }
            break;
        }
        case 4: {
            char search_manufactoring_date[MAX];
            printf("     \n");
            printf("\n                          Enter the manufactoring date:     ");
            scanf("%s", search_manufactoring_date);
            for (int i = 0; i <= items; i++) {
                if (strcmp(search_manufactoring_date, item_name[i]) == 0) {
                    search_result[i] = 1;
                    count++;
                }                
            }
            break;
        }
        case 5: {
            char search_expiry_date[MAX];
            printf("     \n");
            printf("\n                          Enter the expiry date:     ");
            scanf("%s", search_expiry_date);
            for (int i = 0; i <= items; i++) {
                if (strcmp(search_expiry_date, item_name[i]) == 0) {
                    search_result[i] = 1;
                    count++;
                }                
            }
            break;
        }
        default: 
            break;
    }
}

void display_result_list() {
    if (count == 0) {
        printf("\n                          No items found!");
    }
    else {
        printf("     \n");
        printf("                                           %d items found!\n", count);
        printf("     \n");
        printf("**********************************************************************************************************\n");
        printf("*                                            Search Result                                               *\n");
        printf("**********************************************************************************************************\n");
        printf("*                                                                                                        *\n");
        printf("*   No.  |   Name              |  Quantity    |   Price      |   Manufactoring Date   |   Expiry Date    *\n");
        printf("*                                                                                                        *\n");
        for (int i = 0; i <= items; i++) {
            if (search_result[i] == 1) {
                printf("*   %-1d    |   %-13s     |   %-3d        |   %-7d    |   %s           |   %s     *\n", i + 1, item_name[i], item_quantity[i], item_price[i], item_manufactoring_date[i], item_expiry_date[i]);
            }
        }
        printf("*                                                                                                        *\n");
        printf("**********************************************************************************************************\n");
    }
}

void export_data_to_file() {
    FILE *items_txt;
    int j = 1;
    items_txt = fopen("items.txt", "w");
    fprintf(items_txt, "**********************************************************************************************************\n");
    fprintf(items_txt, "*                                              All Items                                                 *\n");
    fprintf(items_txt, "**********************************************************************************************************\n");
    fprintf(items_txt, "*                                                                                                        *\n");
    fprintf(items_txt, "*   No.  |   Name              |  Quantity    |   Price      |   Manufactoring Date   |   Expiry Date    *\n");
    fprintf(items_txt, "*                                                                                                        *\n");
    for (int i = 0; i <= items; i++) {
        if (item_name[i][0] != '\0') {
            fprintf(items_txt, "*   %-1d    |   %-13s     |   %-3d        |   %-7d    |   %s           |   %s     *\n", j, item_name[i], item_quantity[i], item_price[i], item_manufactoring_date[i], item_expiry_date[i]);
            j++;
        }
    }
    fprintf(items_txt, "*                                                                                                        *\n");
    fprintf(items_txt, "**********************************************************************************************************\n");
    fclose(items_txt);
    printf("\n                                  Data exported to items.txt!");
}

void open_file() {
    FILE *items_txt;
    items_txt = fopen("items.txt", "r");
    if (items_txt == NULL) {
        printf("File does not exist!");
        return;
    }
    char c;
    while ((c = fgetc(items_txt)) != EOF) {
        printf("%c", c);
    }
    fclose(items_txt);
}

void delete_found_item(int choice_6) {
    search_by_field(choice_6);
    display_result_list();
    printf("     \n");
    if (count != 0) {
        printf("                     Do you want to delete all found items? (yes/no) (Press y or n)     ");
        char choice_6_6_1 = getch();

        if (choice_6_6_1 == 'Y' || choice_6_6_1 == 'y') {
            for (int i = 0; i <= items; i++) {
                if (search_result[i] == 1) {
                    strcpy(item_name[i], "");
                    item_quantity[i] = 0;
                    item_price[i] = 0;
                    strcpy(item_manufactoring_date[i], "");
                    strcpy(item_expiry_date[i], "");
                }
            }
            printf("\n");
            printf("                     %d items deleted!", count);
        
        } else {
            printf("\n");
            printf("                     No items deleted!");
        } 
    }
}

void delete_all_data() {
    printf("     \n");
    printf("                     Do you want to delete all items? (yes/no) (Press y or n)     ");
    char choice_7 = getch();
    if (choice_7 == 'Y' || choice_7 == 'y') {
        for (int i = 0; i <= items; i++) {
            strcpy(item_name[i], "");
            item_quantity[i] = 0;
            item_price[i] = 0;
            strcpy(item_manufactoring_date[i], "");
            strcpy(item_expiry_date[i], "");
        }
        items = -1;
        printf(" \n");
        printf("\n                     All items deleted!");
    } else {
        printf(" \n");
        printf("\n                     No items deleted!");
    }
}
