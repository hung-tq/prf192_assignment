#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

// Include main prototypes
#include "main.h"

// Macro declare for easy read - 14
#define MAXDB                           50
#define LOOP                            while(1)
#define LABEL                           (option ? "customer" : "product")
#define TYPE                            (option ? 1 : 0)
#define LAST_INDEX                      countOfDatabase            (databaseMain[TYPE])
#define DATABASE_OUTPUT_DISPLAY         databaseOutputDisplay      (option, LAST_INDEX, isDisplayResult, databaseSearchIndex, databaseMain[TYPE], databaseCatalogue)
#define DATABASE_INPUT                  databaseInput              (option, index, LAST_INDEX, databaseMain[TYPE], inputOption, databaseCatalogue)
#define DATABASE_CATALOGUE_DISPLAY      databaseCatalogueDisplay   (option, databaseCatalogue)
#define DATABASE_SORT_BY_FIELD          databaseSortByField        (option, sortChoice - 1, LAST_INDEX, databaseMain[TYPE])
#define DATABASE_SEARCH_BY_FIELD        databaseSearchByField      (option, searchChoice, LAST_INDEX, databaseSearchIndex, databaseMain[TYPE], databaseCatalogue)
#define DATABASE_EXPORT_TO_FILE         databaseExportToFile       (option, LAST_INDEX, databaseMain[TYPE], databaseCatalogue)
#define DATABASE_FILE_OPEN              databaseFileOpen           (option, isTerminal)
#define DATABASE_DELETE_MATCH_ITEM      databaseDeleteMatchedItem  (option, LAST_INDEX, databaseSearchIndex, databaseMain[TYPE])
#define DATABASE_DELETE_ALL             databaseDeleteAll          (option, LAST_INDEX, databaseMain[TYPE])

