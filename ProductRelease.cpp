//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 14-July-2024 - Created by Charles
Initial creation and setup of ProductRelease class
2.0 - 16-July-2024 - Modified by Anthony
Added detailed comments and explanations
2.1 - 18-July-2024 - Modified by Skyler
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    ProductRelease.cpp

    This module contains the implementation of the ProductRelease class, which represents a product release record.
    The ProductRelease class encapsulates details such as product name, release ID, and release date. The purpose 
    of this class is to provide a cohesive representation of a product release and manage its read and write operations 
    to a file. The attributes and methods are placed together to provide high cohesion and facilitate easy management 
    of product release records.

    Includes:
    - ProductRelease constructors and destructor
    - Getter and setter methods for various attributes
    - Methods to read and write records from/to a file
*/

#include "ProductRelease.h"
#include <cstring>

const int ProductRelease::recordSize = sizeof(productName) + sizeof(releaseID) + sizeof(releaseDate);

// Default constructor
ProductRelease::ProductRelease() {
    memset(productName, 0, sizeof(productName));
    memset(&releaseID, 0, sizeof(releaseID));
    memset(&releaseDate, 0, sizeof(releaseDate));
}

// Parameterized constructor
ProductRelease::ProductRelease(const char* name, ReleaseID id, Date date) {
    strncpy(productName, name, sizeof(productName) - 1);
    productName[sizeof(productName) - 1] = '\0';
    releaseID = id;
    releaseDate = date;
}

// Setter for product name
void ProductRelease::setProductName(const char* name) {
    strncpy(productName, name, sizeof(productName) - 1);
    productName[sizeof(productName) - 1] = '\0';
}

// Getter for product name (const)
const char* ProductRelease::getProductName() const {
    return productName;
}

// Mutable getter for product name (non-const)
char* ProductRelease::getProductNameMutable() {
    return productName;
}

// Setter for release ID
void ProductRelease::setReleaseID(ReleaseID id) {
    releaseID = id;
}

// Getter for release ID
ReleaseID ProductRelease::getReleaseID() const {
    return releaseID;
}

// Setter for release date
void ProductRelease::setReleaseDate(Date date) {
    releaseDate = date;
}

// Getter for release date
Date ProductRelease::getReleaseDate() const {
    return releaseDate;
}

// Write the ProductRelease record to a file
bool ProductRelease::writeRecord(fstream &dbFile) const {
    dbFile.seekp(0, ios::end);
    dbFile.write(productName, sizeof(productName));
    dbFile.write(reinterpret_cast<const char*>(&releaseID), sizeof(releaseID));
    dbFile.write(reinterpret_cast<const char*>(&releaseDate), sizeof(releaseDate));
    dbFile.flush();
    return true;
}

// Read a ProductRelease record from a file
bool ProductRelease::readRecord(fstream &dbFile) {
    if (dbFile.read(productName, sizeof(productName))) {
        dbFile.read(reinterpret_cast<char*>(&releaseID), sizeof(releaseID));
        dbFile.read(reinterpret_cast<char*>(&releaseDate), sizeof(releaseDate));
        return true;
    }
    return false;
}

// Get the size of the ProductRelease record
int ProductRelease::getRecordSize() const {
    return recordSize;
}

// Read the ProductRelease record from a buffer
void ProductRelease::readFromBuffer(const char* buffer) {
    memcpy(productName, buffer, sizeof(productName));
    memcpy(&releaseID, buffer + sizeof(productName), sizeof(releaseID));
    memcpy(&releaseDate, buffer + sizeof(productName) + sizeof(releaseID), sizeof(releaseDate));
}
