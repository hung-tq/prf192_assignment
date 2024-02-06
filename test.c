#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 5
#define MAX_NAME_LENGTH 50
#define MAX_DATE_LENGTH 20

char item_names[MAX_ITEMS][MAX_NAME_LENGTH];
int item_quantities[MAX_ITEMS];
float item_prices[MAX_ITEMS];
char manufacturing_dates[MAX_ITEMS][MAX_DATE_LENGTH];
char expiry_dates[MAX_ITEMS][MAX_DATE_LENGTH];

int item_count = 0;

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
    printf("*                                  8. Exit.                                               *\n");
    printf("*                                                                                         *\n");
    printf("*******************************************************************************************\n");
    printf("\n                                  Enter your choice:     ");
}

void display_all_items() {
    for (int i = 0; i < item_count; i++) {
        printf("Name: %s, Quantity: %d, Price: %.2f, Manufacturing Date: %s, Expiry Date: %s\n",
               item_names[i], item_quantities[i], item_prices[i], manufacturing_dates[i], expiry_dates[i]);
    }
    printf("\nPress Enter to return to the main menu...");
    getchar(); // Consume the newline character left in the buffer
    getchar(); // Wait for user input
}

void add_new_item() {
    main_menu_display();
    if (item_count < MAX_ITEMS) {
        printf("Enter item name: ");
        scanf("%s", item_names[item_count]);
        printf("Enter item quantity: ");
        scanf("%d", &item_quantities[item_count]);
        printf("Enter item price: ");
        scanf("%f", &item_prices[item_count]);
        printf("Enter manufacturing date (YYYY-MM-DD): ");
        scanf("%s", manufacturing_dates[item_count]);
        printf("Enter expiry date (YYYY-MM-DD): ");
        scanf("%s", expiry_dates[item_count]);
        item_count++;
        printf("\nItem added successfully.\n");
    } else {
        printf("Max items reached. Cannot add more.\n");
    }
    printf("\nPress Enter to return to the main menu...");
    getchar(); // Consume the newline character left in the buffer
    getchar(); // Wait for user input
}

void sort_items(int field) {
    for (int i = 0; i < item_count - 1; i++) {
        for (int j = 0; j < item_count - i - 1; j++) {
            if (field == 1 && strcmp(item_names[j], item_names[j + 1]) > 0) {
                // Sort by name
                char temp_name[MAX_NAME_LENGTH];
                strcpy(temp_name, item_names[j]);
                strcpy(item_names[j], item_names[j + 1]);
                strcpy(item_names[j + 1], temp_name);

                int temp_quantity = item_quantities[j];
                item_quantities[j] = item_quantities[j + 1];
                item_quantities[j + 1] = temp_quantity;

                float temp_price = item_prices[j];
                item_prices[j] = item_prices[j + 1];
                item_prices[j + 1] = temp_price;

                char temp_manufacturing[MAX_DATE_LENGTH];
                strcpy(temp_manufacturing, manufacturing_dates[j]);
                strcpy(manufacturing_dates[j], manufacturing_dates[j + 1]);
                strcpy(manufacturing_dates[j + 1], temp_manufacturing);

                char temp_expiry[MAX_DATE_LENGTH];
                strcpy(temp_expiry, expiry_dates[j]);
                strcpy(expiry_dates[j], expiry_dates[j + 1]);
                strcpy(expiry_dates[j + 1], temp_expiry);
            } else if (field == 2 && item_quantities[j] > item_quantities[j + 1]) {
                // Sort by quantity
                char temp_name[MAX_NAME_LENGTH];
                strcpy(temp_name, item_names[j]);
                strcpy(item_names[j], item_names[j + 1]);
                strcpy(item_names[j + 1], temp_name);

                int temp_quantity = item_quantities[j];
                item_quantities[j] = item_quantities[j + 1];
                item_quantities[j + 1] = temp_quantity;

                float temp_price = item_prices[j];
                item_prices[j] = item_prices[j + 1];
                item_prices[j + 1] = temp_price;

                char temp_manufacturing[MAX_DATE_LENGTH];
                strcpy(temp_manufacturing, manufacturing_dates[j]);
                strcpy(manufacturing_dates[j], manufacturing_dates[j + 1]);
                strcpy(manufacturing_dates[j + 1], temp_manufacturing);

                char temp_expiry[MAX_DATE_LENGTH];
                strcpy(temp_expiry, expiry_dates[j]);
                strcpy(expiry_dates[j], expiry_dates[j + 1]);
                strcpy(expiry_dates[j + 1], temp_expiry);
            }
        }
    }
    printf("\nItems sorted successfully.\n");
    printf("\nPress Enter to return to the main menu...");
    getchar(); // Consume the newline character left in the buffer
    getchar(); // Wait for user input
}

