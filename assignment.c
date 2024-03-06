#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ARRAY 	100
#define MAX_STRING	255

char* strlwr(char* str);
int getUserChoice(void);
void printAllCustomers(int* nos, char names[][MAX_STRING], int* ages, char phone_numbers[][MAX_STRING], int* account_balances, int* bonus_points, int count);
void addCustomer(int* nos, char names[][MAX_STRING], int* ages, char phone_numbers[][MAX_STRING], int* account_balances, int* bonus_points, int* count);
void addCustomersFromFile(int* nos, char names[][MAX_STRING], int* ages, char phone_numbers[][MAX_STRING], int* account_balances, int* bonus_points, int* count);
void sortAllCustomers(int* nos, char names[][MAX_STRING], int* ages, char phone_numbers[][MAX_STRING], int* account_balances, int* bonus_points, int count);
void searchCustomer(int* nos, char names[][MAX_STRING], int* ages, char phone_numbers[][MAX_STRING], int* account_balances, int* bonus_points, int count);
void saveToFile(int* nos, char names[][MAX_STRING], int* ages, char phone_numbers[][MAX_STRING], int* account_balances, int* bonus_points, int count);
void removeCustomer(int* nos, char names[][MAX_STRING], int* ages, char phone_numbers[][MAX_STRING], int* account_balances, int* bonus_points, int* count);
void removeAllCustomers(int* pCount);

int isFull(int n);
int isEmpty(int n);
char* ltrim(char str[]);
char* rtrim(char str[]);
char* trim(char str[]);
char* nameStr(char str[]);

void lastWord(char str[MAX_STRING], char last[MAX_STRING]);
void swapNumber(int* a, int* b);
void swapString(char str1[MAX_STRING], char str2[MAX_STRING]);

int getUserChoice(void);
int getUserSearchChoice(void);
int getUserSortChoice(void);

int main(){
	int nos[MAX_ARRAY];
	char names[MAX_ARRAY][MAX_STRING];
	int  ages[MAX_ARRAY];			// By default, 0 is male, 1 is female
	char phone_numbers[MAX_ARRAY][MAX_STRING];
	int  account_balances[MAX_ARRAY];
    int  bonus_points[MAX_ARRAY];
	int count = 0;
	int choice = 0;
	
	do{
		choice = getUserChoice();
		switch (choice){
			case 1:                
                printAllCustomers(nos, names, ages, phone_numbers, account_balances, bonus_points, count);
                getchar();
                break;
            case 2:                
                addCustomer(nos, names, ages, phone_numbers, account_balances, bonus_points, &count);
                getchar();
                break;
            case 3:                
                addCustomersFromFile(nos, names, ages, phone_numbers, account_balances, bonus_points, &count);
                getchar();
                break;
            case 4:                
                sortAllCustomers(nos, names, ages, phone_numbers, account_balances, bonus_points, count);
                break;
            case 5:                
                searchCustomer(nos, names, ages, phone_numbers, account_balances, bonus_points, count);
                break;
            case 6:                
                saveToFile(nos, names, ages, phone_numbers, account_balances, bonus_points, count);
                getchar();
                break;
            case 7:                
                removeCustomer(nos, names, ages, phone_numbers, account_balances, bonus_points, &count);
                getchar();
                break;
            case 8:                
                removeAllCustomers(&count);
                getchar();
                break;
            default:                
                printf("Quitting the program...\n");
                exit(0);
                break;
			}
		}
	while (choice > 0 && choice < 8);
	return 0;
}

void printACustomer(int nos, char name[MAX_STRING], int age, char phone[MAX_STRING], int account_balance, int bonus_point) {
    printf("\t| %-4d | %-35s | %-6d | %-20d | %-19d | %-12d |\n", nos, name, age, phone, account_balance, bonus_point);
}

void printAllCustomers(int nos[], char names[][MAX_STRING], int ages[], char phone_numbers[][MAX_STRING], int account_balances[], int bonus_points[], int count) {
    if (isEmpty(count)) {
        printf("\n\n\t\t\t\t The list is empty!\n");
        return;
    }
    printf("\t\t\t\t  *** The list of all customers ***\n\n");
    printf("\t| %-4s | %-35s | %-6s | %-20s | %-19s | %-12s |\n", " No", "             Full name", " Age", "    Phone Number", " Account Balance", " Bonus Point");
    for (int i = 0; i < count; i++) {
        printACustomer(nos[i], names[i], ages[i], phone_numbers[i], account_balances[i], bonus_points[i]);
    }
    printf("\n\t\t\t\t\t  Enter to exit...");
}

