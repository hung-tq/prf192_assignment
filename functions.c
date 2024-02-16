#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXDB 50


int countOfDatabase(char parameter_database[MAXDB][MAXDB][MAXDB]) 
{
    for (int i = MAXDB - 1; i > -1; i--) 
        if (strcmp(parameter_database[i][0], "\0") != 0)
            return i;
    
    return -1;
}

int databaseInput(int databaseType, int index, int lastIndex, char parameter_database[MAXDB][MAXDB][MAXDB], char option[5], char database_catalogue[2][5][20]) 
{
    char tempHolder[5][MAXDB] = {};
    printf("\n");

    for (int i = 0; i < 5; i++) 
    {
        if (index == -1 && strcmp(option, "-1") == 0) 
        {
            printf("                   Enter %s or q to quit:  ", database_catalogue[databaseType][i]);
            scanf("%s", tempHolder[i]);
            if (strcmp(tempHolder[i], "q") == 0)
                return 0; // Quit
        }
        else if (0 < option[i] - 48 && option[i] - 48 < 6)
        {
            printf("                   Enter %s or q to quit: ", database_catalogue[databaseType][option[i] - 49]);
            scanf("%s", tempHolder[i]);
            if (strcmp(tempHolder[i], "q") == 0)
                return 0; // Quit
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (index == -1 && strcmp(option, "-1") == 0)
            strcpy(parameter_database[lastIndex + 1][i], tempHolder[i]);
        else if (0 < option[i] - 48 && option[i] - 48 < 6)
            strcpy(parameter_database[index][option[i] - 49], tempHolder[i]);
    }

    return 1; // Valid option    
}

void databaseOutputDisplay(int databaseType, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogueParameter[2][5][20]) 
{
    int j = 1;
    system("cls"); // Clear the terminal
    printf("********************************************************************************************************\n");
    printf("*                                       %-14s                                              *\n", databaseType ? "Product Database" : "Customer Database");
    printf("********************************************************************************************************\n");
    printf("*                                                                                                      *\n");
    printf("*   No. |   %-4s            |   %-5s   |   %-12s    |   %-18s   |   %-11s   *\n", databaseCatalogueParameter[databaseType][0], databaseCatalogueParameter[databaseType][1], databaseCatalogueParameter[databaseType][2], databaseCatalogueParameter[databaseType][3], databaseCatalogueParameter[databaseType][4]);
    printf("*                                                                                                      *\n");
    for (int i = 0; i <= lastIndex; i++) 
    {
        if (strcmp(databaseParameter[i][0], "\0") != 0) 
        {
            printf("*   %-3d |   %-14s  |   %-5s   |   %-12s    |   %-18s   |   %-11s   *\n", j, databaseParameter[i][0], databaseParameter[i][1], databaseParameter[i][2], databaseParameter[i][3], databaseParameter[i][4]);
            j++;
        }
    }
    printf("*                                                                                                      *\n");
    printf("********************************************************************************************************\n\n");
}

void databaseCatalogueDisplay(int databaseType, char databaseCatalogueParameter[2][5][20])
{
    for (int i = 0; i < 5; i++)
        printf("                          %d. %s\n", i + 1, databaseCatalogueParameter[databaseType][i]);
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
    for (int i = 0; i <= lastIndex; i++)
    {
        for (int j = i + 1; j <= lastIndex; j++)
        {
            if (strcmp(databaseParameter[i][choiceSort], databaseParameter[j][choiceSort]) > 0)
                databaseRowSwap(i, j, databaseParameter);
        }
    }
    return 1; // Valid
}