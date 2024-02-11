#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

#include "product_menu.h"

#define MAXDB 1000 // Size of database 
#define MAXLENGTH 1000 // Length of string

int items = 5;
char catalogue[6][20] = {"No.", "name", "weight", "price", "manufactoring date", "expiry date"};
char item_name[MAXDB][MAXLENGTH] = {"chicken", "apple", "banana", "beef", "pineapple", "rice"};
int item_weight[MAXDB] = {1, 2, 3, 4, 5, 800000};
int item_price[MAXDB] = {1000, 2000, 3000, 44000, 5000, 5000000};
char item_manufactoring_date[MAXDB][MAXLENGTH] = {"22/10/2023", "23/10/2023", "24/10/2023", "25/10/2023", "n", "12/12/1222"};
char item_expiry_date[MAXDB][MAXLENGTH] = {"22/10/2024", "23/10/2024", "24/10/2024", "25/10/2024", "non", "13/13/1313"};
int search_result[MAXDB];
int count = 0;


// Main program
void product_menu() {
    // Loop 
    while (1) {
        main_menu_display();
        int choice = getch() - '0';
        switch (choice) {
            case 1: { // Display all items
                display_all_items();
                printf("\n                               Press any keys to return to main menu     ");
                getch();
                break;
            }
            case 2: { // Add an item
                display_all_items();
                if (add_an_item() == 1) {
                    printf("\n                                            Add item successfully!\n");
                    printf("\n                     Press r to refresh the list, any other key to return to main menu    ");
                    char choice_2 = getch();
                    if (choice_2 == 'R' || choice_2 == 'r') {
                        display_all_items();
                        printf("\n                                   Press any keys to return to main menu     ");
                        getch();
                    }
                    else {
                        printf("\n\n                                            Returning to main menu...");
                        sleep(1);
                    }
                }
                break;
            }
            case 3: { // Sort items by fields
                while (1) {
                    display_all_items();
                    display_catalogue();
                    printf("\n                          Which field do you want to sort (Press a listed number)    ");
                    int choice_3 = getch() - '0';               
                    if (sort_by_field(choice_3) == 1) {
                        printf("\n\n                          Sort by %s successfully!\n", catalogue[choice_3]);
                        printf("\n                          Press any keys to return to main menu     ");
                        getch();
                        break;                
                    } else if (sort_by_field(choice_3) == 0) {
                        printf("\n\n                                     Enter a valid option!");
                        sleep(1);
                    }
                    else
                        break;
                }
                break;
            }
            case 4: { // Search by fields
                while (1) {
                    display_all_items();
                    display_catalogue();
                    printf("\n                          Which field do you want to search (Press a listed number)     ");
                    int choice_4 = getch() - '0'; 
                    memset(search_result, 0, MAXDB); // Set all elements to 0
                    if (search_by_field(choice_4) == 1) {
                        display_result_list();
                        printf("\n                          Press r to search again or Enter to return to main menu     ");
                        char choice_4_1 = getch();
                        if (choice_4_1 != 'R' && choice_4_1 != 'r') {
                            break;
                        }
                    } else if (search_by_field(choice_4) == 0) {
                        printf("\n\n                                     Enter a valid option!");
                        sleep(1);
                    } else
                        break;
                }
                break;

            }
            case 5: { // Print all the data to a text file
                printf("\n");
                export_data_to_file();
                printf("\n\n                           Press o to open file or Enter to return to main menu    ");
                char choice_5 = getch();
                printf("\n");
                if (choice_5 == 'O' || choice_5 == 'o') {
                    open_file();
                    printf("\n                                  Press any keys to return to main menu     ");
                    getch();
                }
                else {
                    printf("\n                                  Returning to main menu...");
                    sleep(1);
                }
                break;
            }
            case 6: { // Delete the matched item
                while (1) {
                    display_all_items();
                    display_catalogue();
                    printf("\n                  Which field do you want an item to delete in  (Press a listed number)     ");
                    int choice_6 = getch() - '0';
                    if (delete_found_item(choice_6) == 1) {
                        printf("\n\n                     Press r to continue delete or Enter to return to main menu     ");
                        char choice_6_1 = getch();
                        if (choice_6_1 != 'R' && choice_6_1 != 'r') {
                            break;
                        } 
                    } else if  (delete_found_item(choice_6) == 0) {
                        printf("\n\n                                     Enter a valid option!");
                        sleep(1);
                    } else
                        break;                 
                }
                break;
            }
            case 7: { // Delete all data
                display_all_items();
                delete_all_data();
                printf("\n\n                          Press any keys to return to main menu     ");
                getch();
                break;
            }
            case 8: // Quit
                break;
            default: { // Invalid option
                printf("\n\n                                     Enter a valid option!");
                sleep(1);
                break;
            }
        }
        if (choice == 8) { // End program
            printf("\nExiting...");
            sleep(1);
            break;
        }   
    }
}

