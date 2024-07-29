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
    DatabaseRecord.cpp

    This module contains the implementation of the DatabaseRecord class, which serves as the base class 
    for managing database records. The purpose of this class is to provide basic file operations for reading 
    and writing records to a file. It includes methods for opening and closing the file, finding and deleting 
    records, and seeking to the beginning of the file.

    Includes:
    - DatabaseRecord constructor and destructor
    - File operations (open, close, find, delete)
    - Utility methods for seeking and managing the file pointer
*/

#include "DatabaseRecord.h"
#include <iostream>
#include <ctime>
#include <cstring>
#include <sstream>

using namespace std;

//-------------------------------------
// Static Member Initialization
//-------------------------------------

fstream DatabaseRecord::dbFile;

//-------------------------------------
// Constructor
//-------------------------------------
/*
    DatabaseRecord::DatabaseRecord()
    - Purpose: Initialize a DatabaseRecord object and generate a random ID.
*/
DatabaseRecord::DatabaseRecord() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < 6; i++) {
        this->id[i] = 'A' + std::rand() % 26;
    }
}

//-------------------------------------
// Getter for ID
//-------------------------------------
/*
    int DatabaseRecord::getID() const
    - Purpose: Get the integer representation of the record ID.
    - Returns: int (out): The integer representation of the record ID.
*/
int DatabaseRecord::getID() const {
    int intID = 0;
    for (int i = 0; i < 6; i++) {
        intID = intID * 10 + (id[i] - 'A');
    }
    cout << "Converted ID " << string(id) << " to integer " << intID << endl; // Debug output
    return intID;
}

//-------------------------------------
// File Operations
//-------------------------------------
/*
    void DatabaseRecord::openFile(const string& fileName)
    - Purpose: Open the database file with the given file name.
    - Parameters:
        - const string& fileName (in): The name of the file to open.
*/
void DatabaseRecord::openFile(const string& fileName) {
    dbFile.open(fileName, ios::in | ios::out | ios::binary | ios::app);
    if (!dbFile) {
        dbFile.open(fileName, ios::out | ios::binary | ios::app);
        dbFile.close();
        dbFile.open(fileName, ios::in | ios::out | ios::binary | ios::app);
    }
    if (!dbFile.is_open()) {
        throw runtime_error("Error opening database file: " + fileName);
    }
    cout << "Database file " << fileName << " opened successfully." << endl; // Debug output
}


/*
    void DatabaseRecord::closeFile()
    - Purpose: Close the database file.
*/
void DatabaseRecord::closeFile() {
    if (dbFile.is_open()) {
        dbFile.close();
    }
}

//-------------------------------------
// Utility Methods
//-------------------------------------
/*
    void DatabaseRecord::seekToBeginning()
    - Purpose: Seek to the beginning of the database file.
*/
void DatabaseRecord::seekToBeginning() {
    dbFile.clear();
    dbFile.seekg(0, ios::beg);
}

/*
    fstream& DatabaseRecord::getFile()
    - Purpose: Get the file stream for the database file.
    - Returns: fstream& (out): The file stream for the database file.
*/
fstream& DatabaseRecord::getFile() {
    cout << "Returning database file stream." << endl; // Debug output
    return dbFile;
}


//-------------------------------------
// Record Operations
//-------------------------------------
/*
    bool DatabaseRecord::findRecord(const char* id, DatabaseRecord& record)
    - Purpose: Find a record with the given ID in the database file.
    - Parameters:
        - const char* id (in): The ID of the record to find.
        - DatabaseRecord& record (out): The record object to store the found record.
    - Returns: bool (out): True if the record is found, false otherwise.
*/
bool DatabaseRecord::findRecord(const char* id, DatabaseRecord& record) {
    seekToBeginning();
    string line;
    while (getline(dbFile, line)) {
        istringstream iss(line);
        string tempID;
        iss >> tempID;
        if (tempID == id) {
            record.readFromBuffer(line.c_str());
            return true;
        }
    }
    return false;
}

/*
    bool DatabaseRecord::deleteRecord(const char* id)
    - Purpose: Delete a record with the given ID from the database file.
    - Parameters:
        - const char* id (in): The ID of the record to delete.
    - Returns: bool (out): True if the record is deleted successfully, false otherwise.
*/
bool DatabaseRecord::deleteRecord(const char* id) {
    seekToBeginning();
    string line;
    bool found = false;

    ofstream tempFile("temp.txt");
    while (getline(dbFile, line)) {
        istringstream iss(line);
        string tempID;
        iss >> tempID;
        if (tempID == id) {
            found = true;
            continue;
        }
        tempFile << line << endl;
    }
    tempFile.close();
    if (found) {
        remove("Database.txt");
        rename("temp.txt", "Database.txt");
    }
    return found;
}