void search_item(char item_name[MAX_NAME_LENGTH]) {
    main_menu_display();
    int found = 0;
    for (int i = 0; i < item_count; i++) {
        if (strcmp(item_names[i], item_name) == 0) {
            printf("Name: %s, Quantity: %d, Price: %.2f, Manufacturing Date: %s, Expiry Date: %s\n",
                   item_names[i], item_quantities[i], item_prices[i], manufacturing_dates[i], expiry_dates[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("Item not found\n");
    }
    printf("\nPress Enter to return to the main menu...");
    getchar(); // Consume the newline character left in the buffer
    getchar(); // Wait for user input
}

void write_to_file() {
    main_menu_display();
    FILE *file = fopen("items.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < item_count; i++) {
            fprintf(file, "Name: %s, Quantity: %d, Price: %.2f, Manufacturing Date: %s, Expiry Date: %s\n",
                    item_names[i], item_quantities[i], item_prices[i], manufacturing_dates[i], expiry_dates[i]);
        }
        fclose(file);
        printf("Data written to file.\n");
    } else {
        printf("Error opening file.\n");
    }
    printf("\nPress Enter to return to the main menu...");
    getchar(); // Consume the newline character left in the buffer
    getchar(); // Wait for user input
}

void delete_item(char item_name[MAX_NAME_LENGTH]) {
    main_menu_display();
    int found = 0;
    for (int i = 0; i < item_count; i++) {
        if (strcmp(item_names[i], item_name) == 0) {
            for (int j = i; j < item_count - 1; j++) {
                strcpy(item_names[j], item_names[j + 1]);
                item_quantities[j] = item_quantities[j + 1];
                item_prices[j] = item_prices[j + 1];
                strcpy(manufacturing_dates[j], manufacturing_dates[j + 1]);
                strcpy(expiry_dates[j], expiry_dates[j + 1]);
            }
            item_count--;
            found = 1;
            printf("Item deleted.\n");
            break;
        }
    }

    if (!found) {
        printf("Item not found\n");
    }
    printf("\nPress Enter to return to the main menu...");
    getchar(); // Consume the newline character left in the buffer
    getchar(); // Wait for user input
}

void delete_all_items() {
    main_menu_display();
    item_count = 0;
    printf("All items deleted.\n");
    printf("\nPress Enter to return to the main menu...");
    getchar(); // Consume the newline character left in the buffer
    getchar(); // Wait for user input
}

int main() {
    int choice;

    do {
        main_menu_display();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_all_items();
                break;
            case 2:
                add_new_item();
                break;
            case 3:
                printf("1. Sort by Name\n");
                printf("2. Sort by Quantity\n");
                printf("Enter your choice: ");
                int sort_choice;
                scanf("%d", &sort_choice);
                sort_items(sort_choice);
                break;
            case 4:
                printf("Enter item name to search: ");
                char search_name[MAX_NAME_LENGTH];
                scanf("%s", search_name);
                search_item(search_name);
                break;
            case 5:
                write_to_file();
                break;
            case 6:
                printf("Enter item name to delete: ");
                char delete_name[MAX_NAME_LENGTH];
                scanf("%s", delete_name);
                delete_item(delete_name);
                break;
            case 7:
                delete_all_items();
                break;
            case 8:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}
