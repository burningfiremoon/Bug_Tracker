//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 14-July-2024 - Created by Tanvir
Initial creation and setup of ChangeRequest class
2.0 - 17-July-2024 - Modified by Charles
3.0 - 26-July-2024 - Modified by Anthony
4.0 - 29 July-2024 - Modified by Anthony
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    ChangeRequest.cpp

    This module contains the implementation of the ChangeRequest class, which represents a change request record.
    The ChangeRequest class encapsulates details such as change ID, requester name, description, status,
    priority, and the date first reported. The purpose of this class is to provide a cohesive representation of
    a change request and manage its read and write operations to a file. The attributes and methods are placed
    together to provide high cohesion and facilitate easy management of change request records.

    Includes:
    - ChangeRequest constructor and destructor
    - Getter and setter methods for various attributes
    - Methods to read and write records from/to a file
    - Static methods to update specific fields in a change request record
*/

#include "ChangeRequest.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

//-------------------------------------
// Static Member Initialization
//-------------------------------------
const int ChangeRequest::recordSize = sizeof(changeID) + sizeof(requesterName) + sizeof(description) + sizeof(status) + sizeof(priority) + sizeof(dateFirstReported);

//-------------------------------------
// Constructor
//-------------------------------------
/*
    ChangeRequest::ChangeRequest(const char* changeID)
    - Purpose: Initialize a ChangeRequest object with a given change ID.
    - Parameters:
        - const char* changeID (in): The change ID to initialize the ChangeRequest with.
*/
ChangeRequest::ChangeRequest(const char* changeID) {
    strncpy(this->changeID, changeID, sizeof(this->changeID) - 1);
    this->changeID[sizeof(this->changeID) - 1] = '\0'; // Ensure null termination
    strcpy(status, StatusReported);  // Default status
    priority = 0;
    memset(requesterName, 0, sizeof(requesterName));
    memset(description, 0, sizeof(description));
    dateFirstReported = {0, 0, 0};
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
ChangeRequest::ChangeRequest(const ChangeRequest& data) {
    strncpy(this->changeID, data.changeID, sizeof(this->changeID) - 1);
    this->changeID[sizeof(this->changeID) - 1] = '\0'; // Ensure null termination
    strncpy(this->requesterName, data.requesterName, sizeof(this->requesterName) - 1);
    this->requesterName[sizeof(this->requesterName) - 1] = '\0'; // Ensure null termination
    strncpy(this->description, data.description, sizeof(this->description) - 1);
    this->description[sizeof(this->description) - 1] = '\0'; // Ensure null termination
    strncpy(this->status, data.status, StatusStringLength);
    this->status[StatusStringLength] = '\0'; // Ensure null termination
    this->priority = data.priority;
    this->dateFirstReported = data.dateFirstReported;
}

//-------------------------------------
// Default Constructor
//-------------------------------------
/*
    ChangeRequest::ChangeRequest()
    - Purpose: Initialize a blank ChangeRequest object to use functions.
    - Parameters:
        - None
*/
ChangeRequest::ChangeRequest() {
    strcpy(status, StatusReported);  // Default status
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
    this->changeID[sizeof(this->changeID) - 1] = '\0'; // Ensure null termination
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
    this->requesterName[sizeof(this->requesterName) - 1] = '\0'; // Ensure null termination
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
        - const char* description (in): The description to set. The input string is copied into
          a fixed-length buffer and padded with spaces if necessary.
    - Post-condition: The description is stored in a fixed-length buffer, with any unused buffer space
      filled with spaces, ensuring that the buffer is null-terminated.
*/
void ChangeRequest::setDescription(const char* description) {
    // Copy the input description and pad with spaces
    size_t len = strlen(description);
    strncpy(this->description, description, sizeof(this->description) - 1);

    // If the description is shorter than the allocated space, pad with spaces
    if (len < sizeof(this->description) - 1) {
        memset(this->description + len, ' ', sizeof(this->description) - 1 - len);
    }

    // Ensure null termination
    this->description[sizeof(this->description) - 1] = '\0';
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
    void ChangeRequest::setStatus(const char* status)
    - Purpose: Set the status for the ChangeRequest.
    - Parameters:
        - const char* status (in): The status to set.
*/
void ChangeRequest::setStatus(const char* status) {
    strncpy(this->status, status, StatusStringLength);
    this->status[StatusStringLength] = '\0'; // Ensure null termination
}

/*
    const char* ChangeRequest::getStatus() const
    - Purpose: Get the status of the ChangeRequest.
    - Returns: const char* (out): The status of the ChangeRequest.
*/
const char* ChangeRequest::getStatus() const {
    return status;
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
    void ChangeRequest::setDateFirstReported(Date date)
    - Purpose: Set the date first reported for the ChangeRequest.
    - Parameters:
        - Date date (in): The date first reported to set.
*/
void ChangeRequest::setDateFirstReported(Date date) {
    this->dateFirstReported = date;
}

/*
    Date ChangeRequest::getDateFirstReported() const
    - Purpose: Get the date first reported of the ChangeRequest.
    - Returns: Date (out): The date first reported of the ChangeRequest.
*/
Date ChangeRequest::getDateFirstReported() const {
    return dateFirstReported;
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
    if (dbFile.is_open()) {
        dbFile << changeID << " "
               << requesterName << " "
               << description << " "
               << status << " "
               << priority << " "
               << dateFirstReported.y << "-"
               << dateFirstReported.m << "-"
               << dateFirstReported.d << endl;
        return true;
    }
    return false;
}

/*
    bool ChangeRequest::readRecord(fstream &dbFile)
    - Purpose: Read a ChangeRequest record from the given file stream.
    - Parameters:
        - fstream &dbFile (in/out): The file stream to read the record from.
    - Returns: bool (out): True if the record is read successfully, false otherwise.
*/
bool ChangeRequest::readRecord(fstream &dbFile) {
    string line;
    if (getline(dbFile, line)) {
        readFromBuffer(line.c_str());
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
    return sizeof(ChangeRequest);
}

/*
    void ChangeRequest::readFromBuffer(const char* buffer)
    - Purpose: Read the ChangeRequest record from a buffer.
    - Parameters:
        - const char* buffer (in): The buffer to read the record from.
*/
void ChangeRequest::readFromBuffer(const char* buffer) {
    istringstream iss(buffer);
    string dateStr;
    iss >> changeID >> requesterName >> description >> status >> priority >> dateStr;
    sscanf(dateStr.c_str(), "%d-%d-%d", &dateFirstReported.y, &dateFirstReported.m, &dateFirstReported.d);
}

//-------------------------------------
// Static Methods for Updating Records
//-------------------------------------
/*
    bool ChangeRequest::updStatus(const char* id, const char* newStatus)
    - Purpose: Update the status of a ChangeRequest record with the given ID.
    - Parameters:
        - const char* id (in): The ID of the ChangeRequest record to update.
        - const char* newStatus (in): The new status to set.
    - Returns: bool (out): True if the status is updated successfully, false otherwise.
*/
bool ChangeRequest::updStatus(const char* id, const char* newStatus) {
    // Ensure the file is opened correctly
    DatabaseRecord::closeFile();
    DatabaseRecord::openFile("database.dat");

    fstream &dbFile = DatabaseRecord::getFile();
    DatabaseRecord::seekToBeginning();
    string line;
    vector<string> lines;
    bool recordFound = false;

    while (getline(dbFile, line)) {
        istringstream iss(line);
        string tempID;
        iss >> tempID;
        if (tempID == id) {
            recordFound = true;
            ChangeRequest changeRequest(id);
            changeRequest.readFromBuffer(line.c_str());
            changeRequest.setStatus(newStatus);

            // Replace the line with the updated record
            ostringstream oss;
            oss << changeRequest.getChangeID() << " "
                << changeRequest.getRequesterName() << " "
                << changeRequest.getDescription() << " "
                << changeRequest.getStatus() << " "
                << changeRequest.getPriority() << " "
                << changeRequest.getDateFirstReported().y << "-"
                << changeRequest.getDateFirstReported().m << "-"
                << changeRequest.getDateFirstReported().d;
            lines.push_back(oss.str());
        } else {
            lines.push_back(line);
        }
    }

    // Rewrite the file with the updated contents
    if (recordFound) {
        dbFile.close();
        dbFile.open("database.dat", ios::out | ios::trunc);
        for (const auto& l : lines) {
            dbFile << l << endl;
        }
        dbFile.flush();
        dbFile.close(); // Close the file after writing
    } else {
        std::cout << "Record not found for ID: " << id << std::endl;
    }

    return recordFound;
}

/*
    bool ChangeRequest::updDescription(const char* id, const char* newDescription)
    - Purpose: Update the description of a ChangeRequest record with the given ID.
    - Parameters:
        - const char* id (in): The ID of the ChangeRequest record to update.
        - const char* newDescription (in): The new description to set.
    - Returns: bool (out): True if the description is updated successfully, false otherwise.
*/
bool ChangeRequest::updDescription(const char* id, const char* newDescription) {
    // Ensure the file is opened correctly
    DatabaseRecord::closeFile();
    DatabaseRecord::openFile("database.dat");

    fstream &dbFile = DatabaseRecord::getFile();
    DatabaseRecord::seekToBeginning();
    string line;
    vector<string> lines;
    bool recordFound = false;

    while (getline(dbFile, line)) {
        istringstream iss(line);
        string tempID;
        iss >> tempID;
        if (tempID == id) {
            recordFound = true;
            ChangeRequest changeRequest(id);
            changeRequest.readFromBuffer(line.c_str());
            changeRequest.setDescription(newDescription);

            // Replace the line with the updated record
            ostringstream oss;
            oss << changeRequest.getChangeID() << " "
                << changeRequest.getRequesterName() << " "
                << changeRequest.getDescription() << " "
                << changeRequest.getStatus() << " "
                << changeRequest.getPriority() << " "
                << changeRequest.getDateFirstReported().y << "-"
                << changeRequest.getDateFirstReported().m << "-"
                << changeRequest.getDateFirstReported().d;
            lines.push_back(oss.str());
        } else {
            lines.push_back(line);
        }
    }

    // Rewrite the file with the updated contents
    if (recordFound) {
        dbFile.close();
        dbFile.open("database.dat", ios::out | ios::trunc);
        for (const auto& l : lines) {
            dbFile << l << endl;
        }
        dbFile.flush();
        dbFile.close(); // Close the file after writing
    } else {
        std::cout << "Record not found for ID: " << id << std::endl;
    }

    return recordFound;
}
