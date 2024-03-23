#pragma once

#define MAXDB 50

int  mainMenu                        (int option, char databaseMain[2][MAXDB][5][MAXDB], char databaseCatalogue[2][5][20], int databaseSearchIndex[MAXDB]); 

void controlMenu();
void productMenuDisplay();
void customerMenuDisplay();

int  countOfDatabase                 (char databaseParameter[MAXDB][5][MAXDB]);
int  databaseInput                   (int databaseType, int index, int lastIndex, char databaseParameter[MAXDB][5][MAXDB], char option[6], char databaseCatalogueParameter[2][5][20]);
void databaseOutputDisplay           (int databaseType, int lastIndex, int isDisplayResult, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][5][MAXDB], char databaseCatalogueParameter[2][5][20]);
void databaseCatalogueDisplay        (int databaseType, char databaseCatalogueParameter[2][5][20]);
void databaseRowSwap                 (int firstIndex, int secondIndex, char databaseParameter[MAXDB][5][MAXDB]);
int  databaseSortByField             (int databaseType, int choiceSort, int lastIndex, char databaseParameter[MAXDB][5][MAXDB]);
int  databaseSearchByField           (int databaseType, int choiceSearch, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][5][MAXDB], char databaseCatalogue[2][5][20]);
void databaseResultListDisplay       (int databaseType, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogue[2][5][20]);
int  databaseExportToFile            (int databaseType, int lastIndex, char databaseParameter[MAXDB][5][MAXDB], char databaseCatalogue[2][5][20]);
int  databaseFileOpen                (int databaseType, char isTerminal);
int  databaseFoundItem               (int databaseSearchIndex[MAXDB]);
int  databaseDeleteMatchedItem       (int databaseType, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][5][MAXDB]);
void databaseDeleteAll               (int databaseType, int lastIndex, char databaseParameter[MAXDB][5][MAXDB]);
int  findInvalidInput                (char inputString[6]);
int  verifyDateStringInput_ddmmyyyy  (char dateString[10]);
void trimWhiteSpace                  (char *str);
int  isDigitString                   (char *input);

// MAIN_H