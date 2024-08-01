#include "ChangeItem.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

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
    strcpy(status, StatusReported);  // Default status
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
    strncpy(this->status, data.status, StatusStringLength);
    this->status[StatusStringLength] = '\0'; // Ensure null termination
    this->priority = data.priority;
    this->releaseID = data.releaseID;
    this->dateFirstReported = data.dateFirstReported;
}

//-------------------------------------
// Default Constructor
//-------------------------------------
/*
    ChangeItem::ChangeItem()
    - Purpose: Initialize a blank ChangeItem object to use functions.
    - Parameters:
        - None
*/
ChangeItem::ChangeItem() {
    strcpy(status, StatusReported);  // Default status
    priority = 0;
    memset(changeID, 0, sizeof(changeID));
    memset(productName, 0, sizeof(productName));
    memset(changeDescription, 0, sizeof(changeDescription));
    memset(releaseID.id, 0, sizeof(releaseID.id));
    dateFirstReported = {0, 0, 0};
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
        - const char* changeDescription (in): The change description to set. The input string is copied into
          a fixed-length buffer and padded with spaces if necessary.
    - Post-condition: The description is stored in a fixed-length buffer, with any unused buffer space
      filled with spaces, ensuring that the buffer is null-terminated.
*/
void ChangeItem::setChangeDescription(const char* changeDescription) {
    // Copy the input description and pad with spaces
    size_t len = strlen(changeDescription);
    strncpy(this->changeDescription, changeDescription, sizeof(this->changeDescription) - 1);

    // If the description is shorter than the allocated space, pad with spaces
    if (len < sizeof(this->changeDescription) - 1) {
        memset(this->changeDescription + len, ' ', sizeof(this->changeDescription) - 1 - len);
    }

    // Ensure null termination
    this->changeDescription[sizeof(this->changeDescription) - 1] = '\0';
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
    void ChangeItem::setStatus(const char* status)
    - Purpose: Set the status for the ChangeItem.
    - Parameters:
        - const char* status (in): The status to set.
*/
void ChangeItem::setStatus(const char* status) {
    strncpy(this->status, status, StatusStringLength);
    this->status[StatusStringLength] = '\0'; // Ensure null termination
}

/*
    const char* ChangeItem::getStatus() const
    - Purpose: Get the status of the ChangeItem.
    - Returns: const char* (out): The status of the ChangeItem.
*/
const char* ChangeItem::getStatus() const {
    return this->status;
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
    if (dbFile.is_open()) {
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
    return false;
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
        readFromBuffer(line.c_str());
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
    // Extract fields from the buffer, ensure they are null-terminated
    strncpy(this->changeID, buffer, sizeof(this->changeID) - 1);
    this->changeID[sizeof(this->changeID) - 1] = '\0';
    strncpy(this->productName, buffer + sizeof(this->changeID), sizeof(this->productName) - 1);
    this->productName[sizeof(this->productName) - 1] = '\0';
    strncpy(this->changeDescription, buffer + sizeof(this->changeID) + sizeof(this->productName), sizeof(this->changeDescription) - 1);
    this->changeDescription[sizeof(this->changeDescription) - 1] = '\0';
    strncpy(this->status, buffer + sizeof(this->changeID) + sizeof(this->productName) + sizeof(this->changeDescription), StatusStringLength);
    this->status[StatusStringLength] = '\0';
    this->priority = *reinterpret_cast<const int*>(buffer + sizeof(this->changeID) + sizeof(this->productName) + sizeof(this->changeDescription) + sizeof(this->status));
    strncpy(this->releaseID.id, buffer + sizeof(this->changeID) + sizeof(this->productName) + sizeof(this->changeDescription) + sizeof(this->status) + sizeof(this->priority), sizeof(this->releaseID.id) - 1);
    this->releaseID.id[sizeof(this->releaseID.id) - 1] = '\0';
    this->dateFirstReported.y = *reinterpret_cast<const int*>(buffer + sizeof(this->changeID) + sizeof(this->productName) + sizeof(this->changeDescription) + sizeof(this->status) + sizeof(this->priority) + sizeof(this->releaseID.id));
    this->dateFirstReported.m = *reinterpret_cast<const int*>(buffer + sizeof(this->changeID) + sizeof(this->productName) + sizeof(this->changeDescription) + sizeof(this->status) + sizeof(this->priority) + sizeof(this->releaseID.id) + sizeof(this->dateFirstReported.y));
    this->dateFirstReported.d = *reinterpret_cast<const int*>(buffer + sizeof(this->changeID) + sizeof(this->productName) + sizeof(this->changeDescription) + sizeof(this->status) + sizeof(this->priority) + sizeof(this->releaseID.id) + sizeof(this->dateFirstReported.y) + sizeof(this->dateFirstReported.m));
}

//-------------------------------------
// Static Methods for Updating Records
//-------------------------------------
/*
    bool ChangeItem::updStatus(const char* id, const char* newStatus)
    - Purpose: Update the status of a ChangeItem record with the given ID.
    - Parameters:
        - const char* id (in): The ID of the ChangeItem record to update.
        - const char* newStatus (in): The new status to set.
    - Returns: bool (out): True if the status is updated successfully, false otherwise.
*/
bool ChangeItem::updStatus(const char* id, const char* newStatus) {
    // Open the database file
    ifstream dbFileIn("database.dat");
    if (!dbFileIn) {
        cerr << "Error opening database file for reading." << endl;
        return false;
    }

    // Temporary storage for file lines
    vector<string> lines;
    string line;
    bool recordFound = false;

    // Read the file line by line
    while (getline(dbFileIn, line)) {
        if (line.find(id) != string::npos) {
            // Record found, update status
            recordFound = true;
            string newStatusStr(newStatus);
            newStatusStr.resize(StatusStringLength, ' '); // Pad with spaces if necessary
            line.replace(80, StatusStringLength, newStatusStr); // Assuming status starts at position 80
        }
        lines.push_back(line);
    }

    dbFileIn.close();

    // Write back to the file if the record was found and updated
    if (recordFound) {
        ofstream dbFileOut("database.dat", ios::out | ios::trunc);
        if (!dbFileOut) {
            cerr << "Error opening database file for writing." << endl;
            return false;
        }

        for (const auto& l : lines) {
            dbFileOut << l << endl;
        }
        dbFileOut.close();
    }

    return recordFound;
}

/*
    bool ChangeItem::updRelease(const char* id, int newRelease)
    - Purpose: Update the release ID of a ChangeItem record with the given ID.
    - Parameters:
        - const char* id (in): The ID of the ChangeItem record to update.
        - int newRelease (in): The new release ID to set.
    - Returns: bool (out): True if the release ID is updated successfully, false otherwise.
*/
bool ChangeItem::updRelease(const char* id, int newRelease) {
    // Implementation would be similar to updStatus
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
    // Implementation would be similar to updStatus
    return false;
}

/*
    bool ChangeItem::updDesc(const char* id, const char* newDescription)
    - Purpose: Update the description of a ChangeItem record with the given ID.
    - Parameters:
        - const char* id (in): The ID of the ChangeItem record to update.
        - const char* newDescription (in): The new description to set.
    - Returns: bool (out): True if the description is updated successfully, false otherwise.
*/
bool ChangeItem::updDesc(const char* id, const char* newDescription) {
    // Implementation would be similar to updStatus
    return false;
}
