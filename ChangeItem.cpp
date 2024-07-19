//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 15-July-2024 - Created by Tanvir
Initial creation and setup of ChangeItem class
2.0 - 17-July-2024 - Modified by Charles
Added detailed comments and explanations
2.1 - 18-July-2024 - Modified by Skyler
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    ChangeItem.cpp

    This module contains the implementation of the ChangeItem class, which represents a change item record.
    The ChangeItem class encapsulates details such as change ID, product name, change description, status, 
    priority, release ID, and the date first reported. The purpose of this class is to provide a cohesive 
    representation of a change item and manage its read and write operations to a file. The attributes and 
    methods are placed together to provide high cohesion and facilitate easy management of change item records.

    Includes:
    - ChangeItem constructor and destructor
    - Getter and setter methods for various attributes
    - Methods to read and write records from/to a file
    - Static methods to update specific fields in a change item record
*/

#include "ChangeItem.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

const int ChangeItem::recordSize = sizeof(changeID) + sizeof(productName) + sizeof(changeDescription) + sizeof(status) + sizeof(priority) + sizeof(releaseID) + sizeof(dateFirstReported);

ChangeItem::ChangeItem(const char* changeID) {
    strncpy(this->changeID, changeID, sizeof(this->changeID) - 1);
    this->changeID[sizeof(this->changeID) - 1] = '\0'; // Ensure null termination
    status = 0;
    priority = 0;
    memset(productName, 0, sizeof(productName));
    memset(changeDescription, 0, sizeof(changeDescription));
    memset(releaseID.id, 0, sizeof(releaseID.id));
    dateFirstReported = {0, 0, 0};
}
ChangeItem::ChangeItem(const ChangeItem& data) {
    strncpy(this->changeID, data.changeID, sizeof(this->changeID) - 1);
    this->changeID[sizeof(this->changeID) - 1] = '\0'; // Ensure null termination
    strncpy(this->productName, data.productName, sizeof(this->productName) - 1);
    this->productName[sizeof(this->productName) - 1] = '\0'; // Ensure null termination
    strncpy(this->changeDescription, data.changeDescription, sizeof(this->changeDescription) - 1);
    this->changeDescription[sizeof(this->changeDescription) - 1] = '\0'; // Ensure null termination
    this->status = data.status;
    this->priority = data.priority;
    this->releaseID = data.releaseID;
    this->dateFirstReported = data.dateFirstReported;
}

void ChangeItem::setChangeID(const char* changeID) {
    strncpy(this->changeID, changeID, sizeof(this->changeID) - 1);
    this->changeID[sizeof(this->changeID) - 1] = '\0'; // Ensure null termination
}

const char* ChangeItem::getChangeID() const {
    return changeID;
}

void ChangeItem::setProductName(const char* productName) {
    strncpy(this->productName, productName, sizeof(this->productName) - 1);
    this->productName[sizeof(this->productName) - 1] = '\0'; // Ensure null termination
}

const char* ChangeItem::getProductName() const {
    return productName;
}

void ChangeItem::setChangeDescription(const char* changeDescription) {
    strncpy(this->changeDescription, changeDescription, sizeof(this->changeDescription) - 1);
    this->changeDescription[sizeof(this->changeDescription) - 1] = '\0'; // Ensure null termination
}

const char* ChangeItem::getChangeDescription() const {
    return changeDescription;
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

void ChangeItem::setReleaseID(ReleaseID releaseID) {
    this->releaseID = releaseID;
}

ReleaseID ChangeItem::getReleaseID() const {
    return releaseID;
}

void ChangeItem::setDateFirstReported(Date date) {
    this->dateFirstReported = date;
}

Date ChangeItem::getDateFirstReported() const {
    return dateFirstReported;
}

bool ChangeItem::writeRecord(fstream &dbFile) const {
    dbFile << changeID << " "
           << productName << " "
           << changeDescription << " "
           << status << " "
           << priority << " "
           << releaseID.id << " "
           << dateFirstReported.y << "-"
           << dateFirstReported.m << "-"
           << dateFirstReported.d << endl;
    return true;
}

bool ChangeItem::readRecord(fstream &dbFile) {
    string line;
    if (getline(dbFile, line)) {
        istringstream iss(line);
        string releaseIDStr, dateStr;
        iss >> changeID >> productName >> changeDescription >> status >> priority >> releaseIDStr >> dateStr;
        strncpy(releaseID.id, releaseIDStr.c_str(), sizeof(releaseID.id) - 1);
        releaseID.id[sizeof(releaseID.id) - 1] = '\0';
        sscanf(dateStr.c_str(), "%d-%d-%d", &dateFirstReported.y, &dateFirstReported.m, &dateFirstReported.d);
        return true;
    }
    return false;
}

int ChangeItem::getRecordSize() const {
    return sizeof(ChangeItem);
}

void ChangeItem::readFromBuffer(const char* buffer) {
    istringstream iss(buffer);
    string releaseIDStr, dateStr;
    iss >> changeID >> productName >> changeDescription >> status >> priority >> releaseIDStr >> dateStr;
    strncpy(releaseID.id, releaseIDStr.c_str(), sizeof(releaseID.id) - 1);
    releaseID.id[sizeof(releaseID.id) - 1] = '\0';
    sscanf(dateStr.c_str(), "%d-%d-%d", &dateFirstReported.y, &dateFirstReported.m, &dateFirstReported.d);
}

bool ChangeItem::updStatus(const char* id, int newStatus) {
    fstream &dbFile = DatabaseRecord::getFile();
    DatabaseRecord::seekToBeginning();
    string line;
    streampos pos;
    while (getline(dbFile, line)) {
        pos = dbFile.tellg();
        istringstream iss(line);
        string tempID;
        iss >> tempID;
        if (tempID == id) {
            dbFile.seekp(pos - streampos(line.size() + 1)); // Explicit cast to streampos
            ChangeItem changeItem(id);
            changeItem.readFromBuffer(line.c_str());
            changeItem.setStatus(newStatus);
            changeItem.writeRecord(dbFile);
            return true;
        }
    }
    return false;
}

bool ChangeItem::updPriority(const char* id, int newPriority) {
    fstream &dbFile = DatabaseRecord::getFile();
    DatabaseRecord::seekToBeginning();
    string line;
    streampos pos;
    while (getline(dbFile, line)) {
        pos = dbFile.tellg();
        istringstream iss(line);
        string tempID;
        iss >> tempID;
        if (tempID == id) {
            dbFile.seekp(pos - streampos(line.size() + 1)); // Explicit cast to streampos
            ChangeItem changeItem(id);
            changeItem.readFromBuffer(line.c_str());
            changeItem.setPriority(newPriority);
            changeItem.writeRecord(dbFile);
            return true;
        }
    }
    return false;
}
