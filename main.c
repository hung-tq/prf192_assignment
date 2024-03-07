#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

#include "main.h"

// Macro declare for easy read

#define MAXDB                           50
#define LOOP                            while(1)
#define LABEL                           (option ? "customer" : "product")
#define TYPE                            (option ? 1 : 0)
#define LAST_INDEX                      countOfDatabase            (databaseMain[TYPE])
#define DATABASE_OUTPUT_DISPLAY         databaseOutputDisplay      (option, LAST_INDEX, databaseMain[TYPE], databaseCatalogue)
#define DATABASE_INPUT                  databaseInput              (option, index, LAST_INDEX, databaseMain[TYPE], inputOption, databaseCatalogue)
#define DATABASE_CATALOGUE_DISPLAY      databaseCatalogueDisplay   (option, databaseCatalogue)
#define DATABASE_SORT_BY_FIELD          databaseSortByField        (option, sortChoice - 1, LAST_INDEX, databaseMain[TYPE])
#define DATABASE_SEARCH_BY_FIELD        databaseSearchByField      (option, searchChoice, LAST_INDEX, databaseSearchIndex, databaseMain[TYPE], databaseCatalogue)
#define DATABASE_RESULT_LIST_DISPLAY    databaseResultListDisplay  (option, LAST_INDEX, databaseSearchIndex, databaseMain[TYPE], databaseCatalogue)
#define DATABASE_EXPORT_TO_FILE         databaseExportToFile       (option, LAST_INDEX, databaseMain[TYPE], databaseCatalogue)
#define DATABASE_FILE_OPEN              databaseFileOpen           (option, isTerminal)
#define DATABASE_DELETE_MATCH_ITEM      databaseDeleteMatchedItem  (option, LAST_INDEX, databaseSearchIndex, databaseMain[TYPE])
#define DATABASE_DELETE_ALL             databaseDeleteAll          (option, LAST_INDEX, databaseMain[TYPE])

// Databases

char databaseMain[2][MAXDB][MAXDB][MAXDB]          
= 
{
    {      // Product Database
        {"chicken",    "10", "30",  "22/10/2023", "22/10/2024"},
        {"beef",       "15", "20",  "15/11/2023", "15/11/2024"},
        {"pork",       "12", "25",  "18/12/2023", "18/12/2024"},
        {"fish",       "8",  "40",  "05/09/2023", "05/09/2024"},
        {"vegetables", "5",  "50",  "30/11/2023", "30/11/2024"},
        {"fruits",     "6",  "60",  "12/12/2023", "12/12/2024"},
        {"bread",      "3",  "70",  "01/01/2023", "01/01/2024"},
        {"milk",       "2",  "80",  "02/02/2023", "02/02/2024"},
        {"cheese",     "4",  "90",  "03/03/2023", "03/03/2024"},
        {"eggs",       "1",  "100", "04/04/2023", "04/04/2024"}
    },
    {      // Customer Database
        {"John",    "25", "1234567890", "1000", "50"},
        {"Alice",   "30", "9876543210", "2000", "100"},
        {"Bob",     "35", "5555555555", "1500", "75"},
        {"Emma",    "28", "9999999999", "1800", "90"},
        {"Michael", "40", "1111111111", "1200", "60"},
        {"Sophia",  "32", "4444444444", "2500", "125"},
        {"William", "27", "6666666666", "900",  "45"},
        {"Olivia",  "31", "2222222222", "1700", "85"},
        {"James",   "29", "8888888888", "1400", "70"},
        {"Emily",   "33", "3333333333", "2200", "110"}
    }
};

char databaseCatalogue[2][5][20] 
=
{
    {"name", "stock", "price",       "manufacturing date", "expiry date"}, // Product Database
    {"name", "age",   "phone number","acconut balance",    "bonus point"}, // Customer Database
};

int databaseSearchIndex[MAXDB]; // Store the boolen of search result

// Main program
int main() {
    // int columns, rows;
    printf("\e[1;1H\e[2J");
    // hidecursor();

    // LOOP 
    // {
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

    LOOP 
    {
        controlMenu();
        int choiceMainMenu = getch() - '0' - 1;

        switch (choiceMainMenu) 
        {
            case 0:
            case 1:
                mainMenu(-1, -1, choiceMainMenu, databaseMain);
                break;
            case 2: 
                printf("\n\n                                        Goodbye!\n\n");
                sleep(2);
                printf("\e[1;1H\e[2J");
                return 0;
            default:
                printf("\n\n                                        Invalid choice. Please try again.");
                sleep(1);
                break;
        }
    }

    return 0;
}