// Main program
int main() {

    // Main database: tables - records - properties - 50 characters length of string
    char databaseMain[2][MAXDB][5][MAXDB]          
    = 
    {
    // Product Database
    {      
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

    // Customer Database
    {      
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

    // Catalogue Databases: tables - propertie names - 20 characters length of string
    char databaseCatalogue[2][5][20] 
    =
    {
    // Product Database Catalogue
    {"name", "stock", "price",       "manufacturing date", "expiry date"},

    // Customer Database Catalogue
    {"name", "age",   "phone number","acconut balance",    "bonus point"}, 
    };

    // Store the boolen of search result - parrallel with the databaseMain
    int databaseSearchIndex[MAXDB]; 

    system("cls");

    // Main Loop
    LOOP 
    {
        controlMenu();

        int choiceMainMenu = getch() - '0' - 1;
        // int choiceMainMenu = 0;

        switch (choiceMainMenu) 
        {
            // Enter the product menu, customer menu
            case 0:
            case 1:
            {
                mainMenu(choiceMainMenu, databaseMain, databaseCatalogue, databaseSearchIndex);
                break;
            }

            // Quiting
            case 2:
            { 
                printf("\n\n                                                  Goodbye!");
                sleep(2);
                system("cls");
                return 0;
            }

            // Invalid option
            default:
            {
                printf("\n\n                                        Invalid choice. Please try again.");
                sleep(1);
                break;
            }
        }
    }

    return 0;
}

// Function Definitions
int countOfDatabase(char databaseParameter[MAXDB][5][MAXDB]) 
{
    // Get last index from the bottom of the table
    for (int i = MAXDB - 1; i > -1; i--) 
        if (strcmp(databaseParameter[i][0], "\0") != 0)
            return i;
    
    return -1;
}

void trimWhiteSpace(char *str) {
    int len = strlen(str);
    
    // Trim trailing white spaces
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n'))
        len--;
    
    // Add null terminator at the new end of the string
    str[len] = '\0';
}

int isDigitString(char *input)
{
    for (int i = 0; i < strlen(input); i++)
        if (input[i] <= '/' || input[i] >= ':')
            return 0;
    return 1;
}

int databaseInput(int databaseType, int index, int lastIndex, char databaseParameter[MAXDB][5][MAXDB], char option[6], char databaseCatalogueParameter[2][5][20]) 
{
    // Clear the buffer
    setbuf(stdin, NULL);

    char tempHolder[5][MAXDB] = {};
    printf("\n");

    // Back a step
    if (strcmp(option, "6") == 0) 
        return 2;

    // Check if the inputOption contains any digit 6
    if (strstr(option, "6") != NULL) 
        return 2;

    // Assign value to temp variable
    for (int i = 0; i < 5; i++) 
    {
        // For add an item function
        if (index == -1 && strcmp(option, "-1") == 0) 
        {
            printf("                      Enter %s or q to back:  ", databaseCatalogueParameter[databaseType][i]);

            // Get the input string and trim all white space
            fgets(tempHolder[i], MAXDB, stdin);
            trimWhiteSpace(tempHolder[i]);

            // Quit
            if (strcmp(tempHolder[i], "q") == 0)
                return 0; 
        }

        // For modify an item function
        else if (0 < option[i] - 48 && option[i] - 48 < 6)
        {
            printf("                      Enter %s or q to back:  ", databaseCatalogueParameter[databaseType][option[i] - 49]);

            // Get the input string and trim all white space
            fgets(tempHolder[i], MAXDB, stdin);
            trimWhiteSpace(tempHolder[i]);

            // Quit
            if (strcmp(tempHolder[i], "q") == 0)
                return 0; 
        }
    }

    // Check the input
    for (int i = 0; i < 5; i++)
    {
        // String length must smaller than 23 characters
        if (strlen(tempHolder[i]) > 23 == 1)
        {
            return -1;
        }

        // Check valid input
        if ((0 < option[i] - 48 && option[i] - 48 < 6) || strcmp(option, "-1") == 0)
        {
            // Check if the input string is digits larger than 0 or not
            if (option[i] - 49 == 1 && (atoi(tempHolder[i]) < 0 || isDigitString(tempHolder[i]) == 0))
            {
                return -1; // Invalid
            }

            // Check if the input string is digits larger than 0 or not
            if (option[i] - 49 == 2 && (atoi(tempHolder[i]) < 0 || isDigitString(tempHolder[i]) == 0))
            {
                return -1; // Invalid
            }

            // Check if the input string is digits larger than 0 or not, or is a true date string
            if (option[i] - 49 == 3 && ((verifyDateStringInput_ddmmyyyy(tempHolder[i]) == -1 && databaseType == 0) || (atoi(tempHolder[i]) < 0 && databaseType == 1)))
            {
                return -1; // Invalid
            }

            // Check if the input string is digits larger than 0 or not, or is a true date string
            if (option[i] - 49 == 4 && ((verifyDateStringInput_ddmmyyyy(tempHolder[i]) == -1 && databaseType == 0) || (atoi(tempHolder[i]) < 0 && databaseType == 1)))
            {
                return -1; // Invalid
            }
        }
    }

    // Assaign temp value to database
    for (int i = 0; i < 5; i++)
    {
        // If there is no inputOption or inputOption == "-1"
        if (index == -1 && strcmp(option, "-1") == 0)
            strcpy(databaseParameter[lastIndex + 1][i], tempHolder[i]);

        // There is inputOption
        else if (0 < option[i] - 48 && option[i] - 48 < 6)
            strcpy(databaseParameter[index][option[i] - 49], tempHolder[i]);
    }

    // Valid option
    return 1;     
}

void databaseOutputDisplay(int databaseType, int lastIndex, int isDisplayResult, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][5][MAXDB], char databaseCatalogueParameter[2][5][20]) 
{
    int j = 1;

    // Clear the terminal
    system("cls"); 

    printf("************************************************************************************************************************\n");
    printf("*                                                 %-20s                                                 *\n", isDisplayResult ? (databaseType ? "Customer Search List" : "Product Search List") : (databaseType ? "Customer Database" : "Product Database"));
    printf("************************************************************************************************************************\n");
    printf("*                                                                                                                      *\n");
    printf("*   no. |   %-15s            |   %-6s   |   %-12s    |   %-18s   |   %-11s       *\n", databaseCatalogueParameter[databaseType][0], databaseCatalogueParameter[databaseType][1], databaseCatalogueParameter[databaseType][2], databaseCatalogueParameter[databaseType][3], databaseCatalogueParameter[databaseType][4]);
    printf("*                                                                                                                      *\n");
    for (int i = 0; i <= lastIndex; i++)
    { 
        // Print all items
        if (isDisplayResult == 0)
        {
            if (strcmp(databaseParameter[i][0], "\0") != 0) 
            {
                printf("*   %-3d |   %-25s  |   %-6s   |   %-12s    |   %-18s   |   %-11s       *\n", j, databaseParameter[i][0], databaseParameter[i][1], databaseParameter[i][2], databaseParameter[i][3], databaseParameter[i][4]);
                j++;
            }
        }

        // Print the result list items
        else
        {
            if (databaseSearchIndex[i] == 1)
            {
                printf("*   %-3d |   %-25s  |   %-6s   |   %-12s    |   %-18s   |   %-11s       *\n", j, databaseParameter[i][0], databaseParameter[i][1], databaseParameter[i][2], databaseParameter[i][3], databaseParameter[i][4]);
                j++;
            }
        }
    }
    printf("*                                                                                                                      *\n");
    printf("************************************************************************************************************************\n\n");
}

void databaseCatalogueDisplay(int databaseType, char databaseCatalogueParameter[2][5][20])
{
    // Display some catalogues: name, ...
    for (int i = 0; i < 5; i++)
        printf("                                %d. %s\n", i + 1, databaseCatalogueParameter[databaseType][i]);
    printf("                                6. back\n"); 
}

void databaseRowSwap(int firstIndex, int secondIndex, char databaseParameter[MAXDB][5][MAXDB])
{
    // Swap two adjacent rows in a table
    char tempHolder[5][MAXDB] = {};
    for (int i = 0; i < 5; i++)
    {
        strcpy(tempHolder[i], databaseParameter[firstIndex][i]);
        strcpy(databaseParameter[firstIndex][i], databaseParameter[secondIndex][i]);
        strcpy(databaseParameter[secondIndex][i], tempHolder[i]);
    }
}

int databaseSortByField(int databaseType, int choiceSort, int lastIndex, char databaseParameter[MAXDB][5][MAXDB])
{
    // Invalid
    if (0 > choiceSort || choiceSort > 5)
        return -1; 
    
    // Back
    if (choiceSort == 5)
        return 0; 

    if (-1 < choiceSort && choiceSort < 5)
        for (int i = 0; i <= lastIndex; i++)
            for (int j = i + 1; j <= lastIndex; j++)
            {

                // Sort number string
                if ('0' <= databaseParameter[i][choiceSort][0] && databaseParameter[i][choiceSort][0] <= '9' && databaseParameter[i][choiceSort][2] != '/') 
                {   
                    if (atoi(databaseParameter[i][choiceSort]) > atoi(databaseParameter[j][choiceSort]))
                        databaseRowSwap(i, j, databaseParameter);
                }

                // Sort date string dd/mm/yyyy
                else if (databaseParameter[i][choiceSort][2] == '/') 
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

                    // Date comapare: year - month - day
                    if (atoi(tempFirstYear) > atoi(tempSecondYear))
                        databaseRowSwap(i, j, databaseParameter);
                    else if (atoi(tempFirstYear) == atoi(tempSecondYear) && atoi(tempFirstMonth) > atoi(tempSecondMonth))
                        databaseRowSwap(i, j, databaseParameter);
                    else if (atoi(tempFirstYear) == atoi(tempSecondYear) && atoi(tempFirstMonth) == atoi(tempSecondMonth) && atoi(tempFirstDay) > atoi(tempSecondDay))
                        databaseRowSwap(i, j, databaseParameter);
                }

                // Sort alphabet string
                else  
                {   
                    if (strcmp(databaseParameter[i][choiceSort], databaseParameter[j][choiceSort]) > 0)
                        databaseRowSwap(i, j, databaseParameter);
                }
            }

    // Valid
    return 1; 
}

int databaseSearchByField(int databaseType, int choiceSearch, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][5][MAXDB], char databaseCatalogue[2][5][20])
{
    int count = 0;
    char searchParameter[MAXDB];

    // Clear the buffer
    setbuf(stdin, NULL);

    // Clear the databaseSearchIndex
    memset(databaseSearchIndex, 0, MAXDB); 
    
    if (0 > choiceSearch || choiceSearch > 5)
        // Invalid
        return -1; 

    if (choiceSearch == 5)
        // Quit
        return 0; 

    printf("\n                                Enter %s to search or q to go back: ", databaseCatalogue[databaseType][choiceSearch]);
    
    // Get the input and trim all white spaces
    fgets(searchParameter, MAXDB, stdin);
    trimWhiteSpace(searchParameter);

    // Back
    if (strcmp(searchParameter, "q") == 0)
        return 2; 

    for (int i = 0; i <= lastIndex; i++)
    {
        if (strcmp(databaseParameter[i][choiceSearch], searchParameter) == 0)
        {
            databaseSearchIndex[i] = 1;
            count++;
        }
    }

    // Not found
    if (count == 0)
        return 3; 

    // Valid
    return 1; 
}

