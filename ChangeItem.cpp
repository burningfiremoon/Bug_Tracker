//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 15-July-2024 - Created by Tanvir
Initial creation and setup of ChangeItem class
2.0 - 17-July-2024 - Modified by Charles
Added detailed comments and explanations
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

//-------------------------------------
// Static Member Initialization
//-------------------------------------

const int ChangeItem::recordSize = sizeof(changeID) + sizeof(productName) + sizeof(changeDescription) + sizeof(status) + sizeof(priority) + sizeof(releaseID) + sizeof(dateFirstReported);

//-------------------------------------
// Constructor
//-------------------------------------
/*
    ChangeItem::ChangeItem(const char* changeID)
    - Purpose: Initialize a ChangeItem object with a given change ID.
    - Parameters:
        - const char* changeID (in): The change ID to initialize the ChangeItem with.
*/
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

//-------------------------------------
// Copy Constructor
//-------------------------------------
/*
    ChangeItem::ChangeItem(const ChangeItem& data)
    - Purpose: Copy constructor to create a copy of an existing ChangeItem object.
    - Parameters:
        - const ChangeItem& data (in): The ChangeItem object to copy.
*/
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

//-------------------------------------
// Destructor
//-------------------------------------
/*
    ChangeItem::~ChangeItem()
    - Purpose: Destructor to clean up resources used by the ChangeItem object.
*/
ChangeItem::~ChangeItem() {}

//-------------------------------------
// Setters and Getters
//-------------------------------------
/*
    void ChangeItem::setChangeID(const char* changeID)
    - Purpose: Set the change ID for the ChangeItem.
    - Parameters:
        - const char* changeID (in): The change ID to set.
*/
void ChangeItem::setChangeID(const char* changeID) {
    strncpy(this->changeID, changeID, sizeof(this->changeID) - 1);
    this->changeID[sizeof(this->changeID) - 1] = '\0'; // Ensure null termination
}

/*
    const char* ChangeItem::getChangeID() const
    - Purpose: Get the change ID of the ChangeItem.
    - Returns: const char* (out): The change ID of the ChangeItem.
*/
const char* ChangeItem::getChangeID() const {
    return changeID;
}

/*
    void ChangeItem::setProductName(const char* productName)
    - Purpose: Set the product name for the ChangeItem.
    - Parameters:
        - const char* productName (in): The product name to set.
*/
void ChangeItem::setProductName(const char* productName) {
    strncpy(this->productName, productName, sizeof(this->productName) - 1);
    this->productName[sizeof(this->productName) - 1] = '\0'; // Ensure null termination
}

/*
    const char* ChangeItem::getProductName() const
    - Purpose: Get the product name of the ChangeItem.
    - Returns: const char* (out): The product name of the ChangeItem.
*/
const char* ChangeItem::getProductName() const {
    return productName;
}

/*
    void ChangeItem::setChangeDescription(const char* changeDescription)
    - Purpose: Set the change description for the ChangeItem.
    - Parameters:
        - const char* changeDescription (in): The change description to set.
*/
void ChangeItem::setChangeDescription(const char* changeDescription) {
    strncpy(this->changeDescription, changeDescription, sizeof(this->changeDescription) - 1);
    this->changeDescription[sizeof(this->changeDescription) - 1] = '\0'; // Ensure null termination
}

/*
    const char* ChangeItem::getChangeDescription() const
    - Purpose: Get the change description of the ChangeItem.
    - Returns: const char* (out): The change description of the ChangeItem.
*/
const char* ChangeItem::getChangeDescription() const {
    return changeDescription;
}

/*
    void ChangeItem::setStatus(int status)
    - Purpose: Set the status for the ChangeItem.
    - Parameters:
        - int status (in): The status to set.
*/
void ChangeItem::setStatus(int status) {
    this->status = status;
}

/*
    int ChangeItem::getStatus() const
    - Purpose: Get the status of the ChangeItem.
    - Returns: int (out): The status of the ChangeItem.
*/
int ChangeItem::getStatus() const {
    return status;
}