// Function Definitions

int countOfDatabase(char databaseParameter[MAXDB][MAXDB][MAXDB]) 
{
    for (int i = MAXDB - 1; i > -1; i--) 
        if (strcmp(databaseParameter[i][0], "\0") != 0)
            return i;
    
    return -1;
}

int databaseInput(int databaseType, int index, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB], char option[5], char databaseCatalogueParameter[2][5][20]) 
{
    char tempHolder[5][MAXDB] = {};
    printf("\n");

    if (strcmp(option, "6") == 0) 
        return 2; // Back a step

    // Assign value to temp variable
    for (int i = 0; i < 5; i++) 
    {
        if (index == -1 && strcmp(option, "-1") == 0) 
        {
            printf("                   Enter %s or q to back:  ", databaseCatalogueParameter[databaseType][i]);
            scanf("%s", tempHolder[i]);
            if (strcmp(tempHolder[i], "q") == 0)
                return 0; // Quit
        }
        else if (0 < option[i] - 48 && option[i] - 48 < 6)
        {
            printf("                   Enter %s or q to back: ", databaseCatalogueParameter[databaseType][option[i] - 49]);
            scanf("%s", tempHolder[i]);
            if (strcmp(tempHolder[i], "q") == 0)
                return 0; // Quit
        }
    }

    // Check the input
    for (int i = 0; i < 5; i++)
        if ((0 < option[i] - 48 && option[i] - 48 < 6) || strcmp(option, "-1") == 0)
        {
            if (i == 1 && atoi(tempHolder[i]) < 0)
                return -1; // Invalid
            if (i == 2 && atoi(tempHolder[i]) < 0)
                return -1; // Invalid
            if (i == 3 && verifyDateStringInput_ddmmyyyy(tempHolder[i]) == -1)
                return -1; // Invalid
            if (i == 4 && verifyDateStringInput_ddmmyyyy(tempHolder[i]) == -1)
                return -1; // Invalid
        }

    // Assaign temp value to database
    for (int i = 0; i < 5; i++)
    {
        if (index == -1 && strcmp(option, "-1") == 0)
            strcpy(databaseParameter[lastIndex + 1][i], tempHolder[i]);
        else if (0 < option[i] - 48 && option[i] - 48 < 6)
            strcpy(databaseParameter[index][option[i] - 49], tempHolder[i]);
    }

    return 1; // Valid option    
}

void databaseOutputDisplay(int databaseType, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogueParameter[2][5][20]) 
{
    int j = 1;
    printf("\e[1;1H\e[2J"); // Clear the terminal
    printf("************************************************************************************************************************\n");
    printf("*                                                 %-14s                                                     *\n", databaseType ? "Customer Database" : "Product Database");
    printf("************************************************************************************************************************\n");
    printf("*                                                                                                                      *\n");
    printf("*   no. |   %-4s            |   %-5s   |   %-12s    |   %-18s   |   %-11s                   *\n", databaseCatalogueParameter[databaseType][0], databaseCatalogueParameter[databaseType][1], databaseCatalogueParameter[databaseType][2], databaseCatalogueParameter[databaseType][3], databaseCatalogueParameter[databaseType][4]);
    printf("*                                                                                                                      *\n");
    for (int i = 0; i <= lastIndex; i++) 
        if (strcmp(databaseParameter[i][0], "\0") != 0) 
        {
            printf("*   %-3d |   %-14s  |   %-5s   |   %-12s    |   %-18s   |   %-11s                   *\n", j, databaseParameter[i][0], databaseParameter[i][1], databaseParameter[i][2], databaseParameter[i][3], databaseParameter[i][4]);
            j++;
        }
    printf("*                                                                                                                      *\n");
    printf("************************************************************************************************************************\n\n");
}

void databaseCatalogueDisplay(int databaseType, char databaseCatalogueParameter[2][5][20])
{
    for (int i = 0; i < 5; i++)
        printf("                             %d. %s\n", i + 1, databaseCatalogueParameter[databaseType][i]);
    printf("                             6. back\n");
}

