#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <Windows.h>
#include <vadefs.h>
#include <string.h>
#include <conio.h>

#include "functions.c"

#define MAXDB 50




// Default database illustration:

// product_database
//
//      Name, Stock, Price, Manufacturing Date, Expiry Date
//

// customer_database
//
//      Name, Age, Phone Number, Account Balance, Bonus Point
//

int main() 
{
    char option[3];

    printf("Welcome to the store!\n");
    printf("Which field would you like to modify:   ");
    scanf("%s", option);
    int lastIndexOfProduct = countOfDatabase(product_database) - 1;

    getch();

    databaseOutput(lastIndexOfProduct, product_database, product_database_catalogue);

    return 0;
}