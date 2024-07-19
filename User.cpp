//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 15-July-2024 - Created by Skyler
Initial creation and setup of User class
2.0 - 17-July-2024 - Modified by Skyler
Added detailed comments and explanations
2.1 - 18-July-2024 - Modified by Skyler
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    User.cpp

    This module contains the implementation of the User class, which represents a user record.
    The User class encapsulates details such as requester name, phone number, email, and address.
    The purpose of this class is to provide a cohesive representation of a user and manage its read 
    and write operations to a file. The attributes and methods are placed together to provide high 
    cohesion and facilitate easy management of user records.

    Includes:
    - User constructors and destructor
    - Getter and setter methods for various attributes
    - Methods to read and write records from/to a file
*/

#include "User.h"
#include <iostream>
#include <cstring>

using namespace std;

const int User::recordSize = sizeof(requesterName) + sizeof(phone) + sizeof(email) + sizeof(address);

User::User(const char* requesterName) : DatabaseRecord() {
    strncpy(this->requesterName, requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
    memset(phone, 0, sizeof(phone));
    memset(email, 0, sizeof(email));
    memset(address, 0, sizeof(address));
}

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

bool User::writeRecord(fstream &dbFile) const {
    dbFile.seekp(0, ios::end);
    dbFile.write(requesterName, sizeof(requesterName));
    dbFile.write(phone, sizeof(phone));
    dbFile.write(email, sizeof(email));
    dbFile.write(address, sizeof(address));
    dbFile.flush();
    return true;
}

bool User::readRecord(fstream &dbFile) {
    char tempRequesterName[31];
    char tempPhone[12];
    char tempEmail[25];
    char tempAddress[31];

    if (dbFile.read(tempRequesterName, sizeof(tempRequesterName))) {
        dbFile.read(tempPhone, sizeof(tempPhone));
        dbFile.read(tempEmail, sizeof(tempEmail));
        dbFile.read(tempAddress, sizeof(tempAddress));

        setRequesterName(tempRequesterName);
        setPhone(tempPhone);
        setEmail(tempEmail);
        setAddress(tempAddress);
        return true;
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
