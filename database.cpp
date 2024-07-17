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
#include "database.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
using namespace std;

// Static member initialization
fstream DatabaseRecord::dbFile;

//-------------------------------------
// Function definitions

// ----- DatabaseRecord methods -----
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

bool DatabaseRecord::findRecord(int id, DatabaseRecord& record) {
    seekToBeginning();
    int tempID;
    char buffer[record.getRecordSize() - sizeof(int)];
    while (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(buffer, record.getRecordSize() - sizeof(tempID));
        if (tempID == id) {
            record.setID(tempID);
            record.readFromBuffer(buffer);
            return true;
        }
    }
    return false;
}

bool DatabaseRecord::deleteRecord(int id) {
    seekToBeginning();
    int tempID;
    streampos posToDelete;
    bool found = false;
    char buffer[1024]; // Assuming max record size for simplicity

    // Locate the record to delete
    while (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        posToDelete = dbFile.tellg();
        dbFile.read(buffer, 1024 - sizeof(tempID)); // Adjust buffer size as needed
        if (tempID == id) {
            found = true;
            break;
        }
    }

    if (!found) return false;

    // Move the last record to the position of the deleted record
    dbFile.seekg(-static_cast<int>(sizeof(buffer)), ios::end);
    streampos lastPos = dbFile.tellg();
    dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID));
    dbFile.read(buffer, 1024 - sizeof(tempID));

    dbFile.seekp(posToDelete - sizeof(tempID) - (1024 - sizeof(tempID)), ios::beg);
    dbFile.write(reinterpret_cast<const char*>(&tempID), sizeof(tempID));
    dbFile.write(buffer, 1024 - sizeof(tempID));
    dbFile.flush();

    dbFile.close();
    if (truncate("Database.dat", lastPos) != 0) {
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

// ----- ChangeRequest methods -----
ChangeRequest::ChangeRequest() : id(0) {
    memset(description, 0, sizeof(description));
}

ChangeRequest::ChangeRequest(int id, const char* description) : id(id) {
    strncpy(this->description, description, sizeof(this->description));
}

ChangeRequest::~ChangeRequest() {}

void ChangeRequest::setID(int id) {
    this->id = id;
}

int ChangeRequest::getID() const {
    return id;
}

void ChangeRequest::setDescription(const char* description) {
    strncpy(this->description, description, sizeof(this->description));
}

const char* ChangeRequest::getDescription() const {
    return description;
}

bool ChangeRequest::writeRecord() const {
    dbFile.seekp(0, ios::end);
    dbFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
    dbFile.write(description, sizeof(description));
    dbFile.flush();
    return true;
}

bool ChangeRequest::readRecord() {
    int tempID;
    char tempDesc[30];
    if (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(tempDesc, sizeof(tempDesc));
        setID(tempID);
        setDescription(tempDesc);
        return true;
    }
    return false;
}

int ChangeRequest::getRecordSize() const {
    return sizeof(id) + sizeof(description);
}

void ChangeRequest::readFromBuffer(const char* buffer) {
    memcpy(description, buffer, sizeof(description));
}

// ----- User methods -----
User::User() : id(0) {
    memset(name, 0, sizeof(name));
}

User::User(int id, const char* name) : id(id) {
    strncpy(this->name, name, sizeof(this->name));
}

User::~User() {}

void User::setInfo(const char* name) {
    strncpy(this->name, name, sizeof(this->name));
}

const char* User::getInfo() const {
    return name;
}

void User::setID(int id) {
    this->id = id;
}

int User::getID() const {
    return id;
}

bool User::writeRecord() const {
    dbFile.seekp(0, ios::end);
    dbFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
    dbFile.write(name, sizeof(name));
    dbFile.flush();
    return true;
}

bool User::readRecord() {
    int tempID;
    char tempName[30];
    if (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(tempName, sizeof(tempName));
        setID(tempID);
        setInfo(tempName);
        return true;
    }
    return false;
}

int User::getRecordSize() const {
    return sizeof(id) + sizeof(name);
}

void User::readFromBuffer(const char* buffer) {
    memcpy(name, buffer, sizeof(name));
}

// ----- ChangeItem methods -----
ChangeItem::ChangeItem() : id(0), status(0), priority(0) {
    memset(productID, 0, sizeof(productID));
    memset(description, 0, sizeof(description));
    memset(requester, 0, sizeof(requester));
}

ChangeItem::ChangeItem(int id, const char* productID, const char* description, int status, int priority, const char* requester)
    : id(id), status(status), priority(priority) {
    strncpy(this->productID, productID, sizeof(this->productID));
    strncpy(this->description, description, sizeof(this->description));
    strncpy(this->requester, requester, sizeof(this->requester));
}

ChangeItem::~ChangeItem() {}

void ChangeItem::setID(int id) {
    this->id = id;
}

int ChangeItem::getID() const {
    return id;
}

void ChangeItem::setProductID(const char* productID) {
    strncpy(this->productID, productID, sizeof(this->productID));
}

const char* ChangeItem::getProductID() const {
    return productID;
}

void ChangeItem::setDescription(const char* description) {
    strncpy(this->description, description, sizeof(this->description));
}

const char* ChangeItem::getDescription() const {
    return description;
}

void ChangeItem::setStatus(int status) {
    this->status = status;
}

int ChangeItem::getStatus() const {
    return status;
}

void ChangeItem::setPriority(int priority) {
    this->priority = priority;
}

int ChangeItem::getPriority() const {
    return priority;
}

void ChangeItem::setRequester(const char* requester) {
    strncpy(this->requester, requester, sizeof(this->requester));
}

const char* ChangeItem::getRequester() const {
    return requester;
}

bool ChangeItem::writeRecord() const {
    dbFile.seekp(0, ios::end);
    dbFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
    dbFile.write(productID, sizeof(productID));
    dbFile.write(description, sizeof(description));
    dbFile.write(reinterpret_cast<const char*>(&status), sizeof(status));
    dbFile.write(reinterpret_cast<const char*>(&priority), sizeof(priority));
    dbFile.write(requester, sizeof(requester));
    dbFile.flush();
    return true;
}

bool ChangeItem::readRecord() {
    int tempID, tempStatus, tempPriority;
    char tempProductID[30], tempDescription[30], tempRequester[30];

    if (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(tempProductID, sizeof(tempProductID));
        dbFile.read(tempDescription, sizeof(tempDescription));
        dbFile.read(reinterpret_cast<char*>(&tempStatus), sizeof(tempStatus));
        dbFile.read(reinterpret_cast<char*>(&tempPriority), sizeof(tempPriority));
        dbFile.read(tempRequester, sizeof(tempRequester));

        setID(tempID);
        setProductID(tempProductID);
        setDescription(tempDescription);
        setStatus(tempStatus);
        setPriority(tempPriority);
        setRequester(tempRequester);

        return true;
    }
    return false;
}

int ChangeItem::getRecordSize() const {
    return sizeof(id) + sizeof(productID) + sizeof(description) + sizeof(status) + sizeof(priority) + sizeof(requester);
}

void ChangeItem::readFromBuffer(const char* buffer) {
    memcpy(productID, buffer, sizeof(productID));
    memcpy(description, buffer + sizeof(productID), sizeof(description));
    memcpy(&status, buffer + sizeof(productID) + sizeof(description), sizeof(status));
    memcpy(&priority, buffer + sizeof(productID) + sizeof(description) + sizeof(status), sizeof(priority));
    memcpy(requester, buffer + sizeof(productID) + sizeof(description) + sizeof(status) + sizeof(priority), sizeof(requester));
}

bool ChangeItem::updStatus(int id, int newStatus) {
    ChangeItem changeItem;
    if (findRecord(id, changeItem)) {
        changeItem.setStatus(newStatus);
        changeItem.writeRecord();
        return true;
    }
    return false;
}

bool ChangeItem::updRelease(int id, int newRelease) {
    // Implementation of updating release
    return false;
}

bool ChangeItem::updPriority(int id, int newPriority) {
    ChangeItem changeItem;
    if (findRecord(id, changeItem)) {
        changeItem.setPriority(newPriority);
        changeItem.writeRecord();
        return true;
    }
    return false;
}

bool ChangeItem::updDesc(int id, const char* newDescription) {
    ChangeItem changeItem;
    if (findRecord(id, changeItem)) {
        changeItem.setDescription(newDescription);
        changeItem.writeRecord();
        return true;
    }
    return false;
}

bool ChangeItem::showRequester(int id) {
    ChangeItem changeItem;
    if (findRecord(id, changeItem)) {
        cout << "Requester: " << changeItem.getRequester() << endl;
        return true;
    }
    return false;
}

// ----- ProductRelease methods -----
ProductRelease::ProductRelease() : id(0) {
    memset(name, 0, sizeof(name));
    memset(version, 0, sizeof(version));
}

ProductRelease::ProductRelease(int id, const char* name, const char* version) : id(id) {
    strncpy(this->name, name, sizeof(this->name));
    strncpy(this->version, version, sizeof(this->version));
}

ProductRelease::~ProductRelease() {}

void ProductRelease::setID(int id) {
    this->id = id;
}

int ProductRelease::getID() const {
    return id;
}

void ProductRelease::setName(const char* name) {
    strncpy(this->name, name, sizeof(this->name));
}

const char* ProductRelease::getName() const {
    return name;
}

void ProductRelease::setVersion(const char* version) {
    strncpy(this->version, version, sizeof(this->version));
}

const char* ProductRelease::getVersion() const {
    return version;
}

bool ProductRelease::writeRecord() const {
    dbFile.seekp(0, ios::end);
    dbFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
    dbFile.write(name, sizeof(name));
    dbFile.write(version, sizeof(version));
    dbFile.flush();
    return true;
}

bool ProductRelease::readRecord() {
    int tempID;
    char tempName[30], tempVersion[30];
    if (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(tempName, sizeof(tempName));
        dbFile.read(tempVersion, sizeof(tempVersion));
        setID(tempID);
        setName(tempName);
        setVersion(tempVersion);
        return true;
    }
    return false;
}

int ProductRelease::getRecordSize() const {
    return sizeof(id) + sizeof(name) + sizeof(version);
}

void ProductRelease::readFromBuffer(const char* buffer) {
    memcpy(name, buffer, sizeof(name));
    memcpy(version, buffer + sizeof(name), sizeof(version));
}

bool ProductRelease::addRelease(const ProductRelease& release) {
    dbFile.seekp(0, ios::end);
    dbFile.write(reinterpret_cast<const char*>(&release.id), sizeof(release.id));
    dbFile.write(release.name, sizeof(release.name));
    dbFile.write(release.version, sizeof(release.version));
    dbFile.flush();
    return true;
}

bool ProductRelease::addProduct(int id, const char* name) {
    // Implementation of adding a product
    return false;
}

bool ProductRelease::showProduct(int id) {
    // Implementation of showing a product
    return false;
}

bool ProductRelease::showRelease(int id) {
    // Implementation of showing a release
    return false;
}

// Functions to open and close all database files
void openDatabase() {
    DatabaseRecord::openFile();
}

void closeDatabase() {
    DatabaseRecord::closeFile();
}

// Function to truncate a file
int truncateFile(const char* path, off_t length) {
    int fd = open(path, O_WRONLY);
    if (fd == -1) {
        return -1;
    }
    int result = ftruncate(fd, length);
    close(fd);
    return result;
}