int databaseExportToFile(int databaseType, int lastIndex, char databaseParameter[MAXDB][5][MAXDB], char databaseCatalogueParameter[2][5][20])
{
    FILE *items_txt;
    int j = 1;

    if (databaseType == 1)
        items_txt = fopen("./databases/customer database.txt", "w");
    else
        items_txt = fopen("./databases/product database.txt", "w");

    // Invalid, file not found
    if (items_txt == NULL) 
    {
        return -1; 
    }
    fprintf(items_txt,"************************************************************************************************************************\n");
    fprintf(items_txt,"*                                                 %-20s                                                 *\n",(databaseType ? "Customer Database" : "Product Database"));
    fprintf(items_txt,"************************************************************************************************************************\n");
    fprintf(items_txt,"*                                                                                                                      *\n");
    fprintf(items_txt,"*   no. |   %-15s            |   %-6s   |   %-12s    |   %-18s   |   %-11s       *\n", databaseCatalogueParameter[databaseType][0], databaseCatalogueParameter[databaseType][1], databaseCatalogueParameter[databaseType][2], databaseCatalogueParameter[databaseType][3], databaseCatalogueParameter[databaseType][4]);
    fprintf(items_txt,"*                                                                                                                      *\n");
    for (int i = 0; i <= lastIndex; i++)
    { 
        if (strcmp(databaseParameter[i][0], "\0") != 0) 
        {
            fprintf(items_txt,"*   %-3d |   %-25s  |   %-6s   |   %-12s    |   %-18s   |   %-11s       *\n", j, databaseParameter[i][0], databaseParameter[i][1], databaseParameter[i][2], databaseParameter[i][3], databaseParameter[i][4]);
            j++;
        }
    }
    fprintf(items_txt,"*                                                                                                                      *\n");
    fprintf(items_txt,"************************************************************************************************************************\n");
    fprintf(items_txt, "\nNumbers of records: %d", j - 1);

    fclose(items_txt);

    // Valid
    return 1; 
}

