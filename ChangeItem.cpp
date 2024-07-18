#include "ChangeItem.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int ChangeItem::recordSize = sizeof(changeID) + sizeof(productName) + sizeof(changeDescription) + sizeof(status) + sizeof(priority) + sizeof(releaseID) + sizeof(dateFirstReported);

ChangeItem::ChangeItem(const char* changeID) {
    strncpy(this->changeID, changeID, sizeof(this->changeID) - 1);
    this->changeID[sizeof(this->changeID) - 1] = '\0'; // Ensure null termination
    status = 0;
    priority = 0;
    memset(productName, 0, sizeof(productName));
    memset(changeDescription, 0, sizeof(changeDescription));
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

ChangeItem::~ChangeItem() {}

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
    dbFile.seekp(0, ios::end);
    dbFile.write(changeID, sizeof(changeID));
    dbFile.write(productName, sizeof(productName));
    dbFile.write(changeDescription, sizeof(changeDescription));
    dbFile.write(reinterpret_cast<const char*>(&status), sizeof(status));
    dbFile.write(reinterpret_cast<const char*>(&priority), sizeof(priority));
    dbFile.write(reinterpret_cast<const char*>(&releaseID), sizeof(releaseID));
    dbFile.write(reinterpret_cast<const char*>(&dateFirstReported), sizeof(dateFirstReported));
    dbFile.flush();
    return true;
}

bool ChangeItem::readRecord(fstream &dbFile) {
    char tempChangeID[7];
    char tempProductName[31];
    char tempChangeDescription[31];
    int tempStatus, tempPriority;
    ReleaseID tempReleaseID;
    Date tempDateFirstReported;

    if (dbFile.read(tempChangeID, sizeof(tempChangeID))) {
        dbFile.read(tempProductName, sizeof(tempProductName));
        dbFile.read(tempChangeDescription, sizeof(tempChangeDescription));
        dbFile.read(reinterpret_cast<char*>(&tempStatus), sizeof(tempStatus));
        dbFile.read(reinterpret_cast<char*>(&tempPriority), sizeof(tempPriority));
        dbFile.read(reinterpret_cast<char*>(&tempReleaseID), sizeof(tempReleaseID));
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
    memcpy(&releaseID, buffer + sizeof(changeID) + sizeof(productName) + sizeof(changeDescription) + sizeof(status) + sizeof(priority), sizeof(releaseID));
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

bool ChangeItem::updRelease(const char* id, int newRelease) {
    ChangeItem changeItem(id);
    if (findRecord(id, changeItem)) {
        ReleaseID newReleaseID;
        snprintf(newReleaseID.id, sizeof(newReleaseID.id), "%08d", newRelease);
        changeItem.setReleaseID(newReleaseID);
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
