#ifndef HEADER_FILE
#define HEADER_FILE

void product_menu();            // Product menu

void product_menu_display();    // Product menu display
void display_catalogue();       // Display catalogues
void display_all_items();       // Display product list
int  item_input(int, int, int, int, int, int);             // Add a product to database
int  sort_by_field(int);        // Search by field (choice) (using bubble sort)
void swap_sort(int, int);       // Swap the order of two adjacent items (previous pos, next pos)
int  search_by_field(int);      // Search by field (choice)
void export_data_to_file();     // Export database to items.txt file
void open_file();               // Display the content of items.txt file
int  delete_found_item(int);    // Delete a product by field (choice)
void display_result_list();     // Display the result list
void delete_all_data();         // Erase the database

void display_search_menu();
int modify_item(int, int, int, int, int, int);
void refresh_list(int);

// Return values:
// 1:  Valid option
// -1: Return to product menu
// 0:  Invalid option

#endif

