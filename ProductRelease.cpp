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

//-------------------------------------
// Constructors
//-------------------------------------
/*
    ProductRelease::ProductRelease()
    - Purpose: Default constructor that initializes a ProductRelease object with empty or zero values.
    - Parameters:
        - None
*/
ProductRelease::ProductRelease() {
    memset(productName, 0, sizeof(productName));
    memset(&releaseID, 0, sizeof(releaseID));
    memset(&releaseDate, 0, sizeof(releaseDate));
}

/*
    ProductRelease::ProductRelease(const char* name, ReleaseID id, Date date)
    - Purpose: Parameterized constructor that initializes a ProductRelease object with specified values.
    - Parameters:
        - const char* name (in): The name of the product.
        - ReleaseID id (in): The ID of the release.
        - Date date (in): The date of the release.
*/
ProductRelease::ProductRelease(const char* name, ReleaseID id, Date date) {
    strncpy(productName, name, sizeof(productName) - 1);
    productName[sizeof(productName) - 1] = '\0';
    releaseID = id;
    releaseDate = date;
}

//-------------------------------------
// Setters and Getters
//-------------------------------------
/*
    void ProductRelease::setProductName(const char* name)
    - Purpose: Set the name of the product for the ProductRelease object.
    - Parameters:
        - const char* name (in): The name to set.
*/
void ProductRelease::setProductName(const char* name) {
    strncpy(productName, name, sizeof(productName) - 1);
    productName[sizeof(productName) - 1] = '\0';
}

/*
    const char* ProductRelease::getProductName() const
    - Purpose: Get the name of the product for the ProductRelease object.
    - Returns: const char* (out): The name of the product.
*/
const char* ProductRelease::getProductName() const {
    return productName;
}

/*
    void ProductRelease::setReleaseID(ReleaseID id)
    - Purpose: Set the release ID for the ProductRelease object.
    - Parameters:
        - ReleaseID id (in): The release ID to set.
*/
void ProductRelease::setReleaseID(ReleaseID id) {
    releaseID = id;
}

/*
    ReleaseID ProductRelease::getReleaseID() const
    - Purpose: Get the release ID for the ProductRelease object.
    - Returns: ReleaseID (out): The release ID of the ProductRelease.
*/
ReleaseID ProductRelease::getReleaseID() const {
    return releaseID;
}

/*
    void ProductRelease::setReleaseDate(Date date)
    - Purpose: Set the release date for the ProductRelease object.
    - Parameters:
        - Date date (in): The release date to set.
*/
void ProductRelease::setReleaseDate(Date date) {
    releaseDate = date;
}

/*
    Date ProductRelease::getReleaseDate() const
    - Purpose: Get the release date for the ProductRelease object.
    - Returns: Date (out): The release date of the ProductRelease.
*/
Date ProductRelease::getReleaseDate() const {
    return releaseDate;
}

//-------------------------------------
// File Operations
//-------------------------------------
/*
    bool ProductRelease::writeRecord(fstream &dbFile) const
    - Purpose: Write the ProductRelease record to the given file stream.
    - Parameters:
        - fstream &dbFile (in/out): The file stream to write the record to.
    - Returns: bool (out): True if the record is written successfully, false otherwise.
*/
bool ProductRelease::writeRecord(fstream &dbFile) const {
    dbFile.seekp(0, ios::end);
    dbFile.write(productName, sizeof(productName));
    dbFile.write(reinterpret_cast<const char*>(&releaseID), sizeof(releaseID));
    dbFile.write(reinterpret_cast<const char*>(&releaseDate), sizeof(releaseDate));
    dbFile.flush();
    return true;
}

/*
    bool ProductRelease::readRecord(fstream &dbFile)
    - Purpose: Read a ProductRelease record from the given file stream.
    - Parameters:
        - fstream &dbFile (in/out): The file stream to read the record from.
    - Returns: bool (out): True if the record is read successfully, false otherwise.
*/
bool ProductRelease::readRecord(fstream &dbFile) {
    if (dbFile.read(productName, sizeof(productName))) {
        dbFile.read(reinterpret_cast<char*>(&releaseID), sizeof(releaseID));
        dbFile.read(reinterpret_cast<char*>(&releaseDate), sizeof(releaseDate));
        return true;
    }
    return false;
}

/*
    int ProductRelease::getRecordSize() const
    - Purpose: Get the size of the ProductRelease record.
    - Returns: int (out): The size of the ProductRelease record in bytes.
*/
int ProductRelease::getRecordSize() const {
    return sizeof(productName) + sizeof(releaseID) + sizeof(releaseDate);
}

/*
    void ProductRelease::readFromBuffer(const char* buffer)
    - Purpose: Read the ProductRelease record from a buffer.
    - Parameters:
        - const char* buffer (in): The buffer to read the record from.
*/
void ProductRelease::readFromBuffer(const char* buffer) {
    memcpy(productName, buffer, sizeof(productName));
    memcpy(&releaseID, buffer + sizeof(productName), sizeof(releaseID));
    memcpy(&releaseDate, buffer + sizeof(productName) + sizeof(releaseID), sizeof(releaseDate));
}