void addCustomer(int nos[], char names[][MAX_STRING], int ages[], char phone_numbers[][MAX_STRING], int account_balances[], int bonus_points[], int* pCount){
    if (isFull(*pCount))
    {
        printf("\t\t\t\t      Sorry! The list is full!\n");
        return;
    }        
    int no = 0;
    char name[MAX_STRING];
    int age = 0;
    char phone[MAX_STRING];
    int account_balance = 0;
    int bonus_point = 0;    
    printf("\t\t\t\t*** Enter information of customer ***\n\n");    
    printf("\t\t\t - Customer No: ");
    scanf("%d", &no);
    fflush(stdin);    
    printf("\t\t\t - Full name: ");
    scanf("%[^\n]", name);
    fflush(stdin);    
    printf("\t\t\t - Age: ");
    scanf("%d", &age);
    fflush(stdin);    
    printf("\t\t\t - Phone number: ");
    scanf("%[^\n]", phone);
    fflush(stdin);    
    printf("\t\t\t - Account balance: ");
    scanf("%d", &account_balance);
    fflush(stdin);    
    printf("\t\t\t - Bonus point: ");
    scanf("%d", &bonus_point);
    fflush(stdin);
	    
    nameStr(name);
    trim(phone);    
    nos[*pCount] = no;
    strcpy(names[*pCount], name);
    ages[*pCount] = age;
    strcpy(phone_numbers[*pCount], phone);
    account_balances[*pCount] = account_balance;
    bonus_points[*pCount] = bonus_point;    
    (*pCount)++;    
    printf("\n\t\t\t\t\t       Added!");
}

void fileReader(FILE* file, int nos[], char names[][MAX_STRING], int ages[], char phone_numbers[][MAX_STRING], int account_balances[], int bonus_points[], int* pCount)
{
    if (isFull(*pCount))
    {
        printf("\t\t\t\t      Sorry! The list is full!\n");
        return;
    }
    int no = 0;
    char name[MAX_STRING];
    int age = 0;
    char phone[MAX_STRING];
    int account_balance = 0;
    int bonus_point = 0;

    fscanf(file, "%d", &no);
    fscanf(file, "%s", name);
    fscanf(file, "%d", &age);
    fscanf(file, "%s", phone);
    fscanf(file, "%d", &account_balance);
    fscanf(file, "%d", &bonus_point);
    nameStr(name);
    trim(phone);
    
    nos[*pCount] = no;
    strcpy(names[*pCount], name);
    ages[*pCount] = age;
    strcpy(phone_numbers[*pCount], phone);
    account_balances[*pCount] = account_balance;
    bonus_points[*pCount] = bonus_point;
    (*pCount)++;
}
void searchCustomer(int nos[], char names[][MAX_STRING], int ages[], char phone_numbers[][MAX_STRING], int account_balances[], int bonus_points[], int count){
    if (isEmpty(count)){
        printf("\n\n\t\t\t\t     Sorry! The list is empty!\n");
        getchar();
        return;
    }    
    int choice = 0;    
    do{
        choice = getUserSearchChoice();        
        switch (choice){
            case 1:{
                printf("\t\t\t\t\t*** Search by ID ***\n\n");                
                int no = 0;                
                printf("\t - Customer No: ");
                scanf("%d", &no);
                fflush(stdin);                
                printf("\n\t| %-4s | %-35s | %-8s | %-15s | %-19s | %-12s |\n", " No", " Name", " Age", " Phone", " Account Balance", " Bonus Points");                
                for (int i = 0; i < count; i++){
                    if (nos[i] == no){
                        printACustomer(nos[i], names[i], ages[i], phone_numbers[i], account_balances[i], bonus_points[i]);
                    }
                }                
                printf("\n\t\t\t\t\t  Enter to exit...");                
                getchar();
                break;
            }            
            case 2:{
                printf("\t\t\t\t       *** Search by name ***\n\n");                
                char name[MAX_STRING];                
                printf("\t - Name: ");
                scanf("%[^\n]", name);
                fflush(stdin);                
                printf("\n\t| %-4s | %-35s | %-8s | %-10s | %-19s | %-12s |\n", " No", " Name", " Age", " Phone", " Account Balance", " Bonus Points");                
                for (int i = 0; i < count; i++){
                    if (strstr(names[i], name) != NULL){
                        printACustomer(nos[i], names[i], ages[i], phone_numbers[i], account_balances[i], bonus_points[i]);
                    }
                }                
                printf("\n\t\t\t\t\t  Enter to exit...");                
                getchar();
                break;
            }
            
            case 3:{
                printf("\t\t\t\t    *** Search by phone ***\n\n");                
                char phone[MAX_STRING];                
                printf("\t - Phone: ");
                scanf("%[^\n]", phone);
                fflush(stdin);                
                printf("\n\t| %-4s | %-35s | %-8s | %-15s | %-19s | %-12s |\n", " No", " Name", " Age", " Phone", " Account Balance", " Bonus Points");                
                for (int i = 0; i < count; i++){
                    if (strstr(phone_numbers[i], phone) != NULL){
                        printACustomer(nos[i], names[i], ages[i], phone_numbers[i], account_balances[i], bonus_points[i]);
                    }
                }                
                printf("\n\t\t\t\t\t  Enter to exit...");                
                getchar();
                break;
            }
        }
    } while (choice > 0 && choice < 4);
}

