#include "User.h"
#include <iostream>
#include <cstring>

using namespace std;

// Static Member Initialization
const int User::recordSize = sizeof(requesterName) + sizeof(phone) + sizeof(email) + sizeof(address);

// Constructor
User::User(const char* requesterName) : DatabaseRecord() {
    strncpy(this->requesterName, requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
    memset(phone, 0, sizeof(phone));
    memset(email, 0, sizeof(email));
    memset(address, 0, sizeof(address));
}

// Copy Constructor
User::User(const User& data) : DatabaseRecord() {
    strncpy(this->requesterName, data.requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
    strncpy(this->phone, data.phone, sizeof(this->phone) - 1);
    this->phone[11] = '\0'; // Ensure null termination
    strncpy(this->email, data.email, sizeof(this->email) - 1);
    this->email[24] = '\0'; // Ensure null termination
    strncpy(this->address, data.address, sizeof(this->address) - 1);
    this->address[30] = '\0'; // Ensure null termination
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

void User::setAddress(const char* address) {
    strncpy(this->address, address, sizeof(this->address) - 1);
    this->address[30] = '\0'; // Ensure null termination
}

const char* User::getAddress() const {
    return address;
}

// File Operations
bool User::writeRecord(fstream &dbFile) const {
    if (!dbFile.is_open()) {
        std::cerr << "Database file is not open for writing." << std::endl;
        return false;
    }
    dbFile.write(requesterName, sizeof(requesterName));
    dbFile.write(phone, sizeof(phone));
    dbFile.write(email, sizeof(email));
    dbFile.write(address, sizeof(address));
    dbFile.flush();
    return true;
}

bool User::readRecord(fstream &dbFile) {
    if (!dbFile.is_open()) {
        std::cerr << "Database file is not open for reading." << std::endl;
        return false;
    }

    std::cout << "Attempting to read record..." << std::endl;
    dbFile.clear(); // Clear any potential error flags
    dbFile.seekg(0, ios::beg); // Ensure we start reading from the beginning of the file

    char tempRequesterName[31] = {0};
    char tempPhone[12] = {0};
    char tempEmail[25] = {0};
    char tempAddress[31] = {0};

    if (dbFile.read(tempRequesterName, sizeof(tempRequesterName))) {
        dbFile.read(tempPhone, sizeof(tempPhone));
        dbFile.read(tempEmail, sizeof(tempEmail));
        dbFile.read(tempAddress, sizeof(tempAddress));

        setRequesterName(tempRequesterName);
        setPhone(tempPhone);
        setEmail(tempEmail);
        setAddress(tempAddress);

        // Debugging output to verify the read data
        std::cout << "Read User Record:" << std::endl;
        std::cout << "Name: " << tempRequesterName << std::endl;
        std::cout << "Phone: " << tempPhone << std::endl;
        std::cout << "Email: " << tempEmail << std::endl;
        std::cout << "Address: " << tempAddress << std::endl;

        return true;
    } else {
        std::cerr << "Failed to read record. Current file position: " << dbFile.tellg() << std::endl;
    }
    return false;
}


int User::getRecordSize() const {
    return sizeof(requesterName) + sizeof(phone) + sizeof(email) + sizeof(address);
}

void User::readFromBuffer(const char* buffer) {
    memcpy(requesterName, buffer, sizeof(requesterName));
    memcpy(phone, buffer + sizeof(requesterName), sizeof(phone));
    memcpy(email, buffer + sizeof(requesterName) + sizeof(phone), sizeof(email));
    memcpy(address, buffer + sizeof(requesterName) + sizeof(phone) + sizeof(email), sizeof(address));
}

ostream& operator<<(ostream& os, const User& user) {
    os << "Requester Name: " << user.requesterName << endl;
    os << "Phone: " << user.phone << endl;
    os << "Email: " << user.email << endl;
    os << "Address: " << user.address << endl;
    return os;
}
