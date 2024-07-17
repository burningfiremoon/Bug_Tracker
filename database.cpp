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
fstream ChangeRequest::dbFile;
fstream User::dbFile;
fstream ChangeItem::dbFile;
fstream ProductRelease::dbFile;

//-------------------------------------
// Function definitions

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

void ChangeRequest::openFile() {
    dbFile.open("ChangeRequest.dat", ios::in | ios::out | ios::binary);
    if (!dbFile) {
        dbFile.open("ChangeRequest.dat", ios::out | ios::binary);
        dbFile.close();
        dbFile.open("ChangeRequest.dat", ios::in | ios::out | ios::binary);
    }
    if (!dbFile.is_open()) {
        cerr << "Error opening ChangeRequest file." << endl;
        exit(1);
    }
}

void ChangeRequest::closeFile() {
    if (dbFile.is_open()) {
        dbFile.close();
    }
}

bool ChangeRequest::writeRecord(const ChangeRequest& changeRequest) {
    dbFile.seekp(0, ios::end);
    dbFile.write(reinterpret_cast<const char*>(&changeRequest.id), sizeof(changeRequest.id));
    dbFile.write(changeRequest.description, sizeof(changeRequest.description));
    dbFile.flush();
    return true;
}

bool ChangeRequest::getNext(ChangeRequest& changeRequest) {
    int tempID;
    char tempDesc[30];
    if (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(tempDesc, sizeof(tempDesc));
        changeRequest.setID(tempID);
        changeRequest.setDescription(tempDesc);
        return true;
    }
    return false;
}

bool ChangeRequest::findRecord(int id, ChangeRequest& changeRequest) {
    seekToBeginning();
    int tempID;
    char tempDesc[30];
    while (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(tempDesc, sizeof(tempDesc));
        if (tempID == id) {
            changeRequest.setID(tempID);
            changeRequest.setDescription(tempDesc);
            return true;
        }
    }
    return false;
}

bool ChangeRequest::deleteRecord(int id) {
    seekToBeginning();
    ChangeRequest temp;
    streampos posToDelete;
    bool found = false;

    while (dbFile.read(reinterpret_cast<char*>(&temp.id), sizeof(temp.id))) {
        posToDelete = dbFile.tellg();
        dbFile.read(temp.description, sizeof(temp.description));
        if (temp.id == id) {
            found = true;
            break;
        }
    }

    if (!found) return false;

    dbFile.seekg(-recordSize, ios::end);
    streampos lastPos = dbFile.tellg();
    dbFile.read(reinterpret_cast<char*>(&temp.id), sizeof(temp.id));
    dbFile.read(temp.description, sizeof(temp.description));

    dbFile.seekp(posToDelete - sizeof(temp.id) - sizeof(temp.description), ios::beg);
    dbFile.write(reinterpret_cast<const char*>(&temp.id), sizeof(temp.id));
    dbFile.write(temp.description, sizeof(temp.description));
    dbFile.flush();

    dbFile.close();
    if (truncate("ChangeRequest.dat", lastPos) != 0) {
        cerr << "Error truncating ChangeRequest file." << endl;
        return false;
    }
    openFile();

    return true;
}