void addCustomersFromFile(int nos[], char names[][MAX_STRING], int ages[], char phone_numbers[][MAX_STRING], int account_balances[], int bonus_points[], int* pCount){
	FILE* file = fopen("customers.txt", "r");
	if (file != NULL){
		while (!feof(file)){
			fileReader(file, nos, names, ages, phone_numbers, account_balances, bonus_points, pCount);
		}
		fclose(file);
	}
	else
    {
        printf("Failed to open file.\n");
    }
}

void saveToFile(int nos[], char names[][MAX_STRING], int ages[], char phone_numbers[][MAX_STRING], int account_balances[], int bonus_points[], int count){
    if (isEmpty(count)){
        printf("\n\n\t\t\t\t     Sorry! The list is empty!\n");
        return;
    }    
    
    printf("\t\t\t\t *** Save all customers to file ***\n\n");    
    printf("\t - Please enter the file name to save!\n");
    printf("\t - File name: ");    
    char path[MAX_STRING];
    scanf("%[^\n]", path);
    fflush(stdin);
	    
    FILE* file = fopen(path, "w");    
    for (int i = 0; i < count; i++){
        fprintf(file, "%d, %s, %d, %d, %d, %d\n", nos[i], names[i], ages[i], phone_numbers[i], account_balances[i], bonus_points[i]);
    }    
    fclose(file);    
    printf("\n\t\t\t\t\t       Saved!");
}

void sortAllCustomers(int nos[], char names[][MAX_STRING], int ages[], char phone_numbers[][MAX_STRING], int account_balances[], int bonus_points[], int count){    
    if (isEmpty(count)){
        printf("\n\n\t\t\t\t     Sorry! The list is empty!\n");
        getchar();        
        return;
    }  
    int choice = 0;
    do {
    	choice = getUserSortChoice();
    	switch (choice){
    			case 1: {
    				printf ("\t\t\t\t *** Sort by ID ***\n\n");
    				for ( int i = 0; i < count; i++){
    					for (int j = count - 1; j > i; j--){
    						if ( nos[j] < nos[j - 1]){
	    					swapNumber(&nos[j], &nos[j - 1]);
                            swapString(names[j], names[j - 1]);
                            swapNumber(&ages[j], &ages[j - 1]);
                            swapString(phone_numbers[j], phone_numbers[j - 1]);
                            swapNumber(&account_balances[j], &account_balances[j - 1]);
                            swapNumber(&bonus_points[j], &bonus_points[j - 1]); 
							}
						}
					}
					printf("\n\t\t\t   Sorted!\n");
	                printf("\n\t\t\t\t\t  Enter to exit...");                
	                getchar();
	                break;
				}
				
				case 2:{
	                printf("\t\t\t\t\t*** Sort by name ***\n\n");                
	                for (int i = 0; i < count; i++){
	                    for (int j = count - 1; j > i; j--){
	                    	char lastName1[MAX_STRING];
                        	char lastName2[MAX_STRING];
                        
                        	lastWord(names[j], lastName1);
                        	lastWord(names[j - 1], lastName2);
                        	
	                        if (strcmp(lastName1, lastName2) < 0){
	                        	
	                            swapNumber(&nos[j], &nos[j - 1]);
	                            swapString(names[j], names[j - 1]);
	                            swapNumber(&ages[j], &ages[j - 1]);
	                            swapString(phone_numbers[j], phone_numbers[j - 1]);
	                            swapNumber(&account_balances[j], &account_balances[j - 1]);
	                            swapNumber(&bonus_points[j], &bonus_points[j - 1]);
	                        }
	                    }
	                }
	                printf("\n\t\t\t   Sorted!\n");
	                printf("\n\t\t\t\t\t  Enter to exit...");                
	                getchar();
	                break;
           		}
		}
	}
	while (choice > 0 && choice < 3);
}

