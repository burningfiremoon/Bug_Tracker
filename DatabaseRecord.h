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