void databaseRowSwap(int firstIndex, int secondIndex, char databaseParameter[MAXDB][MAXDB][MAXDB])
{
    char tempHolder[5][MAXDB] = {};
    for (int i = 0; i < 5; i++)
    {
        strcpy(tempHolder[i], databaseParameter[firstIndex][i]);
        strcpy(databaseParameter[firstIndex][i], databaseParameter[secondIndex][i]);
        strcpy(databaseParameter[secondIndex][i], tempHolder[i]);
    }
}

int databaseSortByField(int databaseType, int choiceSort, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB])
{
    if (-1 > choiceSort || choiceSort > 5)
        return -1; // Invalid
    if (choiceSort == -1)
        return 0; // Back
    if (-1 < choiceSort && choiceSort < 5)
        for (int i = 0; i <= lastIndex; i++)
            for (int j = i + 1; j <= lastIndex; j++)
            {
                if ('0' <= databaseParameter[i][choiceSort][0] && databaseParameter[i][choiceSort][0] <= '9' && databaseParameter[i][choiceSort][2] != '/') // Sort number string
                {   
                    if (atoi(databaseParameter[i][choiceSort]) > atoi(databaseParameter[j][choiceSort]))
                        databaseRowSwap(i, j, databaseParameter);
                }
                else if (databaseParameter[i][choiceSort][2] == '/') // Sort date string dd/mm/yyyy
                {
                    char tempFirstYear[5],  tempSecondYear[5];
                    char tempFirstMonth[3], tempSecondMonth[3];
                    char tempFirstDay[3],   tempSecondDay[3];

                    // Get substring
                    memcpy(tempFirstYear, &databaseParameter[i][choiceSort][6], 4);
                    tempFirstYear[4] = '\0';
                    memcpy(tempSecondYear, &databaseParameter[j][choiceSort][6], 4);
                    tempSecondYear[4] = '\0';
                    memcpy(tempFirstMonth, &databaseParameter[i][choiceSort][3], 2);
                    tempFirstMonth[2] = '\0';
                    memcpy(tempSecondMonth, &databaseParameter[j][choiceSort][3], 2);
                    tempSecondMonth[2] = '\0';
                    memcpy(tempFirstDay, &databaseParameter[i][choiceSort][0], 2);
                    tempFirstDay[2] = '\0';
                    memcpy(tempSecondDay, &databaseParameter[j][choiceSort][0], 2);
                    tempSecondDay[2] = '\0';                    

                    if (atoi(tempFirstYear) > atoi(tempSecondYear))
                        databaseRowSwap(i, j, databaseParameter);
                    else if (atoi(tempFirstYear) == atoi(tempSecondYear) && atoi(tempFirstMonth) > atoi(tempSecondMonth))
                        databaseRowSwap(i, j, databaseParameter);
                    else if (atoi(tempFirstYear) == atoi(tempSecondYear) && atoi(tempFirstMonth) == atoi(tempSecondMonth) && atoi(tempFirstDay) > atoi(tempSecondDay))
                        databaseRowSwap(i, j, databaseParameter);
                }
                else  // Sort alphabet string
                {   
                    if (strcmp(databaseParameter[i][choiceSort], databaseParameter[j][choiceSort]) > 0)
                        databaseRowSwap(i, j, databaseParameter);
                }
            }


    return 1; // Valid
}

int databaseSearchByField(int databaseType, int choiceSearch, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogue[2][5][20])
{
    int count = 0;
    char searchParameter[MAXDB];
    memset(databaseSearchIndex, 0, MAXDB); // Clear the databaseSearchIndex
    if (-1 > choiceSearch || choiceSearch > 5)
        return -1; // Invalid
    if (choiceSearch == 5)
        return 0; // Quit

    printf("\n                   Enter %s to search or q to go back: ", databaseCatalogue[databaseType][choiceSearch]);
    scanf("%s", searchParameter);

    if (strcmp(searchParameter, "q") == 0)
        return 2; // Back

    for (int i = 0; i <= lastIndex; i++)
    {
        if (strcmp(databaseParameter[i][choiceSearch], searchParameter) == 0)
        {
            databaseSearchIndex[i] = 1;
            count++;
        }
    }
    if (count == 0)
        return 2; // Not found
    return 1; // Valid
}

