//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 17-July-2024 - Created by Tanvir
Initial creation and setup of DatabaseRecord class
2.0 - 18-July-2024 - Modified by Anthony
3.0 - 26-July-2024 - Modified by Anthony
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    DatabaseRecord.h

    This header file contains the definition of the DatabaseRecord class, which serves as the base class 
    for managing database records. The purpose of this class is to provide basic file operations for reading 
    and writing records to a file. It includes methods for opening and closing the file, finding and deleting 
    records, and seeking to the beginning of the file. The attributes and methods are placed together to 
    provide high cohesion and facilitate easy management of database records.

    Includes:
    - DatabaseRecord constructor and destructor
    - File operations (open, close, find, delete)
    - Utility methods for seeking and managing the file pointer
*/

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
// Struct Definitions
//-------------------------------------
struct Date {
    int y;
    int m;
    int d;
};

struct ReleaseID {
    char id[9]; // 8 characters plus null terminator
};

//-------------------------------------
// Base Class Definition
//-------------------------------------

class DatabaseRecord {
public:
    //-------------------------------------
    // Constructor
    //-------------------------------------
    /*
        DatabaseRecord()
        - Purpose: Initialize a DatabaseRecord object and generate a random ID.
    */
    DatabaseRecord();

    //-------------------------------------
    // Destructor
    //-------------------------------------
    /*
        ~DatabaseRecord()
        - Purpose: Virtual destructor to clean up resources used by the DatabaseRecord object.
    */
    virtual ~DatabaseRecord() = default;

    //-------------------------------------
    // Setters and Getters
    //-------------------------------------
    /*
        int getID() const
        - Purpose: Get the integer representation of the record ID.
        - Returns: int (out): The integer representation of the record ID.
    */
    int getID() const;

    //-------------------------------------
    // Pure Virtual Methods
    //-------------------------------------
    /*
        virtual bool writeRecord(fstream &dbFile) const = 0
        - Purpose: Write the record to the given file stream.
        - Parameters:
            - fstream &dbFile (in/out): The file stream to write the record to.
        - Returns: bool (out): True if the record is written successfully, false otherwise.
    */
    virtual bool writeRecord(fstream &dbFile) const = 0;

    /*
        virtual bool readRecord(fstream &dbFile) = 0
        - Purpose: Read a record from the given file stream.
        - Parameters:
            - fstream &dbFile (in/out): The file stream to read the record from.
        - Returns: bool (out): True if the record is read successfully, false otherwise.
    */
    virtual bool readRecord(fstream &dbFile) = 0;

    /*
        virtual int getRecordSize() const = 0
        - Purpose: Get the size of the record.
        - Returns: int (out): The size of the record.
    */
    virtual int getRecordSize() const = 0;

    /*
        virtual void readFromBuffer(const char* buffer) = 0
        - Purpose: Read the record from a buffer.
        - Parameters:
            - const char* buffer (in): The buffer to read the record from.
    */
    virtual void readFromBuffer(const char* buffer) = 0;

    //-------------------------------------
    // Static Methods for File Operations
    //-------------------------------------
    /*
        static void openFile(const string& fileName)
        - Purpose: Open the database file with the given name.
        - Parameters:
            - const string& fileName (in): The name of the file to open.
    */
    static void openFile(const string& fileName);

    /*
        static void closeFile()
        - Purpose: Close the database file.
    */
    static void closeFile();

    /*
        static bool findRecord(const char* id, DatabaseRecord& record)
        - Purpose: Find a record with the given ID in the database file.
        - Parameters:
            - const char* id (in): The ID of the record to find.
            - DatabaseRecord& record (out): The record object to store the found record.
        - Returns: bool (out): True if the record is found, false otherwise.
    */
    static bool findRecord(const char* id, DatabaseRecord& record);

    /*
        static bool deleteRecord(const char* id)
        - Purpose: Delete a record with the given ID from the database file.
        - Parameters:
            - const char* id (in): The ID of the record to delete.
        - Returns: bool (out): True if the record is deleted successfully, false otherwise.
    */
    static bool deleteRecord(const char* id);

    /*
        static fstream& getFile()
        - Purpose: Get the file stream of the database file.
        - Returns: fstream& (out): The file stream of the database file.
    */
    static fstream& getFile();

    /*
        static void seekToBeginning()
        - Purpose: Seek to the beginning of the database file.
    */
    static void seekToBeginning();

    /*
        static bool backupDatabase(std::fstream& src, const std::string& outputFile)
        - Purpose: Seek to the beginning of the database file.
    */
    static bool backupDatabase(const std::string& outputFile);

protected:
    //-------------------------------------
    // Member Variables
    //-------------------------------------
    static fstream dbFile;
    char id[6];
};

//-------------------------------------
// Function Prototypes
//-------------------------------------
/*
    void openDatabase(const string& fileName)
    - Purpose: Open the database file with the given name.
    - Parameters:
        - const string& fileName (in): The name of the file to open.
*/
void openDatabase(const string& fileName);

/*
    void closeDatabase()
    - Purpose: Close the database file.
*/
void closeDatabase();

/*
    int truncateFile(const char* path, off_t length)
    - Purpose: Truncate the file to the given length.
    - Parameters:
        - const char* path (in): The path of the file to truncate.
        - off_t length (in): The length to truncate the file to.
    - Returns: int (out): 0 on success, -1 on failure.
*/
int truncateFile(const char* path, off_t length);


#endif // DATABASE_RECORD_H
