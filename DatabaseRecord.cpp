/*
    Revision History:
    1.0 - 03-07-2024 [Date] - Created by Skyler
    2.0 - 16-07-2024 [Date] - Modified by Anthony

    database.cpp:
    This file contains the implementations of the database operations.
    It includes necessary headers and implements classes and functions to interact with the database.
    The purpose of this file is to provide a concrete implementation of the database operations, ensuring that
    the main logic of the application remains separate from the database-specific code. This design promotes 
    cohesion by grouping all database-related functionality together.
*/
//-------------------------------------
// List of #includes
#include "DatabaseRecord.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <ctime>
#include <cstring>
using namespace std;

// Static member initialization
fstream DatabaseRecord::dbFile;

//-------------------------------------
// Function definitions

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

void DatabaseRecord::openFile() {
    dbFile.open("Database.dat", ios::in | ios::out | ios::binary);
    if (!dbFile) {
        dbFile.open("Database.dat", ios::out | ios::binary);
        dbFile.close();
        dbFile.open("Database.dat", ios::in | ios::out | ios::binary);
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

bool DatabaseRecord::findRecord(const char* id, DatabaseRecord& record) {
    seekToBeginning();
    char tempID[6];
    char buffer[record.getRecordSize() - sizeof(tempID)];
    while (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(buffer, record.getRecordSize() - sizeof(tempID));
        if (strncmp(tempID, id, sizeof(tempID)) == 0) {
            record.readFromBuffer(buffer);
            return true;
        }
    }
    return false;
}

bool DatabaseRecord::deleteRecord(const char* id) {
    seekToBeginning();
    char tempID[6];
    streampos posToDelete;
    bool found = false;
    char buffer[1024];

    while (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        posToDelete = dbFile.tellg();
        dbFile.read(buffer, 1024 - sizeof(tempID));
        if (strncmp(tempID, id, sizeof(tempID)) == 0) {
            found = true;
            break;
        }
    }

    if (!found) return false;

    dbFile.seekg(-static_cast<streamoff>(sizeof(buffer)), ios::end);
    streampos lastPos = dbFile.tellg();
    dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID));
    dbFile.read(buffer, 1024 - sizeof(tempID));

    dbFile.seekp(posToDelete - static_cast<streamoff>(sizeof(tempID)) - static_cast<streamoff>(1024 - sizeof(tempID)), ios::beg);
    dbFile.write(reinterpret_cast<const char*>(&tempID), sizeof(tempID));
    dbFile.write(buffer, 1024 - sizeof(tempID));
    dbFile.flush();

    dbFile.close();
    if (truncate("Database.dat", static_cast<off_t>(lastPos)) != 0) {
        cerr << "Error truncating database file." << endl;
        return false;
    }
    openFile();

    return true;
}

void DatabaseRecord::seekToBeginning() {
    dbFile.clear();
    dbFile.seekg(0, ios::beg);
}

void openDatabase() {
    DatabaseRecord::openFile();
}

void closeDatabase() {
    DatabaseRecord::closeFile();
}

int truncateFile(const char* path, off_t length) {
    int fd = open(path, O_WRONLY);
    if (fd == -1) {
        return -1;
    }
    int result = ftruncate(fd, length);
    close(fd);
    return result;
}