/*
    void ChangeItem::setPriority(int priority)
    - Purpose: Set the priority for the ChangeItem.
    - Parameters:
        - int priority (in): The priority to set.
*/
void ChangeItem::setPriority(int priority) {
    this->priority = priority;
}

/*
    int ChangeItem::getPriority() const
    - Purpose: Get the priority of the ChangeItem.
    - Returns: int (out): The priority of the ChangeItem.
*/
int ChangeItem::getPriority() const {
    return priority;
}

/*
    void ChangeItem::setReleaseID(ReleaseID releaseID)
    - Purpose: Set the release ID for the ChangeItem.
    - Parameters:
        - ReleaseID releaseID (in): The release ID to set.
*/
void ChangeItem::setReleaseID(ReleaseID releaseID) {
    this->releaseID = releaseID;
}

/*
    ReleaseID ChangeItem::getReleaseID() const
    - Purpose: Get the release ID of the ChangeItem.
    - Returns: ReleaseID (out): The release ID of the ChangeItem.
*/
ReleaseID ChangeItem::getReleaseID() const {
    return releaseID;
}

/*
    void ChangeItem::setDateFirstReported(Date date)
    - Purpose: Set the date first reported for the ChangeItem.
    - Parameters:
        - Date date (in): The date first reported to set.
*/
void ChangeItem::setDateFirstReported(Date date) {
    this->dateFirstReported = date;
}

/*
    Date ChangeItem::getDateFirstReported() const
    - Purpose: Get the date first reported of the ChangeItem.
    - Returns: Date (out): The date first reported of the ChangeItem.
*/
Date ChangeItem::getDateFirstReported() const {
    return dateFirstReported;
}

//-------------------------------------
// File Operations
//-------------------------------------
/*
    bool ChangeItem::writeRecord(fstream &dbFile) const
    - Purpose: Write the ChangeItem record to the given file stream.
    - Parameters:
        - fstream &dbFile (in/out): The file stream to write the record to.
    - Returns: bool (out): True if the record is written successfully, false otherwise.
*/
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

/*
    bool ChangeItem::readRecord(fstream &dbFile)
    - Purpose: Read a ChangeItem record from the given file stream.
    - Parameters:
        - fstream &dbFile (in/out): The file stream to read the record from.
    - Returns: bool (out): True if the record is read successfully, false otherwise.
*/
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

/*
    int ChangeItem::getRecordSize() const
    - Purpose: Get the size of the ChangeItem record.
    - Returns: int (out): The size of the ChangeItem record.
*/
int ChangeItem::getRecordSize() const {
    return sizeof(ChangeItem);
}

/*
    void ChangeItem::readFromBuffer(const char* buffer)
    - Purpose: Read the ChangeItem record from a buffer.
    - Parameters:
        - const char* buffer (in): The buffer to read the record from.
*/
void ChangeItem::readFromBuffer(const char* buffer) {
    istringstream iss(buffer);
    string releaseIDStr, dateStr;
    iss >> changeID >> productName >> changeDescription >> status >> priority >> releaseIDStr >> dateStr;
    strncpy(releaseID.id, releaseIDStr.c_str(), sizeof(releaseID.id) - 1);
    releaseID.id[sizeof(releaseID.id) - 1] = '\0';
    sscanf(dateStr.c_str(), "%d-%d-%d", &dateFirstReported.y, &dateFirstReported.m, &dateFirstReported.d);
}

//-------------------------------------
// Static Methods for Updating Records
//-------------------------------------
/*
    bool ChangeItem::updStatus(const char* id, int newStatus)
    - Purpose: Update the status of a ChangeItem record with the given ID.
    - Parameters:
        - const char* id (in): The ID of the ChangeItem record to update.
        - int newStatus (in): The new status to set.
    - Returns: bool (out): True if the status is updated successfully, false otherwise.
*/
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

/*
    bool ChangeItem::updPriority(const char* id, int newPriority)
    - Purpose: Update the priority of a ChangeItem record with the given ID.
    - Parameters:
        - const char* id (in): The ID of the ChangeItem record to update.
        - int newPriority (in): The new priority to set.
    - Returns: bool (out): True if the priority is updated successfully, false otherwise.
*/
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
