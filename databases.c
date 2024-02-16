#define MAXDB 50

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
    {"name", "stock", "price", "manufacturing date", "expiry date"},
    {"name", "age", "phone number","acconut balance","bonus point"},
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

// Default database illustration:

// product_database
//
//      Name, Stock, Price, Manufacturing Date, Expiry Date
//

// customer_database
//
//      Name, Age, Phone Number, Account Balance, Bonus Point
//