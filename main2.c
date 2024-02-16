#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <unistd.h>


#include "main2.h"

// #include "product_menu.c"
#include "customer_menu.c"
#include "functions.c"


#define LOOP while(1)

char databaseProduct[MAXDB][MAXDB][MAXDB]          // Type 0
= 
{
    {"chicken", "10", "30", "22/10/2023", "22/10/2024"},
    {"beef", "15", "20", "15/11/2023", "15/11/2024"},
    {"pork", "12", "25", "18/12/2023", "18/12/2024"},
    {"fish", "8", "40", "05/09/2023", "05/09/2024"},
    {"vegetables", "5", "50", "30/11/2023", "30/11/2024"},
    {"fruits", "6", "60", "12/12/2023", "12/12/2024"},
    {"bread", "3", "70", "01/01/2023", "01/01/2024"},
    {"milk", "2", "80", "02/02/2023", "02/02/2024"},
    {"cheese", "4", "90", "03/03/2023", "03/03/2024"},
    {"eggs", "1", "100", "04/04/2023", "04/04/2024"}
};

char databaseCatalogue[2][5][20] 
=
{
    {"name", "stock", "price", "manufacturing date", "expiry date"}, // Product Database
    {"name", "age", "phone number","acconut balance","bonus point"}, // Customer Database
};

char databaseCustomer[MAXDB][MAXDB][MAXDB]    // Type 1
= 
{
    {"John", "25", "1234567890", "1000", "50"},
    {"Alice", "30", "9876543210", "2000", "100"},
    {"Bob", "35", "5555555555", "1500", "75"},
    {"Emma", "28", "9999999999", "1800", "90"},
    {"Michael", "40", "1111111111", "1200", "60"},
    {"Sophia", "32", "4444444444", "2500", "125"},
    {"William", "27", "6666666666", "900", "45"},
    {"Olivia", "31", "2222222222", "1700", "85"},
    {"James", "29", "8888888888", "1400", "70"},
    {"Emily", "33", "3333333333", "2200", "110"}
};

int main() {
    int columns, rows;

    system("cls");
    // hidecursor();

    // LOOP {
    //     system("cls");
    //     CONSOLE_SCREEN_BUFFER_INFO csbi;
    //     GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    //     columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    //     rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    //     printf("Columns: %d\n", columns);
    //     printf("Rows: %d\n", rows);

    //     if (columns == 120 && rows == 30) 
    //         break;

    //     printf("Please set the terminal to 120x30 (column x row) for the program to work correctly!");
    //     printf("\nPress any key to recheck after resizing or q to quit");
    //     char isQuit = getch();
    //     if (isQuit == 'q') 
    //         return 0;
    // }

    LOOP {
        int lastIndexOfProduct = countOfDatabase(databaseProduct);

        main_menu_display();
        int choiceMainMenu = getch() - '0';
        switch (choiceMainMenu) {
            case 1:
                LOOP 
                {
                    databaseOutputDisplay(0, lastIndexOfProduct, databaseProduct, databaseCatalogue);
                    databaseCatalogueDisplay(0, databaseCatalogue);
                    printf("\n                          Which field do you want to sort (Press a listed number)    ");
                    int sortByField = getch() - '0';  

                    if (databaseSortByField(0, sortByField - 1, lastIndexOfProduct, databaseProduct)) 
                    {
                        printf("\n\n                          Sort by %s successfully!\n", databaseCatalogue[0][sortByField - 1]);
                        printf("\n                          Press any keys to return to product menu     ");
                        getch();
                        break;
                    } 
                    else if (!databaseSortByField(0, sortByField - 1, lastIndexOfProduct, databaseProduct)) 
                    {
                        printf("\n\n                                     Enter a valid option!");
                        sleep(1);                        
                    }
                    else
                        break; 
                }
                break;
            case 2:
                databaseOutputDisplay(1, 9, databaseCustomer, databaseCatalogue);
                getch();
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