void databaseResultListDisplay(int databaseType, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogue[2][5][20])
{
    int j = 1;
    printf("\e[1;1H\e[2J"); // Clear the terminal
    printf("************************************************************************************************************************\n");
    printf("*                                               %-14s                                                    *\n", databaseType ? "Customer Search List" : "Product Search List");
    printf("************************************************************************************************************************\n");
    printf("*                                                                                                                      *\n");
    printf("*   no. |   %-4s            |   %-5s   |   %-12s    |   %-18s   |   %-11s                   *\n", databaseCatalogue[databaseType][0], databaseCatalogue[databaseType][1], databaseCatalogue[databaseType][2], databaseCatalogue[databaseType][3], databaseCatalogue[databaseType][4]);
    printf("*                                                                                                                      *\n");
    for (int i = 0; i <= lastIndex; i++)
        if (databaseSearchIndex[i] == 1)
        {
            printf("*   %-3d |   %-14s  |   %-5s   |   %-12s    |   %-18s   |   %-11s                   *\n", j, databaseParameter[i][0], databaseParameter[i][1], databaseParameter[i][2], databaseParameter[i][3], databaseParameter[i][4]);
            j++;
        }
    printf("*                                                                                                                      *\n");
    printf("************************************************************************************************************************\n\n");
}

int databaseExportToFile(int databaseType, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogue[2][5][20])
{
    FILE *items_txt;
    int j = 1;
    if (databaseType)
        items_txt = fopen("customer database.txt", "w");
    else
        items_txt = fopen("product database.txt", "w");

    fprintf(items_txt, "********************************************************************************************************\n");
    fprintf(items_txt, "*                                       %-14s                                               *\n", databaseType ? "Customer Database" : "Product Database");
    fprintf(items_txt, "********************************************************************************************************\n");
    fprintf(items_txt, "*                                                                                                      *\n");
    fprintf(items_txt, "*   no. |   %-4s            |   %-5s   |   %-12s    |   %-18s   |   %-11s   *\n", databaseCatalogue[databaseType][0], databaseCatalogue[databaseType][1], databaseCatalogue[databaseType][2], databaseCatalogue[databaseType][3], databaseCatalogue[databaseType][4]);
    fprintf(items_txt, "*                                                                                                      *\n");
    for (int i = 0; i <= lastIndex; i++)
        if (strcmp(databaseParameter[i][0], "\0") != 0)
        {
            fprintf(items_txt, "*   %-3d |   %-14s  |   %-5s   |   %-12s    |   %-18s   |   %-11s   *\n", j, databaseParameter[i][0], databaseParameter[i][1], databaseParameter[i][2], databaseParameter[i][3], databaseParameter[i][4]);
            j++;
        }
    fprintf(items_txt, "*                                                                                                      *\n");
    fprintf(items_txt, "********************************************************************************************************\n");
    fclose(items_txt);

    return 1; // Valid
}

int databaseFileOpen(int databaseType, char isTerminal)
{
    if (isTerminal == 'o' || isTerminal == 'O')
        if (databaseType)
            system("notepad \"customer database.txt\"");
        else
            system("notepad \"product database.txt\"");

    else if (isTerminal == 't' || isTerminal == 'T')
    {
        FILE *items_txt;
        if (databaseType)
            items_txt = fopen("customer database.txt", "r");
        else
            items_txt = fopen("product database.txt", "r");

        if (items_txt == NULL) 
        {
            printf("File does not exist!");
            return -1; // Invalid
        }
        printf("\n");

        char c;
        printf("\e[1;1H\e[2J");
        while ((c = fgetc(items_txt)) != EOF) 
            printf("%c", c);

        fclose(items_txt);
    }
        
    return 1; // Valid
}

int databaseFoundItem(int databaseSearchIndex[MAXDB])
{
    int count = 0;
    for (int i = 0; i < MAXDB; i++)
        if (databaseSearchIndex[i] == 1)
            count++;

    return count;
}


int databaseDeleteMatchedItem(int databaseType, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][MAXDB][MAXDB])
{
    for (int i = 0; i <= lastIndex; i++)
        if (databaseSearchIndex[i] == 1)
            for (int j = 0; j < 5; j++)
                strcpy(databaseParameter[i][j], "\0");

    return 1; // Valid
}

void databaseDeleteAll(int databaseType, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB])
{
    for (int i = 0; i <= lastIndex; i++)
        for (int j = 0; j < 5; j++)
            strcpy(databaseParameter[i][j], "\0");
}