int databaseFileOpen(int databaseType, char isTerminal)
{
    // Open in explorer in windows
    if (isTerminal == 'o' || isTerminal == 'O')
    {
        system("explorer .\\databases");
    }

    // Open in terminal
    else if (isTerminal == 't' || isTerminal == 'T')
    {
        FILE *items_txt;
        if (databaseType == 1)
            items_txt = fopen("./databases/customer database.txt", "r");
        else
            items_txt = fopen("./databases/product database.txt", "r");

        // Invalid, file not found
        if (items_txt == NULL) 
        {
            printf("File does not exist!");
            return -1;
        }
        printf("\n");

        char c;
        system("cls");
        while ((c = fgetc(items_txt)) != EOF) 
            printf("%c", c);

        fclose(items_txt);
    }

    // Valid
    return 1; 
}

int databaseFoundItem(int databaseSearchIndex[MAXDB])
{
    int count = 0;
    for (int i = 0; i < MAXDB; i++)
        if (databaseSearchIndex[i] == 1)
            count++;

    return count;
}

int databaseDeleteMatchedItem(int databaseType, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][5][MAXDB])
{
    // Delete the matched item
    for (int i = 0; i <= lastIndex; i++)
        if (databaseSearchIndex[i] == 1)
            for (int j = 0; j < 5; j++)
                strcpy(databaseParameter[i][j], "\0");

    // Valid
    return 1; 
}

