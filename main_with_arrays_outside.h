#ifndef HEADER_FILE
#define HEADER_FILE

#define MAX 1000
// Function protypes
void banner(); // Display banner
void main_menu_display(); // Display main menu
void product_menu(); // Display product menu
void customer_menu(); // Display customer menu
int main_menu_choice();
void display_all_items(); // Display all items in the inventory
void add_an_item();
int is_duplicate();
void sort_by_field(int);
void swap_sort(int, int);
void search_by_field(int);

#endif

