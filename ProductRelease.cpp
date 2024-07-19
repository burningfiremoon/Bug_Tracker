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

ProductRelease::ProductRelease() {
    memset(productName, 0, sizeof(productName));
    memset(&releaseID, 0, sizeof(releaseID));
    memset(&releaseDate, 0, sizeof(releaseDate));
}

ProductRelease::ProductRelease(const char* name, ReleaseID id, Date date) {
    strncpy(productName, name, sizeof(productName) - 1);
    productName[sizeof(productName) - 1] = '\0';
    releaseID = id;
    releaseDate = date;
}

void ProductRelease::setProductName(const char* name) {
    strncpy(productName, name, sizeof(productName) - 1);
    productName[sizeof(productName) - 1] = '\0';
}

const char* ProductRelease::getProductName() const {
    return productName;
}

void ProductRelease::setReleaseID(ReleaseID id) {
    releaseID = id;
}

ReleaseID ProductRelease::getReleaseID() const {
    return releaseID;
}

void ProductRelease::setReleaseDate(Date date) {
    releaseDate = date;
}

Date ProductRelease::getReleaseDate() const {
    return releaseDate;
}

bool ProductRelease::writeRecord(fstream &dbFile) const {
    dbFile.seekp(0, ios::end);
    dbFile.write(productName, sizeof(productName));
    dbFile.write(reinterpret_cast<const char*>(&releaseID), sizeof(releaseID));
    dbFile.write(reinterpret_cast<const char*>(&releaseDate), sizeof(releaseDate));
    dbFile.flush();
    return true;
}

bool ProductRelease::readRecord(fstream &dbFile) {
    if (dbFile.read(productName, sizeof(productName))) {
        dbFile.read(reinterpret_cast<char*>(&releaseID), sizeof(releaseID));
        dbFile.read(reinterpret_cast<char*>(&releaseDate), sizeof(releaseDate));
        return true;
    }
    return false;
}

int ProductRelease::getRecordSize() const {
    return sizeof(productName) + sizeof(releaseID) + sizeof(releaseDate);
}

void ProductRelease::readFromBuffer(const char* buffer) {
    memcpy(productName, buffer, sizeof(productName));
    memcpy(&releaseID, buffer + sizeof(productName), sizeof(releaseID));
    memcpy(&releaseDate, buffer + sizeof(productName) + sizeof(releaseID), sizeof(releaseDate));
}
