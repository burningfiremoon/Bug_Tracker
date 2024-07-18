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
#include "ProductRelease.h"
#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;

const int ProductRelease::recordSize = sizeof(productName) + sizeof(releaseID) + sizeof(releaseDate);

ProductRelease::ProductRelease() {
    memset(productName, 0, sizeof(productName));
    memset(releaseID, 0, sizeof(releaseID));
    memset(&releaseDate, 0, sizeof(releaseDate));
}

ProductRelease::ProductRelease(const char* name, const char* releaseID, Date date) {
    strncpy(this->productName, name, sizeof(this->productName) - 1);
    this->productName[10] = '\0'; // Ensure null termination
    strncpy(this->releaseID, releaseID, sizeof(this->releaseID) - 1);
    this->releaseID[8] = '\0'; // Ensure null termination
    this->releaseDate = date;
}

ProductRelease::~ProductRelease() {}

void ProductRelease::setProductName(const char* name) {
    strncpy(this->productName, name, sizeof(this->productName) - 1);
    this->productName[10] = '\0'; // Ensure null termination
}

const char* ProductRelease::getProductName() const {
    return productName;
}

void ProductRelease::setReleaseID(const char* releaseID) {
    strncpy(this->releaseID, releaseID, sizeof(this->releaseID) - 1);
    this->releaseID[8] = '\0'; // Ensure null termination
}

const char* ProductRelease::getReleaseID() const {
    return releaseID;
}

void ProductRelease::setReleaseDate(Date date) {
    this->releaseDate = date;
}

Date ProductRelease::getReleaseDate() const {
    return releaseDate;
}

bool ProductRelease::writeRecord(fstream &dbFile) const {
    dbFile.seekp(0, ios::end);
    dbFile.write(productName, sizeof(productName));
    dbFile.write(releaseID, sizeof(releaseID));
    dbFile.write(reinterpret_cast<const char*>(&releaseDate), sizeof(releaseDate));
    dbFile.flush();
    return true;
}

bool ProductRelease::readRecord(fstream &dbFile) {
    char tempName[11];
    char tempID[9];
    Date tempDate;

    if (dbFile.read(tempName, sizeof(tempName))) {
        dbFile.read(tempID, sizeof(tempID));
        dbFile.read(reinterpret_cast<char*>(&tempDate), sizeof(tempDate));

        setProductName(tempName);
        setReleaseID(tempID);
        setReleaseDate(tempDate);
        return true;
    }
    return false;
}

int ProductRelease::getRecordSize() const {
    return sizeof(productName) + sizeof(releaseID) + sizeof(releaseDate);
}

void ProductRelease::readFromBuffer(const char* buffer) {
    memcpy(productName, buffer, sizeof(productName));
    memcpy(releaseID, buffer + sizeof(productName), sizeof(releaseID));
    memcpy(&releaseDate, buffer + sizeof(productName) + sizeof(releaseID), sizeof(releaseDate));
}

bool ProductRelease::addRelease(const ProductRelease& release) {
    dbFile.seekp(0, ios::end);
    dbFile.write(release.productName, sizeof(release.productName));
    dbFile.write(release.releaseID, sizeof(release.releaseID));
    dbFile.write(reinterpret_cast<const char*>(&release.releaseDate), sizeof(release.releaseDate));
    dbFile.flush();
    return true;
}

bool ProductRelease::addProduct(int id, const char* name) {
    // Implementation of adding a product
    return false;
}

bool ProductRelease::showProduct(int id) {
    // Implementation of showing a product
    return false;
}

bool ProductRelease::showRelease(int id) {
    // Implementation of showing a release
    return false;
}
