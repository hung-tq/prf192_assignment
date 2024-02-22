#pragma once

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAXDB                           50

extern char databaseCatalogue[2][5][20];
extern char databaseMain[2][MAXDB][MAXDB][MAXDB];
extern int  databaseSearchIndex[MAXDB];

int mainMenu(int columns, int rows, int option, char databaseMain[2][MAXDB][MAXDB][MAXDB]); 

void controlMenu();
void productMenuDisplay();
void customerMenuDisplay();

int  countOfDatabase            (char databaseParameter[MAXDB][MAXDB][MAXDB]);
int  databaseInput              (int databaseType, int index, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB], char option[5], char databaseCatalogueParameter[2][5][20]);
void databaseOutputDisplay      (int databaseType, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogueParameter[2][5][20]);
void databaseCatalogueDisplay   (int databaseType, char databaseCatalogueParameter[2][5][20]);
void databaseRowSwap            (int firstIndex, int secondIndex, char databaseParameter[MAXDB][MAXDB][MAXDB]);
int  databaseSortByField        (int databaseType, int choiceSort, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB]);
int  databaseSearchByField      (int databaseType, int choiceSearch, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogue[2][5][20]);
void databaseResultListDisplay  (int databaseType, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogue[2][5][20]);
int  databaseExportToFile       (int databaseType, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogue[2][5][20]);
int  databaseFileOpen           (int databaseType, char isTerminal);
int  databaseFoundItem          (int databaseSearchIndex[MAXDB]);
int  databaseDeleteMatchedItem  (int databaseType, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][MAXDB][MAXDB]);
void databaseDeleteAll          (int databaseType, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB]);



#endif // FUNCTIONS_H
