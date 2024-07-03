/*
    Revision History:
    1.0 - 03-07-2024 [Date] - Modified by Skyler

    database.h:
    This header file contains class definitions and function declarations for database operations.
    It includes necessary headers and defines classes and functions to interact with the database.
*/
//-------------------------------------
#ifndef DATABASE_H
#define DATABASE_H

//-------------------------------------
// List of #includes
#include <string>
using namespace std;

//-------------------------------------
// Function prototypes

// -----
// openDatabase
// Opens the database connection
void openDatabase();

// -----
// closeDatabase
// Closes the database connection
void closeDatabase();

//-------------------------------------
// Class definitions

class ChangeRequest {
public:
    // Constructor
    ChangeRequest(int x, string y);

    // Destructor
    ~ChangeRequest();

    // ----- add
    // Adds ChangeRequest to the database
    void add();

    // set attribute1 ***need to change attribute 1 to real attribute
    void setAttribute1(int x);
    // get attribute1 ***need to change attribute 1 to real attribute
    int getAttribute1();
    // set attribute2 ***need to change attribute 2 to real attribute
    void setAttribute2(string y);
    // get attribute2 ***need to change attribute 2 to real attribute
    string getAttribute2();

private:
    // ***need to add attributes
};

class User
{
};

class ChangeItem
{
};

class ProductRelease
{
};

class Product
{
};

#endif // DATABASE_H