void ChangeRequest::seekToBeginning() {
    dbFile.clear();
    dbFile.seekg(0, ios::beg);
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

void User::openFile() {
    dbFile.open("User.dat", ios::in | ios::out | ios::binary);
    if (!dbFile) {
        dbFile.open("User.dat", ios::out | ios::binary);
        dbFile.close();
        dbFile.open("User.dat", ios::in | ios::out | ios::binary);
    }
    if (!dbFile.is_open()) {
        cerr << "Error opening User file." << endl;
        exit(1);
    }
}

void User::closeFile() {
    if (dbFile.is_open()) {
        dbFile.close();
    }
}

bool User::writeRecord(const User& user) {
    dbFile.seekp(0, ios::end);
    dbFile.write(reinterpret_cast<const char*>(&user.id), sizeof(user.id));
    dbFile.write(user.name, sizeof(user.name));
    dbFile.flush();
    return true;
}

bool User::getNext(User& user) {
    int tempID;
    char tempName[30];
    if (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(tempName, sizeof(tempName));
        user.setID(tempID);
        user.setInfo(tempName);
        return true;
    }
    return false;
}

bool User::findRecord(int id, User& user) {
    seekToBeginning();
    int tempID;
    char tempName[30];
    while (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(tempName, sizeof(tempName));
        if (tempID == id) {
            user.setID(tempID);
            user.setInfo(tempName);
            return true;
        }
    }
    return false;
}

bool User::deleteRecord(int id) {
    seekToBeginning();
    User temp;
    streampos posToDelete;
    bool found = false;

    while (dbFile.read(reinterpret_cast<char*>(&temp.id), sizeof(temp.id))) {
        posToDelete = dbFile.tellg();
        dbFile.read(temp.name, sizeof(temp.name));
        if (temp.id == id) {
            found = true;
            break;
        }
    }

    if (!found) return false;

    dbFile.seekg(-recordSize, ios::end);
    streampos lastPos = dbFile.tellg();
    dbFile.read(reinterpret_cast<char*>(&temp.id), sizeof(temp.id));
    dbFile.read(temp.name, sizeof(temp.name));

    dbFile.seekp(posToDelete - sizeof(temp.id) - sizeof(temp.name), ios::beg);
    dbFile.write(reinterpret_cast<const char*>(&temp.id), sizeof(temp.id));
    dbFile.write(temp.name, sizeof(temp.name));
    dbFile.flush();

    dbFile.close();
    if (truncate("User.dat", lastPos) != 0) {
        cerr << "Error truncating User file." << endl;
        return false;
    }
    openFile();

    return true;
}

void User::seekToBeginning() {
    dbFile.clear();
    dbFile.seekg(0, ios::beg);
}

// ChangeItem methods
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

void ChangeItem::openFile() {
    dbFile.open("ChangeItem.dat", ios::in | ios::out | ios::binary);
    if (!dbFile) {
        dbFile.open("ChangeItem.dat", ios::out | ios::binary);
        dbFile.close();
        dbFile.open("ChangeItem.dat", ios::in | ios::out | ios::binary);
    }
    if (!dbFile.is_open()) {
        cerr << "Error opening ChangeItem file." << endl;
        exit(1);
    }
}

void ChangeItem::closeFile() {
    if (dbFile.is_open()) {
        dbFile.close();
    }
}

bool ChangeItem::writeRecord(const ChangeItem& changeItem) {
    dbFile.seekp(0, ios::end);
    dbFile.write(reinterpret_cast<const char*>(&changeItem.id), sizeof(changeItem.id));
    dbFile.write(changeItem.productID, sizeof(changeItem.productID));
    dbFile.write(changeItem.description, sizeof(changeItem.description));
    dbFile.write(reinterpret_cast<const char*>(&changeItem.status), sizeof(changeItem.status));
    dbFile.write(reinterpret_cast<const char*>(&changeItem.priority), sizeof(changeItem.priority));
    dbFile.write(changeItem.requester, sizeof(changeItem.requester));
    dbFile.flush();
    return true;
}

bool ChangeItem::getNext(ChangeItem& changeItem) {
    int tempID, tempStatus, tempPriority;
    char tempProductID[30], tempDescription[30], tempRequester[30];

    if (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(tempProductID, sizeof(tempProductID));
        dbFile.read(tempDescription, sizeof(tempDescription));
        dbFile.read(reinterpret_cast<char*>(&tempStatus), sizeof(tempStatus));
        dbFile.read(reinterpret_cast<char*>(&tempPriority), sizeof(tempPriority));
        dbFile.read(tempRequester, sizeof(tempRequester));

        changeItem.setID(tempID);
        changeItem.setProductID(tempProductID);
        changeItem.setDescription(tempDescription);
        changeItem.setStatus(tempStatus);
        changeItem.setPriority(tempPriority);
        changeItem.setRequester(tempRequester);

        return true;
    }
    return false;
}

bool ChangeItem::findRecord(int id, ChangeItem& changeItem) {
    seekToBeginning();
    int tempID, tempStatus, tempPriority;
    char tempProductID[30], tempDescription[30], tempRequester[30];

    while (dbFile.read(reinterpret_cast<char*>(&tempID), sizeof(tempID))) {
        dbFile.read(tempProductID, sizeof(tempProductID));
        dbFile.read(tempDescription, sizeof(tempDescription));
        dbFile.read(reinterpret_cast<char*>(&tempStatus), sizeof(tempStatus));
        dbFile.read(reinterpret_cast<char*>(&tempPriority), sizeof(tempPriority));
        dbFile.read(tempRequester, sizeof(tempRequester));

        if (tempID == id) {
            changeItem.setID(tempID);
            changeItem.setProductID(tempProductID);
            changeItem.setDescription(tempDescription);
            changeItem.setStatus(tempStatus);
            changeItem.setPriority(tempPriority);
            changeItem.setRequester(tempRequester);
            return true;
        }
    }
    return false;
}

bool ChangeItem::deleteRecord(int id) {
    seekToBeginning();
    ChangeItem temp;
    streampos posToDelete;
    bool found = false;

    while (dbFile.read(reinterpret_cast<char*>(&temp.id), sizeof(temp.id))) {
        posToDelete = dbFile.tellg();
        dbFile.read(temp.productID, sizeof(temp.productID));
        dbFile.read(temp.description, sizeof(temp.description));
        dbFile.read(reinterpret_cast<char*>(&temp.status), sizeof(temp.status));
        dbFile.read(reinterpret_cast<char*>(&temp.priority), sizeof(temp.priority));
        dbFile.read(temp.requester, sizeof(temp.requester));
        if (temp.id == id) {
            found = true;
            break;
        }
    }

    if (!found) return false;

    dbFile.seekg(-recordSize, ios::end);
    streampos lastPos = dbFile.tellg();
    dbFile.read(reinterpret_cast<char*>(&temp.id), sizeof(temp.id));
    dbFile.read(temp.productID, sizeof(temp.productID));
    dbFile.read(temp.description, sizeof(temp.description));
    dbFile.read(reinterpret_cast<char*>(&temp.status), sizeof(temp.status));
    dbFile.read(reinterpret_cast<char*>(&temp.priority), sizeof(temp.priority));
    dbFile.read(temp.requester, sizeof(temp.requester));

    dbFile.seekp(posToDelete - sizeof(temp.id) - sizeof(temp.productID) - sizeof(temp.description) - sizeof(temp.status) - sizeof(temp.priority) - sizeof(temp.requester), ios::beg);
    dbFile.write(reinterpret_cast<const char*>(&temp.id), sizeof(temp.id));
    dbFile.write(temp.productID, sizeof(temp.productID));
    dbFile.write(temp.description, sizeof(temp.description));
    dbFile.write(reinterpret_cast<const char*>(&temp.status), sizeof(temp.status));
    dbFile.write(reinterpret_cast<const char*>(&temp.priority), sizeof(temp.priority));
    dbFile.write(temp.requester, sizeof(temp.requester));
    dbFile.flush();

    dbFile.close();
    if (truncate("ChangeItem.dat", lastPos) != 0) {
        cerr << "Error truncating ChangeItem file." << endl;
        return false;
    }
    openFile();

    return true;
}

void ChangeItem::seekToBeginning() {
    dbFile.clear();
    dbFile.seekg(0, ios::beg);
}

// ProductRelease methods
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

void ProductRelease::openFile() {
    dbFile.open("ProductRelease.dat", ios::in | ios::out | ios::binary);
    if (!dbFile) {
        dbFile.open("ProductRelease.dat", ios::out | ios::binary);
        dbFile.close();
        dbFile.open("ProductRelease.dat", ios::in | ios::out | ios::binary);
    }
    if (!dbFile.is_open()) {
        cerr << "Error opening ProductRelease file." << endl;
        exit(1);
    }
}

void ProductRelease::closeFile() {
    if (dbFile.is_open()) {
        dbFile.close();
    }
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

void ProductRelease::seekToBeginning() {
    dbFile.clear();
    dbFile.seekg(0, ios::beg);
}


// Functions to open and close all database files
void openDatabase() {
    ChangeRequest::openFile();
    User::openFile();
    ChangeItem::openFile();
    ProductRelease::openFile();
}

void closeDatabase() {
    ChangeRequest::closeFile();
    User::closeFile();
    ChangeItem::closeFile();
    ProductRelease::closeFile();
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
