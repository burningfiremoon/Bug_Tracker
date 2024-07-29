#include "ChangeRequest.h"
#include <iostream>
#include <cstring>

using namespace std;

// Static Member Initialization
const int ChangeRequest::recordSize = sizeof(changeID) + sizeof(requesterName) + sizeof(description) + sizeof(reportedDate) + sizeof(priority) + sizeof(state);

// Constructor
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

// Copy Constructor
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

// Destructor
ChangeRequest::~ChangeRequest() {}

// Setters and Getters
void ChangeRequest::setChangeID(const char* changeID) {
    strncpy(this->changeID, changeID, sizeof(this->changeID) - 1);
    this->changeID[6] = '\0'; // Ensure null termination
}

const char* ChangeRequest::getChangeID() const {
    return changeID;
}

void ChangeRequest::setRequesterName(const char* requesterName) {
    strncpy(this->requesterName, requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[30] = '\0'; // Ensure null termination
}

const char* ChangeRequest::getRequesterName() const {
    return requesterName;
}

void ChangeRequest::setDescription(const char* description) {
    strncpy(this->description, description, sizeof(this->description) - 1);
    this->description[29] = '\0'; // Ensure null termination
}

const char* ChangeRequest::getDescription() const {
    return description;
}

void ChangeRequest::setReportedDate(Date date) {
    this->reportedDate = date;
}

Date ChangeRequest::getReportedDate() const {
    return reportedDate;
}

void ChangeRequest::setPriority(int priority) {
    this->priority = priority;
}

int ChangeRequest::getPriority() const {
    return priority;
}

void ChangeRequest::setState(Status state) {
    this->state = state;
}

Status ChangeRequest::getState() const {
    return state;
}

// File Operations
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

bool ChangeRequest::readRecord(fstream &dbFile) {
    char tempChangeID[7];
    char tempRequesterName[31];
    char tempDescription[31];
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

int ChangeRequest::getRecordSize() const {
    return sizeof(changeID) + sizeof(requesterName) + sizeof(description) + sizeof(reportedDate) + sizeof(priority) + sizeof(state);
}

void ChangeRequest::readFromBuffer(const char* buffer) {
    memcpy(changeID, buffer, sizeof(changeID));
    memcpy(requesterName, buffer + sizeof(changeID), sizeof(requesterName));
    memcpy(description, buffer + sizeof(changeID) + sizeof(requesterName), sizeof(description));
    memcpy(&reportedDate, buffer + sizeof(changeID) + sizeof(requesterName) + sizeof(description), sizeof(reportedDate));
    memcpy(&priority, buffer + sizeof(changeID) + sizeof(requesterName) + sizeof(description) + sizeof(reportedDate), sizeof(priority));
    memcpy(&state, buffer + sizeof(changeID) + sizeof(requesterName) + sizeof(description) + sizeof(reportedDate) + sizeof(priority), sizeof(state));
}
