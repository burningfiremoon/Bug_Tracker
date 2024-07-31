//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 15-July-2024 - Created by Tanvir
Initial creation and setup of User class
2.0 - 17-July-2024 - Modified by Skyler
Added detailed comments and explanations
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    User.cpp

    This module contains the implementation of the User class, which represents a user record.
    The User class encapsulates details such as requester name, phone number, email, and address. 
    The purpose of this class is to provide a cohesive representation of a user and manage its read 
    and write operations to a file. The attributes and methods are placed together to provide high cohesion 
    and facilitate easy management of user records.

    Includes:
    - User constructors and destructor
    - Getter and setter methods for various attributes
    - Methods to read and write records from/to a file
    - Operator overload for output stream
*/

#include "User.h"
#include <iostream>
#include <cstring>

using namespace std;

//-------------------------------------
// Static Member Initialization
//-------------------------------------
/*
    const int User::recordSize
    - Purpose: Initialize the record size for the User class.
*/
const int User::recordSize = sizeof(requesterName) + sizeof(phone) + sizeof(email) + sizeof(address);

//-------------------------------------
// Constructor
//-------------------------------------
/*
    User::User(const char* requesterName)
    - Purpose: Constructor to initialize a User object with a given requester name.
    - Parameters:
        - const char* requesterName (in): The requester name to initialize the User with.
*/
User::User(const char* requesterName) : DatabaseRecord() {
    strncpy(this->requesterName, requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
    memset(phone, 0, sizeof(phone));
    memset(email, 0, sizeof(email));
    memset(address, 0, sizeof(address));
}

//-------------------------------------
// Copy Constructor
//-------------------------------------
/*
    User::User(const User& data)
    - Purpose: Copy constructor to create a copy of an existing User object.
    - Parameters:
        - const User& data (in): The User object to copy.
*/
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

//-------------------------------------
// Destructor
//-------------------------------------
/*
    User::~User()
    - Purpose: Destructor to clean up resources used by the User object.
*/
User::~User() {}

//-------------------------------------
// Setters and Getters
//-------------------------------------
/*
    void User::setRequesterName(const char* requesterName)
    - Purpose: Set the requester name for the User.
    - Parameters:
        - const char* requesterName (in): The requester name to set.
*/
void User::setRequesterName(const char* requesterName) {
    strncpy(this->requesterName, requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
}

/*
    const char* User::getRequesterName() const
    - Purpose: Get the requester name of the User.
    - Returns: const char* (out): The requester name of the User.
*/
const char* User::getRequesterName() const {
    return requesterName;
}

/*
    void User::setPhone(const char* phone)
    - Purpose: Set the phone number for the User.
    - Parameters:
        - const char* phone (in): The phone number to set.
*/
void User::setPhone(const char* phone) {
    strncpy(this->phone, phone, sizeof(this->phone) - 1);
    this->phone[11] = '\0'; // Ensure null termination
}

/*
    const char* User::getPhone() const
    - Purpose: Get the phone number of the User.
    - Returns: const char* (out): The phone number of the User.
*/
const char* User::getPhone() const {
    return phone;
}

/*
    void User::setEmail(const char* email)
    - Purpose: Set the email address for the User.
    - Parameters:
        - const char* email (in): The email address to set.
*/
void User::setEmail(const char* email) {
    strncpy(this->email, email, sizeof(this->email) - 1);
    this->email[24] = '\0'; // Ensure null termination
}

/*
    const char* User::getEmail() const
    - Purpose: Get the email address of the User.
    - Returns: const char* (out): The email address of the User.
*/
const char* User::getEmail() const {
    return email;
}

/*
    void User::setAddress(const char* address)
    - Purpose: Set the address for the User.
    - Parameters:
        - const char* address (in): The address to set.
*/
void User::setAddress(const char* address) {
    strncpy(this->address, address, sizeof(this->address) - 1);
    this->address[30] = '\0'; // Ensure null termination
}

/*
    const char* User::getAddress() const
    - Purpose: Get the address of the User.
    - Returns: const char* (out): The address of the User.
*/
const char* User::getAddress() const {
    return address;
}

//-------------------------------------
// File Operations
//-------------------------------------
/*
    bool User::writeRecord(fstream &dbFile) const
    - Purpose: Write the User record to the given file stream.
    - Parameters:
        - fstream &dbFile (in/out): The file stream to write the record to.
    - Returns: bool (out): True if the record is written successfully, false otherwise.
*/
bool User::writeRecord(fstream &dbFile) const {
    dbFile.seekp(0, ios::end);
    dbFile.write(requesterName, sizeof(requesterName));
    dbFile.write(phone, sizeof(phone));
    dbFile.write(email, sizeof(email));
    dbFile.write(address, sizeof(address));
    dbFile.flush();
    return true;
}

/*
    bool User::readRecord(fstream &dbFile)
    - Purpose: Read a User record from the given file stream.
    - Parameters:
        - fstream &dbFile (in/out): The file stream to read the record from.
    - Returns: bool (out): True if the record is read successfully, false otherwise.
*/
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

/*
    int User::getRecordSize() const
    - Purpose: Get the size of the User record.
    - Returns: int (out): The size of the User record.
*/
int User::getRecordSize() const {
    return sizeof(requesterName) + sizeof(phone) + sizeof(email) + sizeof(address);
}

/*
    void User::readFromBuffer(const char* buffer)
    - Purpose: Read the User record from a buffer.
    - Parameters:
        - const char* buffer (in): The buffer to read the record from.
*/
void User::readFromBuffer(const char* buffer) {
    memcpy(requesterName, buffer, sizeof(requesterName));
    memcpy(phone, buffer + sizeof(requesterName), sizeof(phone));
    memcpy(email, buffer + sizeof(requesterName) + sizeof(phone), sizeof(email));
    memcpy(address, buffer + sizeof(requesterName) + sizeof(phone) + sizeof(email), sizeof(address));
}

//-------------------------------------
// Friend Functions
//-------------------------------------
/*
    ostream& operator<<(ostream& os, const User& user)
    - Purpose: Output stream operator to print the User details.
    - Parameters:
        - ostream& os (out): The output stream.
        - const User& user (in): The User object to print.
    - Returns: ostream& (out): The output stream with the User details.
*/
ostream& operator<<(ostream& os, const User& user) {
    os << "Requester Name: " << user.requesterName << endl;
    os << "Phone: " << user.phone << endl;
    os << "Email: " << user.email << endl;
    os << "Address: " << user.address << endl;
    return os;
}
