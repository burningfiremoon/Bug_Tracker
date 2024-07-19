//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 15-July-2024 - Created by Tanvir
Initial creation and setup of ChangeRequest class
2.0 - 16-July-2024 - Modified by Anthony
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    ChangeRequest.cpp

    This module contains the implementation of the ChangeRequest class, which represents a change request record.
    The ChangeRequest class encapsulates details such as change ID, requester name, description, reported date,
    priority, and state. The purpose of this class is to provide a cohesive representation of a change request and 
    manage its read and write operations to a file. The attributes and methods are placed together to provide high
    cohesion and facilitate easy management of change request records.

    Includes:
    - ChangeRequest constructor and destructor
    - Getter and setter methods for various attributes
    - Methods to read and write records from/to a file
*/

#include "ChangeRequest.h"
#include <iostream>
#include <cstring>

using namespace std;

//-------------------------------------
// Static Member Initialization
//-------------------------------------

const int ChangeRequest::recordSize = sizeof(changeID) + sizeof(requesterName) + sizeof(description) + sizeof(reportedDate) + sizeof(priority) + sizeof(state);

//-------------------------------------
// Constructor
//-------------------------------------
/*
    ChangeRequest::ChangeRequest(const char* changeID, const char* requesterName)
    - Purpose: Initialize a ChangeRequest object with a given change ID and requester name.
    - Parameters:
        - const char* changeID (in): The change ID to initialize the ChangeRequest with.
        - const char* requesterName (in): The requester name to initialize the ChangeRequest with.
*/
ChangeRequest::ChangeRequest(const char* changeID, const char* requesterName) : DatabaseRecord() {
    strncpy(this->changeID, changeID, sizeof(this->changeID) - 1);
    this->changeID[6] = '\0'; // Ensure null termination
    strncpy(this->requesterName, requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
    memset(description, 0, sizeof(description));
    reportedDate = {0, 0, 0}; // Default date
    priority = 0;
    state = REPORTED; // Default state

    // Debug print
    cout << "Constructor: changeID = " << this->changeID << endl;
    cout << "Constructor: reportedDate = " << reportedDate.y << "-" << reportedDate.m << "-" << reportedDate.d << endl;
}

//-------------------------------------
// Copy Constructor
//-------------------------------------
/*
    ChangeRequest::ChangeRequest(const ChangeRequest& data)
    - Purpose: Copy constructor to create a copy of an existing ChangeRequest object.
    - Parameters:
        - const ChangeRequest& data (in): The ChangeRequest object to copy.
*/
ChangeRequest::ChangeRequest(const ChangeRequest& data) : DatabaseRecord() {
    strncpy(this->changeID, data.changeID, sizeof(this->changeID) - 1);
    this->changeID[6] = '\0'; // Ensure null termination
    strncpy(this->requesterName, data.requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
    strncpy(this->description, data.description, sizeof(this->description) - 1);
    this->description[29] = '\0'; // Ensure null termination
    this->reportedDate = data.reportedDate;
    this->priority = data.priority;
    this->state = data.state;
}

//-------------------------------------
// Destructor
//-------------------------------------
/*
    ChangeRequest::~ChangeRequest()
    - Purpose: Destructor to clean up resources used by the ChangeRequest object.
*/
ChangeRequest::~ChangeRequest() {}

//-------------------------------------
// Setters and Getters
//-------------------------------------
/*
    void ChangeRequest::setChangeID(const char* changeID)
    - Purpose: Set the change ID for the ChangeRequest.
    - Parameters:
        - const char* changeID (in): The change ID to set.
*/
void ChangeRequest::setChangeID(const char* changeID) {
    strncpy(this->changeID, changeID, sizeof(this->changeID) - 1);
    this->changeID[6] = '\0'; // Ensure null termination
}

/*
    const char* ChangeRequest::getChangeID() const
    - Purpose: Get the change ID of the ChangeRequest.
    - Returns: const char* (out): The change ID of the ChangeRequest.
*/
const char* ChangeRequest::getChangeID() const {
    return changeID;
}

/*
    void ChangeRequest::setRequesterName(const char* requesterName)
    - Purpose: Set the requester name for the ChangeRequest.
    - Parameters:
        - const char* requesterName (in): The requester name to set.
*/
void ChangeRequest::setRequesterName(const char* requesterName) {
    strncpy(this->requesterName, requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
}

/*
    const char* ChangeRequest::getRequesterName() const
    - Purpose: Get the requester name of the ChangeRequest.
    - Returns: const char* (out): The requester name of the ChangeRequest.
*/
const char* ChangeRequest::getRequesterName() const {
    return requesterName;
}

/*
    void ChangeRequest::setDescription(const char* description)
    - Purpose: Set the description for the ChangeRequest.
    - Parameters:
        - const char* description (in): The description to set.
*/
void ChangeRequest::setDescription(const char* description) {
    strncpy(this->description, description, sizeof(this->description) - 1);
    this->description[29] = '\0'; // Ensure null termination
}

/*
    const char* ChangeRequest::getDescription() const
    - Purpose: Get the description of the ChangeRequest.
    - Returns: const char* (out): The description of the ChangeRequest.
*/
const char* ChangeRequest::getDescription() const {
    return description;
}

/*
    void ChangeRequest::setReportedDate(Date date)
    - Purpose: Set the reported date for the ChangeRequest.
    - Parameters:
        - Date date (in): The reported date to set.
*/
void ChangeRequest::setReportedDate(Date date) {
    this->reportedDate = date;
}

/*
    Date ChangeRequest::getReportedDate() const
    - Purpose: Get the reported date of the ChangeRequest.
    - Returns: Date (out): The reported date of the ChangeRequest.
*/
Date ChangeRequest::getReportedDate() const {
    return reportedDate;
}

/*
    void ChangeRequest::setPriority(int priority)
    - Purpose: Set the priority for the ChangeRequest.
    - Parameters:
        - int priority (in): The priority to set.
*/
void ChangeRequest::setPriority(int priority) {
    this->priority = priority;
}

/*
    int ChangeRequest::getPriority() const
    - Purpose: Get the priority of the ChangeRequest.
    - Returns: int (out): The priority of the ChangeRequest.
*/
int ChangeRequest::getPriority() const {
    return priority;
}

/*
    void ChangeRequest::setState(Status state)
    - Purpose: Set the state for the ChangeRequest.
    - Parameters:
        - Status state (in): The state to set.
*/
void ChangeRequest::setState(Status state) {
    this->state = state;
}

/*
    Status ChangeRequest::getState() const
    - Purpose: Get the state of the ChangeRequest.
    - Returns: Status (out): The state of the ChangeRequest.
*/
Status ChangeRequest::getState() const {
    return state;
}

//-------------------------------------
// File Operations
//-------------------------------------
/*
    bool ChangeRequest::writeRecord(fstream &dbFile) const
    - Purpose: Write the ChangeRequest record to the given file stream.
    - Parameters:
        - fstream &dbFile (in/out): The file stream to write the record to.
    - Returns: bool (out): True if the record is written successfully, false otherwise.
*/
bool ChangeRequest::writeRecord(fstream &dbFile) const {
    dbFile.seekp(0, ios::end);
    dbFile.write(changeID, sizeof(changeID));
    dbFile.write(requesterName, sizeof(requesterName));
    dbFile.write(description, sizeof(description));
    dbFile.write(reinterpret_cast<const char*>(&reportedDate), sizeof(reportedDate));
    dbFile.write(reinterpret_cast<const char*>(&priority), sizeof(priority));
    dbFile.write(reinterpret_cast<const char*>(&state), sizeof(state));
    dbFile.flush();
    return true;
}

/*
    bool ChangeRequest::readRecord(fstream &dbFile)
    - Purpose: Read a ChangeRequest record from the given file stream.
    - Parameters:
        - fstream &dbFile (in/out): The file stream to read the record from.
    - Returns: bool (out): True if the record is read successfully, false otherwise.
*/
bool ChangeRequest::readRecord(fstream &dbFile) {
    char tempChangeID[7];
    char tempRequesterName[31];
    char tempDescription[30];
    Date tempDate;
    int tempPriority;
    Status tempState;

    if (dbFile.read(tempChangeID, sizeof(tempChangeID))) {
        dbFile.read(tempRequesterName, sizeof(tempRequesterName));
        dbFile.read(tempDescription, sizeof(tempDescription));
        dbFile.read(reinterpret_cast<char*>(&tempDate), sizeof(tempDate));
        dbFile.read(reinterpret_cast<char*>(&tempPriority), sizeof(tempPriority));
        dbFile.read(reinterpret_cast<char*>(&tempState), sizeof(tempState));

        setChangeID(tempChangeID);
        setRequesterName(tempRequesterName);
        setDescription(tempDescription);
        setReportedDate(tempDate);
        setPriority(tempPriority);
        setState(tempState);

        // Debug print
        cout << "ReadRecord: changeID = " << this->changeID << endl;
        cout << "ReadRecord: reportedDate = " << reportedDate.y << "-" << reportedDate.m << "-" << reportedDate.d << endl;

        return true;
    }
    return false;
}

/*
    int ChangeRequest::getRecordSize() const
    - Purpose: Get the size of the ChangeRequest record.
    - Returns: int (out): The size of the ChangeRequest record.
*/
int ChangeRequest::getRecordSize() const {
    return sizeof(changeID) + sizeof(requesterName) + sizeof(description) + sizeof(reportedDate) + sizeof(priority) + sizeof(state);
}

/*
    void ChangeRequest::readFromBuffer(const char* buffer)
    - Purpose: Read the ChangeRequest record from a buffer.
    - Parameters:
        - const char* buffer (in): The buffer to read the record from.
*/
void ChangeRequest::readFromBuffer(const char* buffer) {
    memcpy(changeID, buffer, sizeof(changeID));
    memcpy(requesterName, buffer + sizeof(changeID), sizeof(requesterName));
    memcpy(description, buffer + sizeof(changeID) + sizeof(requesterName), sizeof(description));
    memcpy(&reportedDate, buffer + sizeof(changeID) + sizeof(requesterName) + sizeof(description), sizeof(reportedDate));
    memcpy(&priority, buffer + sizeof(changeID) + sizeof(requesterName) + sizeof(description) + sizeof(reportedDate), sizeof(priority));
    memcpy(&state, buffer + sizeof(changeID) + sizeof(requesterName) + sizeof(description) + sizeof(reportedDate) + sizeof(priority), sizeof(state));
}