// Function definitions
void main_menu_display() {
    system("cls");
    printf("***************************************************************************************************************\n");
    printf("*                                               Product Menu                                                  *\n");
    printf("***************************************************************************************************************\n");
    printf("*                                                                                                             *\n");
    printf("*                                         1. Display all items.                                               *\n");
    printf("*                                         2. Add an item.                                                     *\n");
    printf("*                                         3. Sort all items.                                                  *\n");
    printf("*                                         4. Look for an item.                                                *\n");
    printf("*                                         5. Export data to a text file.                                      *\n");
    printf("*                                         6. Delete matched item.                                             *\n");
    printf("*                                         7. Delete all items.                                                *\n");
    printf("*                                         8. Quit.                                                            *\n");
    printf("*                                                                                                             *\n");
    printf("***************************************************************************************************************\n");
    printf("\n                                     Press a number to process         ");
}

void display_catalogue() {
    printf("\n                          1.     Name     ");
    printf("\n                          2.     Weight (kg)     ");
    printf("\n                          3.     Price (per kg)     ");
    printf("\n                          4.     Manufactoring Date     ");
    printf("\n                          5.     Expiry Date     ");
    printf("\n                          6.     Return to menu     ");
    printf("\n");
}

void display_all_items() {
    int j = 1;
    system("cls");
    printf("***************************************************************************************************************\n");
    printf("*                                               Product List                                                  *\n");
    printf("***************************************************************************************************************\n");
    printf("*                                                                                                             *\n");
    printf("*   No. |   Name           |   Weight (kg)   |   Price (per kg)    |   Manufactoring Date   |   Expiry Date   *\n");
    printf("*                                                                                                             *\n");
    for (int i = 0; i <= items; i++) {
        if (item_name[i][0] != '\0') {
    printf("*   %-4d|   %-12s   |   %-11d   |   %-14d    |   %-18s   |   %-11s   *\n", j, item_name[i], item_weight[i], item_price[i], item_manufactoring_date[i], item_expiry_date[i]);
            j++;
        }
    }
    printf("*                                                                                                             *\n");
    printf("***************************************************************************************************************\n");
}

int add_an_item() {
    char temp_item_name[MAXLENGTH];
    int temp_item_weight;
    int temp_item_price;
    char temp_item_manufactoring_date[MAXLENGTH];
    char temp_item_expiry_date[MAXLENGTH];

    printf("\n        Item name (string)              (Enter q to return to main menu):     ");
    scanf("%s", temp_item_name);
    if (strcmp(temp_item_name, "q") == 0) {
        return -1;// Return to menu
    }
    printf("        Weight (kg) (integer)           (Enter q to return to main menu):     ");
    scanf("%d", &temp_item_weight);
    if (temp_item_weight == 'q') {
        return -1;// Return to menu
    }
    printf("        Price (per kg) (integer)        (Enter q to return to main menu):     ");
    scanf("%d", &temp_item_price);
    if (temp_item_price == 'q') {
        return -1;// Return to menu
    }
    printf("        Manufactoring date (dd/mm/yyyy) (Enter q to return to main menu):     ");
    scanf("%s", temp_item_manufactoring_date);
    if (strcmp(temp_item_manufactoring_date, "q") == 0) {
        return -1;// Return to menu
    }
    printf("        Expiry date (dd/mm/yyyy)        (Enter q to return to main menu):     ");
    scanf("%s", temp_item_expiry_date);
    if (strcmp(temp_item_expiry_date, "q") == 0) {
        return -1; // Return to menu
    }

    items++;
    strcpy(item_name[items], temp_item_name);
    item_weight[items] = temp_item_weight;
    item_price[items] = temp_item_price;
    strcpy(item_manufactoring_date[items], temp_item_manufactoring_date);
    strcpy(item_expiry_date[items], temp_item_expiry_date);
  
    return 1; // Valid option    
}

