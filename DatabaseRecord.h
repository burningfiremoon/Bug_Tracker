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
#ifndef DATABASE_RECORD_H
#define DATABASE_RECORD_H

//-------------------------------------
// List of #includes
#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>  
#include <fcntl.h>

using namespace std;

//-------------------------------------
// Base class definition

class DatabaseRecord {
public:
    DatabaseRecord();
    int getID() const;

    virtual ~DatabaseRecord() = default;
    virtual bool writeRecord(fstream &dbFile) const = 0;
    virtual bool readRecord(fstream &dbFile) = 0;
    virtual int getRecordSize() const = 0;
    virtual void readFromBuffer(const char* buffer) = 0;

    static void openFile();
    static void closeFile();
    static bool findRecord(const char* id, DatabaseRecord& record);
    static bool deleteRecord(const char* id);
   
protected:
    static fstream dbFile;
    char id[6];

    static void seekToBeginning();
};

//-------------------------------------
// Function prototypes

void openDatabase();
void closeDatabase();
int truncateFile(const char* path, off_t length);

#endif // DATABASE_RECORD_H