int findInvalidInput(char inputString[5])
{
    for (int i = 0; i < 5; i++)
        if (inputString[i]== '0' || inputString[i] == '7' || inputString[i] == '8' || inputString[i] == '9')
            return 1;
}

int verifyDateStringInput_ddmmyyyy(char dateString[10])
{
    if (strlen(dateString) != 10)
        return -1; // Invalid

    if (dateString[2] != '/' || dateString[5] != '/')
        return -1; // Invalid

    for (int i = 0; i < 10; i++)
        if (i != 2 && i != 5)
            if (dateString[i] < '0' || dateString[i] > '9')
                return -1; // Invalid

    char tempDay[3], tempMonth[3], tempYear[5];
    memcpy(tempDay, &dateString[0], 2);
    tempDay[2] = '\0';
    memcpy(tempMonth, &dateString[3], 2);
    tempMonth[2] = '\0';
    memcpy(tempYear, &dateString[6], 4);
    tempYear[4] = '\0';

    if (atoi(tempDay) < 1 || atoi(tempDay) > 31)
        return -1; // Invalid

    if (atoi(tempMonth) < 1 || atoi(tempMonth) > 12)
        return -1; // Invalid

    if (atoi(tempYear) < 1000 || atoi(tempYear) > 9999)
        return -1; // Invalid

    return 1;
}

