#include "User.h"
#include <iostream>
#include <cstring>

using namespace std;

// Static Member Initialization
const int User::recordSize = sizeof(requesterName) + sizeof(phone) + sizeof(email);

// Constructor
User::User(const char* requesterName) : DatabaseRecord() {
    strncpy(this->requesterName, requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
    memset(phone, 0, sizeof(phone));
    memset(email, 0, sizeof(email));
}

// Copy Constructor
User::User(const User& data) : DatabaseRecord() {
    strncpy(this->requesterName, data.requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
    strncpy(this->phone, data.phone, sizeof(this->phone) - 1);
    this->phone[11] = '\0'; // Ensure null termination
    strncpy(this->email, data.email, sizeof(this->email) - 1);
    this->email[24] = '\0'; // Ensure null termination
}

// Destructor
User::~User() {}

// Setters and Getters
void User::setRequesterName(const char* requesterName) {
    strncpy(this->requesterName, requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
}

const char* User::getRequesterName() const {
    return requesterName;
}

void User::setPhone(const char* phone) {
    strncpy(this->phone, phone, sizeof(this->phone) - 1);
    this->phone[11] = '\0'; // Ensure null termination
}

const char* User::getPhone() const {
    return phone;
}

void User::setEmail(const char* email) {
    strncpy(this->email, email, sizeof(this->email) - 1);
    this->email[24] = '\0'; // Ensure null termination
}

const char* User::getEmail() const {
    return email;
}

// File Operations
bool User::writeRecord(fstream &dbFile) const {
    // Get current position of file pointer
    streampos currentPos = dbFile.tellg();

    // look for new line character to determine start of a line
    while (currentPos > 0) {
        dbFile.seekg(currentPos);
        currentPos -= 1;
        char ch;
        dbFile.get(ch);

        if (ch == '\n'){
            dbFile.seekg(currentPos+1);
            break;
        }
        dbFile.clear();
        dbFile.seekg(currentPos);
    }

    if (currentPos == 0){
        dbFile.seekg(0, ios::beg);
    }


    dbFile.seekp((long)dbFile.tellg(), ios::beg);
    dbFile.write(requesterName, sizeof(requesterName));
    dbFile.write(phone, sizeof(phone));
    dbFile.write(email, sizeof(email));
    dbFile.put('\n');
    dbFile.flush();
    // Reseting pointer back to start because errors go brrr
    dbFile.seekg(0, ios::beg);
    return true;
}

bool User::readRecord(fstream &dbFile) {
    if (!dbFile.is_open()) {
        std::cerr << "Database file is not open for reading." << std::endl;
        return false;
    }

    dbFile.clear(); // Clear any potential error flags

    char tempRequesterName[31];
    char tempPhone[12];
    char tempEmail[25];
    string temp;

    if (dbFile.read(tempRequesterName, sizeof(tempRequesterName))) {
        dbFile.read(tempPhone, sizeof(tempPhone));
        dbFile.read(tempEmail, sizeof(tempEmail));
        getline(dbFile, temp);

        setRequesterName(tempRequesterName);
        setPhone(tempPhone);
        setEmail(tempEmail);
        return true;
    } else {
        std::cerr << "Failed to read record. Current file position: " << dbFile.tellg() << std::endl;
    }
    return false;
}


int User::getRecordSize() const {
    return sizeof(requesterName) + sizeof(phone) + sizeof(email);
}

void User::readFromBuffer(const char* buffer) {
    memcpy(requesterName, buffer, sizeof(requesterName));
    memcpy(phone, buffer + sizeof(requesterName), sizeof(phone));
    memcpy(email, buffer + sizeof(requesterName) + sizeof(phone), sizeof(email));
}

ostream& operator<<(ostream& os, const User& user) {
    os << "Requester Name: " << user.requesterName << endl;
    os << "Phone: " << user.phone << endl;
    os << "Email: " << user.email << endl;
    return os;
}
