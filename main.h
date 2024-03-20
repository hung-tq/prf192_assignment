#pragma once

#define MAXDB 50

int  mainMenu                        (int option, char databaseMain[2][MAXDB][MAXDB][MAXDB]); 

void controlMenu();
void productMenuDisplay();
void customerMenuDisplay();

int  countOfDatabase                 (char databaseParameter[MAXDB][MAXDB][MAXDB]);
int  databaseInput                   (int databaseType, int index, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB], char option[5], char databaseCatalogueParameter[2][5][20]);
void databaseOutputDisplay           (int databaseType, int lastIndex, int isDisplayResult, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogueParameter[2][5][20]);
void databaseCatalogueDisplay        (int databaseType, char databaseCatalogueParameter[2][5][20]);
void databaseRowSwap                 (int firstIndex, int secondIndex, char databaseParameter[MAXDB][MAXDB][MAXDB]);
int  databaseSortByField             (int databaseType, int choiceSort, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB]);
int  databaseSearchByField           (int databaseType, int choiceSearch, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogue[2][5][20]);
void databaseResultListDisplay       (int databaseType, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogue[2][5][20]);
int  databaseExportToFile            (int databaseType, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB], char databaseCatalogue[2][5][20]);
int  databaseFileOpen                (int databaseType, char isTerminal);
int  databaseFoundItem               (int databaseSearchIndex[MAXDB]);
int  databaseDeleteMatchedItem       (int databaseType, int lastIndex, int databaseSearchIndex[MAXDB], char databaseParameter[MAXDB][MAXDB][MAXDB]);
void databaseDeleteAll               (int databaseType, int lastIndex, char databaseParameter[MAXDB][MAXDB][MAXDB]);
int  findInvalidInput                (char inputString[5]);
int  verifyDateStringInput_ddmmyyyy  (char dateString[10]);
void trimWhiteSpace                  (char *str);
int  isDigitString                   (char *input);

// MAIN_H