void databaseDeleteAll(int databaseType, int lastIndex, char databaseParameter[MAXDB][5][MAXDB])
{
    // Delete all
    for (int i = 0; i <= lastIndex; i++)
        for (int j = 0; j < 5; j++)
            strcpy(databaseParameter[i][j], "\0");
}

int findInvalidInput(char inputString[6])
{
    // Check if the choice option between 1 and 6, if not return 1
    for (int i = 0; i < strlen(inputString); i++)
        if (inputString[i]== '0' || inputString[i] == '7' || inputString[i] == '8' || inputString[i] == '9')
            return 1;

    // Check the duplicate digits
    for (int i = 0; i < strlen(inputString); i++)
        for (int j = i + 1; j < 5; j++)
            if (inputString[i] == inputString[j])
                return 1;

    // Valid input
    return 0;
}

int verifyDateStringInput_ddmmyyyy(char dateString[10])
{
    // Invalid
    if (strlen(dateString) != 10)
        return -1; 

    // Invalid
    if (dateString[2] != '/' || dateString[5] != '/')
        return -1; 

    // Invalid
    for (int i = 0; i < 10; i++)
        if (i != 2 && i != 5)
            if (dateString[i] < '0' || dateString[i] > '9')
                return -1; 

    // Get day, month, year
    char tempDay[3], tempMonth[3], tempYear[5];
    memcpy(tempDay, &dateString[0], 2);
    tempDay[2] = '\0';
    memcpy(tempMonth, &dateString[3], 2);
    tempMonth[2] = '\0';
    memcpy(tempYear, &dateString[6], 4);
    tempYear[4] = '\0';

    // Invalid
    if (atoi(tempDay) < 1 || atoi(tempDay) > 31)
        return -1; 

    // Invalid
    if (atoi(tempMonth) < 1 || atoi(tempMonth) > 12)
        return -1; 

    // Invalid
    if (atoi(tempYear) < 1000 || atoi(tempYear) > 9999)
        return -1; 

    // Valid
    return 1;
}

