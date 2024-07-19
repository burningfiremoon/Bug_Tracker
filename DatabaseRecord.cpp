//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 17-July-2024 - Created by Tanvir
Initial creation and setup of DatabaseRecord class
2.0 - 18-July-2024 - Modified by Anthony
2.1 - 18-July-2024 - Modified by Skyler
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

fstream DatabaseRecord::dbFile;

DatabaseRecord::DatabaseRecord() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < 6; i++) {
        this->id[i] = 'A' + std::rand() % 26;
    }
}

int DatabaseRecord::getID() const {
    int intID = 0;
    for (int i = 0; i < 6; i++) {
        intID = intID * 10 + (id[i] - 'A');
    }
    return intID;
}

void DatabaseRecord::openFile(const string& fileName) {
    dbFile.open(fileName, ios::in | ios::out | ios::binary);
    if (!dbFile) {
        dbFile.open(fileName, ios::out | ios::binary);
        dbFile.close();
        dbFile.open(fileName, ios::in | ios::out | ios::binary);
    }
    if (!dbFile.is_open()) {
        cerr << "Error opening database file." << endl;
        exit(1);
    }
}

void DatabaseRecord::closeFile() {
    if (dbFile.is_open()) {
        dbFile.close();
    }
}

void DatabaseRecord::seekToBeginning() {
    dbFile.clear();
    dbFile.seekg(0, ios::beg);
}

fstream& DatabaseRecord::getFile() {
    return dbFile;
}

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