void swap_sort(int i, int j) {
    char temp_item_name[MAXLENGTH];
    strcpy(temp_item_name, item_name[i]);
    strcpy(item_name[i], item_name[j]);
    strcpy(item_name[j], temp_item_name);

    int temp_item_weight;
    temp_item_weight = item_weight[i];
    item_weight[i] = item_weight[j];
    item_weight[j] = temp_item_weight;

    int temp_item_price;
    temp_item_price = item_price[i];
    item_price[i] = item_price[j];
    item_price[j] = temp_item_price;

    char temp_item_manufactoring_date[MAXLENGTH];
    strcpy(temp_item_manufactoring_date, item_manufactoring_date[i]);
    strcpy(item_manufactoring_date[i], item_manufactoring_date[j]);
    strcpy(item_manufactoring_date[j], temp_item_manufactoring_date);           

    char temp_item_expiry_date[MAXLENGTH];
    strcpy(temp_item_expiry_date, item_expiry_date[i]);
    strcpy(item_expiry_date[i], item_expiry_date[j]);
    strcpy(item_expiry_date[j], temp_item_expiry_date);   
}

int sort_by_field(int choice_3) {
    for (int i = 0; i <= items; i++) {
        for (int j = i + 1; j <= items; j++) {
            switch (choice_3) {
                case 1:
                    if (strcmp(item_name[i], item_name[j]) > 0) 
                        swap_sort(i, j);
                    break;
                case 2:
                    if (item_weight[i] > item_weight[j])
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
                case 6:
                    return -1; // Return to menu                    
                default:
                    return 0; // Invalid option
            }
        }            
    }
    return 1; // Valid option
}

int search_by_field(int choice_4) {
    memset(search_result, 0, MAXDB); // Set all elements of search_result to 0
    count = 0;
    switch (choice_4) {
        case 1: { // Search by name
            char search_name[MAXLENGTH];
            printf("\n\n                          Enter the name:     ");
            scanf("%s", search_name);
            for (int i = 0; i <= items; i++) {
                if (strcmp(search_name, item_name[i]) == 0) {
                    search_result[i] = 1;
                    count++;
                }
            }
            break;
        }
        case 2: { // Search by weight
            int search_weight;
            printf("\n\n                          Enter the quantity:     ");
            scanf("%d", &search_weight);
            for (int i = 0; i <= items; i++) {
                if (search_weight == item_weight[i]) {
                    search_result[i] = 1;
                    count++;
                }
            }
            break;
        }
        case 3: { // Search by price
            int search_price;
            printf("\n\n                          Enter the price:     ");
            scanf("%d", &search_price);
            for (int i = 0; i <= items; i++) {
                if (search_price == item_price[i]) {
                    search_result[i] = 1;
                    count++;
                }
            }
            break;
        }
        case 4: { // Search by manufactoring date
            char search_manufactoring_date[MAXLENGTH];
            printf("\n\n                          Enter the manufactoring date:     ");
            scanf("%s", search_manufactoring_date);
            for (int i = 0; i <= items; i++) {
                if (strcmp(search_manufactoring_date, item_manufactoring_date[i]) == 0) {
                    search_result[i] = 1;
                    count++;
                }                
            }
            break;
        }
        case 5: { // Search by expiry date
            char search_expiry_date[MAXLENGTH];
            printf("\n\n                          Enter the expiry date:     ");
            scanf("%s", search_expiry_date);
            for (int i = 0; i <= items; i++) {
                if (strcmp(search_expiry_date, item_expiry_date[i]) == 0) {
                    search_result[i] = 1;
                    count++;
                }                
            }
            break;
        }
        case 6:
            return -1; // Return to menu
        default: 
            return 0; // Invalid option
    }
    return 1; // Valid option
}

