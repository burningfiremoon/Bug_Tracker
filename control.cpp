/*
    control.cpp:
    This source file contains function definitions for handling different scenarios.
    It includes necessary headers and defines functions to manage database operations and user management.
*/

#include "control.h"
#include "DatabaseRecord.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void StopAccepting() {
    cout << "StopAccepting called." << endl;
}

void StartAccepting() {
    cout << "StartAccepting called." << endl;
}

bool Init_User(const char* name, const char* phone, const char* email) {
    // Open the database file for writing
    DatabaseRecord::openFile("testDB.txt");

    fstream &dbFile = DatabaseRecord::getFile();
    if (!dbFile.is_open()) {
        std::cerr << "Database file is not open for writing." << std::endl;
        return false;
    }

    User newUser(name);
    newUser.setPhone(phone);
    newUser.setEmail(email);

    // Move to the end of the file for appending the new record
    dbFile.seekp(0, std::ios::end);
    if (!newUser.writeRecord(dbFile)) {
        std::cerr << "Error: Failed to write user record to database." << std::endl;
        DatabaseRecord::closeFile();
        return false;
    }

    DatabaseRecord::closeFile();
    return true;
}

void UpdateUserName(const char* oldName, const char* newName) {
    // Open the database file
    DatabaseRecord::openFile("testDB.txt");

    fstream &dbFile = DatabaseRecord::getFile();
    if (!dbFile.is_open()) {
        std::cerr << "Error: Could not open database file." << std::endl;
        return;
    }

    User user(oldName);
    if (!user.readRecord(dbFile)) {
        std::cerr << "Error: User not found in the database." << std::endl;
        DatabaseRecord::closeFile();
        return;
    }

    // Update the user's name
    user.setRequesterName(newName);

    // Write the updated user record back to the database
    dbFile.seekp(0, std::ios::beg); // Reset file pointer to the beginning
    if (!user.writeRecord(dbFile)) {
        std::cerr << "Error: Failed to update user record in the database." << std::endl;
    } else {
        std::cout << "User name updated successfully." << std::endl;
    }

    // Close the database file
    DatabaseRecord::closeFile();
}

bool CheckUserExists(const char* name) {
    std::cout << "Checking if user exists: " << name << std::endl;

    // Open the database file
    DatabaseRecord::openFile("testDB.txt");
    std::cout << "Database file opened successfully for checking user." << std::endl;

    // Seek to the beginning of the file
    DatabaseRecord::seekToBeginning();

    // Use a User object to determine the buffer size for reading records
    User tempUser(name);
    int recordSize = tempUser.getRecordSize();
    char* buffer = new char[recordSize];

    fstream &dbFile = DatabaseRecord::getFile();

    // Read through the file to find the user
    while (dbFile.read(buffer, recordSize)) {
        User user(name);  // You can use name or an empty string if it requires a non-empty initializer
        user.readFromBuffer(buffer);
        std::cout << "Checking user: " << user.getRequesterName() << std::endl;
        if (strcmp(user.getRequesterName(), name) == 0) {
            std::cout << "User found: " << name << std::endl;
            delete[] buffer;
            DatabaseRecord::closeFile();
            return true;
        }
    }

    // User not found
    std::cout << "User not found: " << name << std::endl;
    delete[] buffer;
    DatabaseRecord::closeFile();
    return false;
}



void showUserInfo(const char* Name) {
    if (CheckUserExists(Name)) {
        DatabaseRecord::openFile("testDB.txt");
        fstream &dbFile = DatabaseRecord::getFile();
        User user(Name);
        if (user.readRecord(dbFile)) {
            cout << "Requester Name: " << user.getRequesterName() << endl;
            cout << "Phone: " << user.getPhone() << endl;
            cout << "Email: " << user.getEmail() << endl;
            cout << "Address: " << user.getAddress() << endl;
        } else {
            std::cerr << "Error: Failed to read user record from database." << std::endl;
        }
        DatabaseRecord::closeFile();
    } else {
        std::cout << "User not found." << std::endl;
    }
}