// Main Program
int mainMenu(int option, char databaseMain[2][MAXDB][5][MAXDB], char databaseCatalogue[2][5][20], int databaseSearchIndex[MAXDB]) 
{
    LOOP 
    {
        // Clear the buffer
        setbuf(stdin, NULL);

        if (option == 1)
            customerMenuDisplay();
        else
            productMenuDisplay(); 

        int mainMenuChoice = getch() - '0';
        
        switch (mainMenuChoice) 
        {

            // Display all items
            case 1: 
            { 
                int isDisplayResult = 0;
                DATABASE_OUTPUT_DISPLAY;

                printf("\n                                   Press any keys to return to main %s menu", LABEL);
                getch();
                break;
            }

            // Add an item
            case 2: 
            {
                LOOP
                {
                    // Clear the buffer
                    setbuf(stdin, NULL);

                    int isDisplayResult = 0; 
                    char inputOption[] = "-1";
                    int index = -1;

                    DATABASE_OUTPUT_DISPLAY;

                    int tempReturn = DATABASE_INPUT;

                    // Valid input
                    if (tempReturn == 1) 
                    {   
                        printf("\n                                               Add item successfully!\n");
                        printf("\n                             Press r to refresh the list, any keys to return to %s menu", LABEL);
                        char endChoice = getch();
                        if (endChoice == 'R' || endChoice == 'r') 
                        {
                            DATABASE_OUTPUT_DISPLAY;

                            printf("\n                                   Press any keys to return to %s menu", LABEL);
                            getch();
                            break;
                        }
                        else 
                        {
                            printf("\n\n                                         Returning to %s menu...", LABEL);
                            sleep(1);
                            break;
                        }
                    }

                    // Invalid input
                    else if (tempReturn == -1)
                    {
                        printf("\n                                               Please check the input!\n");
                        printf("\n                                     Do you want to retry? (yes/no) (press y or n)");
                        char retryChoice = getch();
                        if (retryChoice == 'n')
                            break;
                    }
                    
                    // Back
                    else
                        break;
                }
                break;
            }

            // Sort items by fields
            case 3: 
            { 
                LOOP 
                {
                    // Clear the buffer
                    setbuf(stdin, NULL);

                    int isDisplayResult = 0;

                    DATABASE_OUTPUT_DISPLAY;

                    DATABASE_CATALOGUE_DISPLAY;

                    printf("\n                                Which field do you want to sort (Press a listed number)");

                    int sortChoice = getch() - '0'; 

                    int tempReturn = DATABASE_SORT_BY_FIELD;    
                      
                    if (tempReturn == 1) 
                    {
                        printf("\n                                Sort by %s successfully!\n", databaseCatalogue[option][sortChoice - 1]);
                        printf("\n                                Press any keys to return to %s menu", LABEL);
                        getch();
                        break;
                    } 
                    else if (tempReturn == -1) 
                    {
                        printf("\n\n                                Enter a valid option!");
                        sleep(1);                        
                    }
                    else
                        break;
                }
                break;
            }

            // Search by fields
            case 4: 
            { 
                LOOP 
                {
                    // Clear the buffer
                    setbuf(stdin, NULL);

                    int isDisplayResult = 0;

                    DATABASE_OUTPUT_DISPLAY;
                    
                    DATABASE_CATALOGUE_DISPLAY;

                    printf("\n                                Which field do you want to search (Press a listed number)");
                    int searchChoice = getch() - '0' - 1; 
                    printf("\n");

                    int tempReturn = DATABASE_SEARCH_BY_FIELD;

                    // If found
                    if (tempReturn == 1) 
                    {
                        isDisplayResult = 1;
                        DATABASE_OUTPUT_DISPLAY;

                        printf("\n                                Press r to search again, any p to return to %s menu", LABEL);
                        char endChoice = getch();

                        if (endChoice != 'r' && endChoice != 'R') 
                            break;
                    }

                    // Invalid input choice 
                    else if (tempReturn == -1) 
                    {
                        printf("\n                                                Enter a valid option!");
                        sleep(1);
                    }

                    // Not found 
                    else if (tempReturn == 3)
                    {
                        isDisplayResult = 1;
                        DATABASE_OUTPUT_DISPLAY;

                        printf("\n                                                       Not found!\n");
                        printf("\n                                 Press r to search again, any p to return to %s menu", LABEL);
                        char endChoice = getch();

                        if (endChoice != 'r' && endChoice != 'R') 
                            break;                        
                    }

                    // Back from catalogue menu
                    else if (tempReturn == 0)
                        break;
                    
                    // Back from input process
                    else
                        continue;
                }
                break;
            }

            // Print all the data to a text file
            case 5: 
            {
                // Clear the buffer
                setbuf(stdin, NULL);

                printf("\n");

                DATABASE_EXPORT_TO_FILE;

                printf("\n                                       %s database exported to %s items.txt!\n", LABEL, LABEL);
                printf("\n                                       Press o to open file, p to return to %s menu", LABEL);
                char endChoide = getch();
                printf("\n");

                // Open file
                if (endChoide == 'O' || endChoide == 'o') 
                {
                    printf("\n                                       Press t to open in terminal, o to reveal in explorer");
                    char isTerminal = getch();

                    DATABASE_FILE_OPEN;

                    printf("\n\n                                       Press p to return to %s menu", LABEL);
                    getch();
                }

                // Return back
                else 
                {
                    printf("\n                                       Returning to %s menu...", LABEL);
                    sleep(1);
                }
                break;
            }

            // Delete the matched item
            case 6: 
            { 
                LOOP 
                {
                    // Clear the buffer
                    setbuf(stdin, NULL);

                    int isDisplayResult = 0;
                    DATABASE_OUTPUT_DISPLAY;
                    DATABASE_CATALOGUE_DISPLAY;

                    printf("\n                                Which field do you want an item to delete in (Press a listed number)");

                    int searchChoice = getch() - '0' - 1;

                    printf("\n");
                    int tempSearchReturn = DATABASE_SEARCH_BY_FIELD;

                    printf("\n");

                    // Found
                    if (tempSearchReturn == 1) 
                    {
                        int foundItem = databaseFoundItem(databaseSearchIndex);

                        isDisplayResult = 1;
                        DATABASE_OUTPUT_DISPLAY;

                        printf("\n                                Do you want to delete all found items? (yes/no) (Press y or n)");
                        char deleteFinalChoice = getch();
                        if (deleteFinalChoice == 'y')
                        {
                            DATABASE_DELETE_MATCH_ITEM;

                            printf("\n\n                              Press c to continue deleting, any keys to return to %s menu", LABEL);
                            char continueChoice = getch();

                            if (continueChoice != 'C' && continueChoice != 'c') 
                                break;
                        }
                    }

                    // Invalid input 
                    else if (tempSearchReturn == -1) 
                    {
                        printf("                                                 Enter a valid option!");
                        sleep(1);
                    } 

                    // Not found
                    else if (tempSearchReturn == 3)
                    {
                        printf("                                            Not found!");
                        sleep(3);
                    }

                    // Back from catalogue display
                    else if (tempSearchReturn == 0)
                        break;

                    // Back from input process
                    else 
                        continue;                    
                }
                break;
            }

            // Delete all data
            case 7:
            { 
                // Clear the buffer
                setbuf(stdin, NULL);

                int isDisplayResult = 0;
                DATABASE_OUTPUT_DISPLAY;

                printf("\n                                  Do you want to delete all items? (yes/no) (Press y or n)");
                char deleteAllChoice = getch();

                // Confirm delete all items
                if (deleteAllChoice == 'y') 
                {
                    DATABASE_DELETE_ALL;

                    printf("\n\n                                  All items deleted!");
                }

                // Reject 
                else 
                {
                    printf("\n\n                                  No items deleted!");
                }

                printf("\n\n                                  Press p to return to %s menu", LABEL);
                getch();
                break;
            }

            // Modify an item
            case 8: 
            { 
                LOOP
                {
                    // Clear the buffer
                    setbuf(stdin, NULL);

                    int isQuit = 0;
                    int isDisplayResult = 0;

                    DATABASE_OUTPUT_DISPLAY;

                    printf("\n                    Enter the index of the item you want to modify or 0 to back to %s menu: ", LABEL);
                    int modifyIndex;
                    scanf("%d", &modifyIndex);

                    // Return back
                    if (modifyIndex == 0)
                        break;

                    // Check if the selected index is availble
                    if (modifyIndex < 1 || modifyIndex > LAST_INDEX + 1)
                    {
                        printf("\n                                               Enter a valid option!");
                        sleep(1);
                        continue;
                    }

                    // Clear the databaseSearchIndex array
                    memset(databaseSearchIndex, 0, MAXDB);

                    // Set the selected index is true for displaying that item
                    databaseSearchIndex[modifyIndex - 1] = 1;

                    LOOP
                    {
                        // Clear the buffer
                        setbuf(stdin, NULL);

                        isDisplayResult = 1;
                        DATABASE_OUTPUT_DISPLAY;
                        DATABASE_CATALOGUE_DISPLAY;

                        printf("\n                      Which field do you want to modify (Enter the string of number or 6 to back)   ");
                        char inputOption[6];
                        int index = modifyIndex - 1;
                        scanf("%s", inputOption);

                        if (findInvalidInput(inputOption) == 1)
                        {
                            printf("\n                                                  Enter a valid option!");
                            sleep(1);
                            continue;
                        }

                        int tempDBInputRetutn = DATABASE_INPUT;

                        // Valid input
                        if (tempDBInputRetutn == 1) 
                        {
                            printf("\n                                               Modify item successfully!\n");
                            printf("\n                                 Press r to refresh the list, p to return to %s menu", LABEL);
                            char endChoice = getch();
                            if (endChoice == 'R' || endChoice == 'r') 
                            {
                                isDisplayResult = 0;
                                DATABASE_OUTPUT_DISPLAY;

                                printf("\n                         Press any keys to continue edit others, p to return to %s menu", LABEL);
                                char continueModify = getch();
                                if (continueModify == 'p')
                                {
                                    printf("\n\n                                             Returning to %s menu...", LABEL);
                                    isQuit = 1;
                                    sleep(1);
                                    break;
                                }
                                else 
                                    break;
                            }

                            // Return back
                            else 
                            {
                                isQuit = 1;
                                printf("\n\n                                            Returning to %s menu...", LABEL);
                                sleep(1);
                                break;
                            }
                        }

                        // Invalid input
                        else if (tempDBInputRetutn == -1)
                        {
                            printf("\n                                               Please check the input!\n");
                            printf("\n                                     Do you want to retry? (yes/no) (press y or n)");
                            char retryChoice = getch();
                            if (retryChoice == 'n')
                                break;
                        } 

                        // Back
                        else if (tempDBInputRetutn == 2)
                        {
                            // isQuit = 1;
                            break;
                        }
                    }
                    if (isQuit == 1)
                        break;
                }
                break;
            }
            
            // Quit
            case 9: 
                break;

            // Invalid option
            default: 
            { 
                printf("\n\n                                              Enter a valid option!");
                sleep(1);
                break;
            }
        }

        // End program
        if (mainMenuChoice == 9) 
        { 
            printf("\n\n                                              Returning...");
            sleep(1);
            return 1;
        }   
    }
}

// Banner main menu
void controlMenu() {
    // Clear the terminal
    system("cls"); 
    printf("************************************************************************************************************************\n");
    printf("*                                                 Control menu                                                         *\n");
    printf("************************************************************************************************************************\n");
    printf("*                                                                                                                      *\n");
    printf("*                                               1. Product.                                                            *\n");
    printf("*                                               2. Customer.                                                           *\n");
    printf("*                                               3. Quit.                                                               *\n");
    printf("*                                                                                                                      *\n");
    printf("************************************************************************************************************************\n");
    printf("\n                                           Press a number to process");
}

// Banner product menu
void productMenuDisplay() 
{
    // Clear the terminal
    system("cls");
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
    printf("\n                                              Press a option to process");
}

// Banner customer menu
void customerMenuDisplay()
{
    // Clear the terminal
    system("cls"); 
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
    printf("\n                                              Press a option to process");
}