void display_result_list() {
    int j = 1;
    if (count == 0) {
        printf("\n                          No items found!\n");
    }
    else {
        printf("\n                          %d items found!\n", count);
        printf("\n");
        printf("***************************************************************************************************************\n");
        printf("*                                               Search Result                                                 *\n");
        printf("***************************************************************************************************************\n");
        printf("*                                                                                                             *\n");
        printf("*   No. |   Name           |   Weight (kg)   |   Price (per kg)    |   Manufactoring Date   |   Expiry Date   *\n");
        printf("*                                                                                                             *\n");
        for (int i = 0; i <= items; i++) {
            if (search_result[i] == 1) {
                printf("*   %-4d|   %-12s   |   %-11d   |   %-14d    |   %-18s   |   %-11s   *\n", j, item_name[i], item_weight[i], item_price[i], item_manufactoring_date[i], item_expiry_date[i]);
                j++;
            }
        }
        printf("*                                                                                                             *\n");
        printf("***************************************************************************************************************\n");
    
    }
}

void export_data_to_file() {
    FILE *items_txt;
    items_txt = fopen("items.txt", "w");
    fprintf(items_txt, "***************************************************************************************************************\n");
    fprintf(items_txt, "*                                               Product List                                                  *\n");
    fprintf(items_txt, "***************************************************************************************************************\n");
    fprintf(items_txt, "*                                                                                                             *\n");
    fprintf(items_txt, "*   No. |   Name           |   Weight (kg)   |   Price (per kg)    |   Manufactoring Date   |   Expiry Date   *\n");
    fprintf(items_txt, "*                                                                                                             *\n");
    for (int i = 0; i <= items; i++) {
        if (item_name[i][0] != '\0') {
            fprintf(items_txt, "*   %-4d|   %-12s   |   %-11d   |   %-14d    |   %-18s   |   %-11s   *\n", i + 1, item_name[i], item_weight[i], item_price[i], item_manufactoring_date[i], item_expiry_date[i]);
        }
    }
    fprintf(items_txt, "*                                                                                                             *\n");
    fprintf(items_txt, "***************************************************************************************************************\n");
    fclose(items_txt);
    printf("\n                                     Data exported to items.txt!");
}

void open_file() {
    FILE *items_txt;
    items_txt = fopen("items.txt", "r");
    if (items_txt == NULL) {
        printf("File does not exist!");
        return;
    }
    printf("\n");
    char c;
    while ((c = fgetc(items_txt)) != EOF) {
        printf("%c", c);
    }
    fclose(items_txt);
}

int delete_found_item(int choice_6) {
    if (search_by_field(choice_6) == 1) {
        display_result_list();
        if (count != 0) {
            printf("\n                     Do you want to delete all found items? (yes/no) (Press y or n)     ");
            char choice_6_6_1 = getch();
            if (choice_6_6_1 == 'Y' || choice_6_6_1 == 'y') {
                for (int i = 0; i <= items; i++) {
                    if (search_result[i] == 1) {
                        strcpy(item_name[i], "");
                        item_weight[i] = 0;
                        item_price[i] = 0;
                        strcpy(item_manufactoring_date[i], "");
                        strcpy(item_expiry_date[i], "");
                    }
                }
                printf("\n\n                     %d items deleted!", count);
            } else {
                printf("\n\n                     No items deleted!");
            } 
        }
        return 1; // Valid option
    } else if (search_by_field(choice_6) == 0) {
        return 0; // Invalid option
    } else
        return -1; // Return to menu
}

void delete_all_data() {
    printf("\n                     Do you want to delete all items? (yes/no) (Press y or n)     ");
    char choice_7 = getch();
    if (choice_7 == 'Y' || choice_7 == 'y') {
        for (int i = 0; i <= items; i++) {
            strcpy(item_name[i], "");
            item_weight[i] = 0;
            item_price[i] = 0;
            strcpy(item_manufactoring_date[i], "");
            strcpy(item_expiry_date[i], "");
        }
        items = -1;
        printf("\n\n                     All items deleted!");
    } else {
        printf("\n\n                     No items deleted!");
    }
}