void removeCustomer(int nos[], char names[][MAX_STRING], int ages[], char phone_numbers[][MAX_STRING], int account_balances[], int bonus_points[], int* pCount){
    printf("\n\n\t\t\t\t     *** Remove a customer ***\n\n");    
    int no = 0;    
    printf("\t - Please enter the ID of customer that you want to remove: ");
    scanf("%d", &no);
    fflush(stdin);    
    int check = 0;
    int pos = 0;    
    for (int i = 0; i < *pCount; i++){
        if (nos[i] == no){
            pos = i;
            check = 1;
            break;
        }
    }    
    if (check == 0){
        printf("\n\t\t\t\t  Can not find the ID to remove...");
        return;
    }    
    if (*pCount == 1){
        *pCount = 0;
    }
    else{
        for (int i = pos; i < *pCount - 1; i++){
            nos[i] = nos[i + 1];
            strcpy(names[i], names[i + 1]);
            ages[i] = ages[i + 1];
            strcpy(phone_numbers[i], phone_numbers[i + 1]);
            account_balances[i] = account_balances[i + 1];
            bonus_points[i] = bonus_points[i + 1];
        }        
        (*pCount)--;
    }    
    printf("\n\t\t\t\t\t      Removed!");
}

void removeAllCustomers(int* pCount){
    printf("\n\n\t\t\t\t       *** Remove all customers ***\n\n");    
    if (*pCount == 0){
        printf("\n\n\t\t\t\t     Sorry! The list is empty!\n");
        return;
    }    
    *pCount = 0;    
    printf("\n\t\t\t\t       Removed all customers!");
}

int isFull(int n){
	return n >= MAX_ARRAY;
}

int isEmpty(int n){
	return n <= 0;
}

char* ltrim(char str[]){
	int i = 0;
	
	while (str[i] == ' '){
		i++;
	}
	
	if (i > 0){
		strcpy(&str[0], &str[i]);
	}
	
	return str;
} 

char* rtrim(char str[]){
	int i = strlen(str) - 1;
	
	while (str[i] == ' '){
		i--;
	}
	
	str[i + 1] = '\0';
	
	return str;
}

char* trim(char str[]){
	rtrim(ltrim(str));
	
	char* ptr = strstr(str, "  ");
	
	while (ptr != NULL){
		strcpy(ptr, ptr + 1);
		ptr = strstr(str, "  ");
	}
	
	return str;
}

char* nameStr(char str[]){
	trim(str);
	strlwr(str);
	
	int length = strlen(str);
	
	for (int i = 0; i < length; i++){
		if (i == 0 || (i > 0 && str[i - 1] == ' ')){
			str[i] = toupper(str[i]);
		}
	}
	
	return str;
}

void lastWord(char str[MAX_STRING], char last[MAX_STRING]){
	int length = strlen(str) - 1;
	
	for (; str[length] != ' '; length--);
	int i = 0;
	for (++length; str[length] != '\0'; length++){
		last[i] = str[length];
		i++;
	}
}

void swapNumber(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;	
}

void swapString(char str1[MAX_STRING], char str2[MAX_STRING]){
	char temp[MAX_STRING];
	
	strcpy(temp, str1);
	strcpy(str1, str2);
	strcpy(str2, temp);
}

char* strlwr(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
    return str;
}

int getUserChoice(){
	int choice = 0;	
		
	printf("\n\n\n");	
	printf("                          ----------------------MENU-------------------------\n");
	printf("\t\t       1. Display all customers               |  Press 1\n");
	printf("\t\t       2. Add new customer from console       |  Press 2\n");
    printf("\t\t       3. Import customer from file           |  Press 3\n");
	printf("\t\t       4. Sort all customers                  |  Press 4\n");
	printf("\t\t       5. Search a customers                  |  Press 5\n");
	printf("\t\t       6. Write data to file                  |  Press 6\n");
	printf("\t\t       7. Remove a customer                   |  Press 7\n");
	printf("\t\t       8. Remove all customers                |  Press 8\n");
	printf("\t\t       9. Quit!                               |  Press any\n\n\n");	
	printf("\t\t\t\t\t Your choice: ");	
	scanf("%d", &choice);
	fflush(stdin);
	return choice;
}

int getUserSearchChoice(){
	int choice = 0;	
    printf("\t\t\t  1. Search by ID                   |  Press 1\n");
	printf("\t\t\t  2. Search by name                 |  Press 2\n");
	printf("\t\t\t  3. Search by age                  |  Press 3\n");
	printf("\t\t\t  4. Search by phone                |  Press 4\n");
	printf("\t\t\t  5. Quit!                          |  Press any\n\n\n");	
	printf("\t\t\t\t\t Your choice: ");	
	scanf("%d", &choice);
	fflush(stdin);		
	return choice;
}

int getUserSortChoice()
{
	int choice = 0;	
	printf("\t\t\t  1. Sort by ID                   |  Press 1\n");
	printf("\t\t\t  2. Sort by name                 |  Press 2\n");
	printf("\t\t\t  3. Quit!                        |  Press any\n\n\n");	
	printf("\t\t\t\t\t Your choice: ");	
	scanf("%d", &choice);
	fflush(stdin);	
	return choice;
}