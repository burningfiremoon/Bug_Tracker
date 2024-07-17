/*
    Revision History:
    1.0 - 03-07-2024 [Date] - Modified by Skyler
    2.0 - 16-07-2024 [Date] - Modified by Anthony

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

//-------------------------------------
// List of #includes
#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>  
#include <fcntl.h>

using namespace std;

//-------------------------------------
// Class definitions

class ChangeRequest {
public:
    ChangeRequest();
    ChangeRequest(int id, const char* description);
    ~ChangeRequest();

    void setID(int id);
    int getID() const;
    void setDescription(const char* description);
    const char* getDescription() const;

    static void openFile();
    static void closeFile();
    static bool writeRecord(const ChangeRequest& changeRequest);
    static bool getNext(ChangeRequest& changeRequest);
    static bool findRecord(int id, ChangeRequest& changeRequest);
    static bool deleteRecord(int id);

private:
    int id;
    char description[30];

    static const int recordSize = sizeof(int) + 30 * sizeof(char);
    static fstream dbFile;

    static void seekToBeginning();
};

class User {
public:
    User();
    User(int id, const char* name);
    ~User();

    void setInfo(const char* name);
    const char* getInfo() const;
    void setID(int id);
    int getID() const;

    static void openFile();
    static void closeFile();
    static bool writeRecord(const User& user);
    static bool getNext(User& user);
    static bool findRecord(int id, User& user);
    static bool deleteRecord(int id);

private:
    int id;
    char name[30];

    static const int recordSize = sizeof(int) + 30 * sizeof(char);
    static fstream dbFile;

    static void seekToBeginning();
};

class ChangeItem {
public:
    ChangeItem();
    ChangeItem(int id, const char* productID, const char* description, int status, int priority, const char* requester);
    ~ChangeItem();

    void setID(int id);
    int getID() const;
    void setProductID(const char* productID);
    const char* getProductID() const;
    void setDescription(const char* description);
    const char* getDescription() const;
    void setStatus(int status);
    int getStatus() const;
    void setPriority(int priority);
    int getPriority() const;
    void setRequester(const char* requester);
    const char* getRequester() const;

    static void openFile();
    static void closeFile();
    static bool writeRecord(const ChangeItem& changeItem);
    static bool getNext(ChangeItem& changeItem);
    static bool findRecord(int id, ChangeItem& changeItem);
    static bool deleteRecord(int id);
    static bool updStatus(int id, int newStatus);
    static bool updRelease(int id, int newRelease);
    static bool updPriority(int id, int newPriority);
    static bool updDesc(int id, const char* newDescription);
    static bool showRequester(int id);

private:
    int id;
    char productID[30];
    char description[30];
    int status;
    int priority;
    char requester[30];

    static const int recordSize = sizeof(int) + 30 * sizeof(char) * 3 + sizeof(int) * 2;
    static fstream dbFile;

    static void seekToBeginning();
};

class ProductRelease {
public:
    ProductRelease();
    ProductRelease(int id, const char* name, const char* version);
    ~ProductRelease();

    void setID(int id);
    int getID() const;
    void setName(const char* name);
    const char* getName() const;
    void setVersion(const char* version);
    const char* getVersion() const;

    static void openFile();
    static void closeFile();
    static bool addRelease(const ProductRelease& release);
    static bool addProduct(int id, const char* name);
    static bool showProduct(int id);
    static bool showRelease(int id);

private:
    int id;
    char name[30];
    char version[30];

    static const int recordSize = sizeof(int) + 30 * sizeof(char) * 2;
    static fstream dbFile;

    static void seekToBeginning();
};

//-------------------------------------
// Function prototypes

void openDatabase();
void closeDatabase();
int truncateFile(const char* path, off_t length);

#endif // DATABASE_H
