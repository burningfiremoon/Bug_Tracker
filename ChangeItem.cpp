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
#include "ChangeItem.h"
#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;

const int ChangeItem::recordSize = sizeof(changeID) + sizeof(productName) + sizeof(changeDescription) + sizeof(status) + sizeof(priority) + sizeof(releaseID) + sizeof(dateFirstReported);

ChangeItem::ChangeItem(const char* changeID) {
    strncpy(this->changeID, changeID, sizeof(this->changeID));
    status = 0;
    priority = 0;
    memset(productName, 0, sizeof(productName));
    memset(changeDescription, 0, sizeof(changeDescription));
    memset(releaseID, 0, sizeof(releaseID));
}

ChangeItem::ChangeItem(const ChangeItem& data) {
    strncpy(this->changeID, data.changeID, sizeof(this->changeID));
    strncpy(this->productName, data.productName, sizeof(this->productName));
    strncpy(this->changeDescription, data.changeDescription, sizeof(this->changeDescription));
    this->status = data.status;
    this->priority = data.priority;
    strncpy(this->releaseID, data.releaseID, sizeof(this->releaseID));
    this->dateFirstReported = data.dateFirstReported;
}

ChangeItem::~ChangeItem() {}

void ChangeItem::setChangeID(const char* changeID) {
    strncpy(this->changeID, changeID, sizeof(this->changeID));
}

const char* ChangeItem::getChangeID() const {
    return changeID;
}

void ChangeItem::setProductName(const char* productName) {
    strncpy(this->productName, productName, sizeof(this->productName));
}

const char* ChangeItem::getProductName() const {
    return productName;
}

void ChangeItem::setChangeDescription(const char* changeDescription) {
    strncpy(this->changeDescription, changeDescription, sizeof(this->changeDescription));
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

void ChangeItem::setReleaseID(const char* releaseID) {
    strncpy(this->releaseID, releaseID, sizeof(this->releaseID));
}

const char* ChangeItem::getReleaseID() const {
    return releaseID;
}

void ChangeItem::setDateFirstReported(Date date) {
    this->dateFirstReported = date;
}

Date ChangeItem::getDateFirstReported() const {
    return dateFirstReported;
}

bool ChangeItem::writeRecord(fstream &dbFile) const {
    dbFile.seekp(0, ios::end);
    dbFile.write(changeID, sizeof(changeID));
    dbFile.write(productName, sizeof(productName));
    dbFile.write(changeDescription, sizeof(changeDescription));
    dbFile.write(reinterpret_cast<const char*>(&status), sizeof(status));
    dbFile.write(reinterpret_cast<const char*>(&priority), sizeof(priority));
    dbFile.write(releaseID, sizeof(releaseID));
    dbFile.write(reinterpret_cast<const char*>(&dateFirstReported), sizeof(dateFirstReported));
    dbFile.flush();
    return true;
}

bool ChangeItem::readRecord(fstream &dbFile) {
    char tempChangeID[6];
    char tempProductName[31];
    char tempChangeDescription[31];
    int tempStatus, tempPriority;
    char tempReleaseID[9];
    Date tempDateFirstReported;

    if (dbFile.read(tempChangeID, sizeof(tempChangeID))) {
        dbFile.read(tempProductName, sizeof(tempProductName));
        dbFile.read(tempChangeDescription, sizeof(tempChangeDescription));
        dbFile.read(reinterpret_cast<char*>(&tempStatus), sizeof(tempStatus));
        dbFile.read(reinterpret_cast<char*>(&tempPriority), sizeof(tempPriority));
        dbFile.read(tempReleaseID, sizeof(tempReleaseID));
        dbFile.read(reinterpret_cast<char*>(&tempDateFirstReported), sizeof(tempDateFirstReported));

        setChangeID(tempChangeID);
        setProductName(tempProductName);
        setChangeDescription(tempChangeDescription);
        setStatus(tempStatus);
        setPriority(tempPriority);
        setReleaseID(tempReleaseID);
        setDateFirstReported(tempDateFirstReported);

        return true;
    }
    return false;
}

int ChangeItem::getRecordSize() const {
    return sizeof(changeID) + sizeof(productName) + sizeof(changeDescription) + sizeof(status) + sizeof(priority) + sizeof(releaseID) + sizeof(dateFirstReported);
}

void ChangeItem::readFromBuffer(const char* buffer) {
    memcpy(changeID, buffer, sizeof(changeID));
    memcpy(productName, buffer + sizeof(changeID), sizeof(productName));
    memcpy(changeDescription, buffer + sizeof(changeID) + sizeof(productName), sizeof(changeDescription));
    memcpy(&status, buffer + sizeof(changeID) + sizeof(productName) + sizeof(changeDescription), sizeof(status));
    memcpy(&priority, buffer + sizeof(changeID) + sizeof(productName) + sizeof(changeDescription) + sizeof(status), sizeof(priority));
    memcpy(releaseID, buffer + sizeof(changeID) + sizeof(productName) + sizeof(changeDescription) + sizeof(status) + sizeof(priority), sizeof(releaseID));
    memcpy(&dateFirstReported, buffer + sizeof(changeID) + sizeof(productName) + sizeof(changeDescription) + sizeof(status) + sizeof(priority) + sizeof(releaseID), sizeof(dateFirstReported));
}

bool ChangeItem::updStatus(const char* id, int newStatus) {
    ChangeItem changeItem(id);
    if (findRecord(id, changeItem)) {
        changeItem.setStatus(newStatus);
        changeItem.writeRecord(dbFile);
        return true;
    }
    return false;
}

bool ChangeItem::updRelease(const char* id, const char* newRelease) {
    ChangeItem changeItem(id);
    if (findRecord(id, changeItem)) {
        changeItem.setReleaseID(newRelease);
        changeItem.writeRecord(dbFile);
        return true;
    }
    return false;
}

bool ChangeItem::updPriority(const char* id, int newPriority) {
    ChangeItem changeItem(id);
    if (findRecord(id, changeItem)) {
        changeItem.setPriority(newPriority);
        changeItem.writeRecord(dbFile);
        return true;
    }
    return false;
}

bool ChangeItem::updDesc(const char* id, const char* newDescription) {
    ChangeItem changeItem(id);
    if (findRecord(id, changeItem)) {
        changeItem.setChangeDescription(newDescription);
        changeItem.writeRecord(dbFile);
        return true;
    }
    return false;
}
