#ifndef HEADER_FILE
#define HEADER_FILE

// Function protypes
void banner(); // Display banner
void main_menu_display(); // Display main menu
void product_menu(); // Display product menu
void customer_menu(); // Display customer menu
int main_menu_choice();
void display_all_items(int item_no[], char* item_name[], int item_quantity[], int item_price[], char* item_manufactoring_date[], char* item_expiry_date[],int items); // Display all items in the inventory

#endif