// Main Program
int mainMenu(int columns, int rows, int option, char databaseMain[2][MAXDB][MAXDB][MAXDB]) 
{
    LOOP 
    {
        if (option)
            customerMenuDisplay();
        else
            productMenuDisplay(); 

        int mainMenuChoice = getch() - '0';
        
        switch (mainMenuChoice) 
        {
            case 1: // Display all items
            { 
                DATABASE_OUTPUT_DISPLAY;

                printf("\n                             Press any keys to return to main %s menu     ", LABEL);
                getch();
                break;
            }

            case 2: // Add an item
            {
                LOOP
                {
                    char inputOption[] = "-1";
                    int index = -1;

                    DATABASE_OUTPUT_DISPLAY;

                    int tempReturn = DATABASE_INPUT;

                    if (tempReturn == 1) 
                    {   
                        printf("\n                                              Add item successfully!\n");
                        printf("\n                           Press r to refresh the list, any keys to return to %s menu    ", LABEL);
                        char endChoice = getch();
                        if (endChoice == 'R' || endChoice == 'r') 
                        {
                            DATABASE_OUTPUT_DISPLAY;

                            printf("\n                               Press any keys to return to %s menu     ", LABEL);
                            getch();
                            printf("\n                                            Returning to %s menu...", LABEL);
                            sleep(1);
                            break;
                        }
                        else 
                        {
                            printf("\n\n                                          Returning to %s menu...", LABEL);
                            sleep(1);
                            break;
                        }
                    }
                    else if (tempReturn == -1)
                    {
                        printf("\n                                     Please check the input!");
                        printf("\n                          Do you want to retry? (yes/no) (press y or n)");
                        char retryChoice = getch();
                        if (retryChoice == 'n')
                            break;
                    }
                }
                break;
            }

            case 3: // Sort items by fields
            { 
                LOOP 
                {
                    DATABASE_OUTPUT_DISPLAY;
                    DATABASE_CATALOGUE_DISPLAY;

                    printf("\n                          Which field do you want to sort (Press a listed number)    ");
                    int sortChoice = getch() - '0';   

                    int tempReturn = DATABASE_SORT_BY_FIELD;    
                      
                    if (tempReturn) 
                    {
                        printf("\n                          Sort by %s successfully!\n", databaseCatalogue[option][sortChoice - 1]);
                        printf("\n                          Press any keys to return to %s menu     ", LABEL);
                        getch();
                        break;
                    } 
                    else if (!tempReturn) 
                    {
                        printf("\n\n                                     Enter a valid option!");
                        sleep(1);                        
                    }
                    else
                        break;
                }
                break;
            }

            case 4: // Search by fields
            { 
                LOOP 
                {
                    DATABASE_OUTPUT_DISPLAY;
                    DATABASE_CATALOGUE_DISPLAY;

                    printf("\n                   Which field do you want to search (Press a listed number)     ");
                    int searchChoice = getch() - '0' - 1; 
                    printf("\n");

                    int tempReturn = DATABASE_SEARCH_BY_FIELD;

                    if (tempReturn) 
                    {
                        DATABASE_RESULT_LIST_DISPLAY;

                        printf("\n                        Press r to search again, any p to return to %s menu     ", LABEL);
                        char endChoice = getch();

                        if (endChoice != 'r' && endChoice != 'R') 
                            break;
                    } 
                    else if (tempReturn == -1) 
                    {
                        printf("\n                                     Enter a valid option!");
                        sleep(1);
                    } 
                    else if (tempReturn == 2) {}
                    else
                        break;
                }
                break;

            }

            case 5: // Print all the data to a text file
            { 
                printf("\n");

                DATABASE_EXPORT_TO_FILE;

                printf("\n                           %s database exported to %s items.txt!", LABEL, LABEL);
                printf("\n                           Press o to open file, p to return to %s menu    ", LABEL);
                char endChoide = getch();
                printf("\n");
                if (endChoide == 'O' || endChoide == 'o') 
                {
                    printf("\n                           Press t to open in terminal, o to open file    ");
                    char isTerminal = getch();

                    DATABASE_FILE_OPEN;

                    printf("\n                           Press p to return to %s menu     ", LABEL);
                    getch();
                }
                else 
                {
                    printf("\n                                  Returning to %s menu...", LABEL);
                    sleep(1);
                }
                break;
            }

            case 6: // Delete the matched item
            { 
                LOOP 
                {
                    DATABASE_OUTPUT_DISPLAY;
                    DATABASE_CATALOGUE_DISPLAY;

                    printf("\n                   Which field do you want an item to delete in  (Press a listed number)     ");

                    int searchChoice = getch() - '0' - 1;
                    int tempSearchReturn = DATABASE_SEARCH_BY_FIELD;

                    printf("\n");
                    if (tempSearchReturn) 
                    {
                        int foundItem = databaseFoundItem(databaseSearchIndex);

                        DATABASE_RESULT_LIST_DISPLAY;

                        printf("\n                     Do you want to delete all found items? (yes/no) (Press y or n)     ");
                        char deleteFinalChoice = getch();
                        if (deleteFinalChoice == 'y')
                        {
                            DATABASE_DELETE_MATCH_ITEM;

                            printf("\n\n                     Press c to continue deleting, p to return to %s menu     ", LABEL);
                            char continueChoice = getch();

                            if (continueChoice != 'C' && continueChoice != 'c') 
                                break;
                        }
                    } 
                    else if (tempSearchReturn == -1) 
                    {
                        printf("\n                                     Enter a valid option!");
                        sleep(1);
                    } 
                    else if (tempSearchReturn == 2)
                    {
                        printf("                                            Not found!");
                        sleep(3);
                    }
                    else 
                        break;                 
                }
                break;
            }

            case 7: // Delete all data
            { 
                DATABASE_OUTPUT_DISPLAY;

                printf("\n                     Do you want to delete all items? (yes/no) (Press y or n)     ");
                char deleteAllChoice = getch();

                if (deleteAllChoice == 'y') 
                {
                    DATABASE_DELETE_ALL;

                    printf("\n\n                     All items deleted!");
                } 
                else 
                    printf("\n\n                     No items deleted!");
                
                printf("\n\n                      Press p to return to %s menu     ", LABEL);
                getch();
                break;
            }

            case 8: // Modify an item
            { 
                LOOP
                {
                    int isQuit = 0;

                    DATABASE_OUTPUT_DISPLAY;

                    printf("\n                    Enter the index of the item you want to modify or 0 to back to %s menu: ", LABEL);
                    int modifyIndex;
                    scanf("%d", &modifyIndex);

                    if (modifyIndex == 0)
                        break;

                    if (modifyIndex < 1 || modifyIndex > LAST_INDEX + 1)
                    {
                        printf("\n                                     Enter a valid option!");
                        sleep(1);
                        continue;
                    }

                    memset(databaseSearchIndex, 0, MAXDB);
                    databaseSearchIndex[modifyIndex - 1] = 1;

                    LOOP
                    {
                        DATABASE_RESULT_LIST_DISPLAY;
                        DATABASE_CATALOGUE_DISPLAY;

                        printf("\n                   Which field do you want to modify (Enter the string of number or 6 to back)     ");
                        char inputOption[5];
                        int index = modifyIndex - 1;
                        scanf("%s", inputOption);

                        if (findInvalidInput(inputOption) == 1)
                        {
                            printf("\n                                            Enter a valid option!");
                            sleep(1);
                            continue;
                        }

                        int tempDBInputRetutn = DATABASE_INPUT;
                        if (tempDBInputRetutn == 1) 
                        {
                            printf("\n                                            Modify item successfully!\n");
                            printf("\n                            Press r to refresh the list, p to return to %s menu    ", LABEL);
                            char endChoice = getch();
                            if (endChoice == 'R' || endChoice == 'r') 
                            {
                                DATABASE_OUTPUT_DISPLAY;

                                printf("\n                            Press any keys to continue edit others, p to return to %s menu     ", LABEL);
                                char continueModify = getch();
                                if (continueModify == 'p')
                                {
                                    printf("\n\n                                            Returning to %s menu...", LABEL);
                                    isQuit = 1;
                                    sleep(1);
                                    break;
                                }
                                else 
                                    break;
                            }
                            else 
                            {
                                isQuit = 1;
                                printf("\n\n                                            Returning to %s menu...", LABEL);
                                sleep(1);
                                break;
                            }
                        }
                        else if (tempDBInputRetutn == 2)
                            break;
                    }
                    if (isQuit == 1)
                        break;
                }
                break;
            }
            
            case 9: // Quit
                break;

            default: // Invalid option
            { 
                printf("\n\n                                     Enter a valid option!");
                sleep(1);
                break;
            }
        }

        if (mainMenuChoice == 9) // End program
        { 
            printf("\n                                       Returning...");
            sleep(1);
            return 1;
        }   
    }
}

