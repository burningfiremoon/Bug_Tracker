/*
    Revision History:
    1.0 - 03-07-2024 [Date] - Modified by Skyler

    database.h:
    This header file contains class definitions and function declarations for database operations.
    It includes necessary headers and defines classes and functions to interact with the database.
    The purpose of this header file is to abstract the database interaction, ensuring that the main logic
    of the application remains separate from the database-specific code. This design promotes cohesion by 
    grouping all database-related functionality together.
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
};

class ChangeItem {
public:
};

class ProductRelease {
public:
};

class Product {
public:
};

#endif // DATABASE_H
