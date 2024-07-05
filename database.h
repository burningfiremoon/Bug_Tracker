/*
    database.h
    This header file contains class definitions and function declarations for database operations.
    It includes necessary headers and defines classes and functions to interact with the database.
*/
//-------------------------------------
#ifndef DATABASE_H
#define DATABASE_H

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
    ChangeRequest(int id, string description);

    // Destructor
    ~ChangeRequest();

    // ----- add
    // Adds ChangeRequest to the database
    void add();

    // ----- setAttribute1
    // Sets the ID of the change request
    void setID(int id);

    // ----- getAttribute1
    // Gets the ID of the change request
    int getID();

    // ----- setAttribute2
    // Sets the description of the change request
    void setDescription(string description);

    // ----- getAttribute2
    // Gets the description of the change request
    string getDescription();

private:
    int id; // ID of the change request
    string description; // Description of the change request
};

class User {
public:
    // Add user-related methods and attributes
};

class ChangeItem {
public:
    // Add change item-related methods and attributes
};

class ProductRelease {
public:
    // Add product release-related methods and attributes
};

class Product {
public:
    // Add product-related methods and attributes
};

#endif // DATABASE_H