// Banner

void controlMenu() {
    printf("\e[1;1H\e[2J"); // Clear the terminal
    printf("************************************************************************************************************************\n");
    printf("*                                                 Control menu                                                         *\n");
    printf("************************************************************************************************************************\n");
    printf("*                                                                                                                      *\n");
    printf("*                                               1. Product.                                                            *\n");
    printf("*                                               2. Customer.                                                           *\n");
    printf("*                                               3. Quit.                                                               *\n");
    printf("*                                                                                                                      *\n");
    printf("************************************************************************************************************************\n");
    printf("\n                                        Press a number to process         ");
}

void productMenuDisplay() 
{
    printf("\e[1;1H\e[2J"); // Clear the terminal
    printf("************************************************************************************************************************\n");
    printf("*                                                  Product Menu                                                        *\n");
    printf("************************************************************************************************************************\n");
    printf("*                                                                                                                      *\n");
    printf("*                                             1. Display all items.                                                    *\n");
    printf("*                                             2. Add an item.                                                          *\n");
    printf("*                                             3. Sort all items.                                                       *\n");
    printf("*                                             4. Look for an item.                                                     *\n");
    printf("*                                             5. Export data to a text file.                                           *\n");
    printf("*                                             6. Delete matched item.                                                  *\n");
    printf("*                                             7. Delete all items.                                                     *\n");
    printf("*                                             8. Modify an item.                                                       *\n");
    printf("*                                             9. Back.                                                                 *\n");
    printf("*                                                                                                                      *\n");
    printf("************************************************************************************************************************\n");
    printf("\n\n                                       Press a option to process         ");
}

void customerMenuDisplay()
{
    printf("\e[1;1H\e[2J"); // Clear the terminal
    printf("************************************************************************************************************************\n");
    printf("*                                                  Customer Menu                                                       *\n");
    printf("************************************************************************************************************************\n");
    printf("*                                                                                                                      *\n");
    printf("*                                            1. Display all customers.                                                 *\n");
    printf("*                                            2. Add a customer.                                                        *\n");
    printf("*                                            3. Sort all customers.                                                    *\n");
    printf("*                                            4. Look for a customer.                                                   *\n");
    printf("*                                            5. Export data to a text file.                                            *\n");
    printf("*                                            6. Delete matched customer.                                               *\n");
    printf("*                                            7. Delete all customers.                                                  *\n");
    printf("*                                            8. Modify an item                                                         *\n");
    printf("*                                            9. Back                                                                   *\n");
    printf("*                                                                                                                      *\n");
    printf("************************************************************************************************************************\n");
    printf("\n\n                                       Press a option to process         ");
}
