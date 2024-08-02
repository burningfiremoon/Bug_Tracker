// Include necessary headers
#include "control.h"
#include "DatabaseRecord.h"
#include "ChangeItem.h"
#include "ChangeRequest.h"
#include "User.h"
#include "ProductRelease.h"
#include "StatusConstants.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

// Function to generate a unique Change ID
int generateUniqueChangeID() {
    srand(static_cast<unsigned int>(time(nullptr)));
    return rand() % 1000000; // Generates a random number between 0 and 999999
}

// Function to print a change item
void PrintChangeItem(const ChangeItem& item) {
    cout << "Change ID: " << item.getChangeID() << endl;
    cout << "Product Name: " << item.getProductName() << endl;
    cout << "Change Description: " << item.getChangeDescription() << endl;
    cout << "Status: " << item.getStatus() << endl;
    cout << "Priority: " << item.getPriority() << endl;
    cout << "Release ID: " << item.getReleaseID().id << endl;
    cout << "Date First Reported: " << item.getDateFirstReported().y << "-"
         << item.getDateFirstReported().m << "-"
         << item.getDateFirstReported().d << endl;
}

// User Management
bool Init_User(const char* name, const char* phone, const char* email) {
    User newUser(name);
    newUser.setPhone(phone);
    newUser.setEmail(email);

    fstream& dbFileTemp = DatabaseRecord::getFile();

    if (!newUser.writeRecord(dbFileTemp)) {
        cerr << "Error writing user record to database." << endl;
        return false;
    }

    return true;
}

void UpdateUserName(const char* oldName, const char* newName) {

    fstream& dbFileTemp = DatabaseRecord::getFile();

    User user(oldName);
    while (user.findUser(dbFileTemp, oldName)) {
        if (strcmp(user.getRequesterName(), oldName) == 0) {
            user.setRequesterName(newName);
            dbFileTemp.seekp((long)dbFileTemp.tellg() - user.getRecordSize(), ios::beg);
            user.writeRecord(dbFileTemp);
            cout << "User name updated successfully." << endl;
            break;
        }
    }
}

void UpdateUserEmail(const char* name, const char* newEmail) {
    fstream& dbFileTemp = DatabaseRecord::getFile();

    User user(name);
    while (user.readRecord(dbFileTemp)) {
        if (strcmp(user.getRequesterName(), name) == 0) {
            user.setEmail(newEmail);
            dbFileTemp.seekp((long)dbFileTemp.tellg() - user.getRecordSize(), ios::beg);
            user.writeRecord(dbFileTemp);
            cout << "User email updated successfully." << endl;
            break;
        }
    }
    
}

void UpdateUserPhoneNumber(const char* name, const char* newPhoneNumber) {
    fstream& dbFileTemp = DatabaseRecord::getFile();

    User user(name);
    while (user.readRecord(dbFileTemp)) {
        if (strcmp(user.getRequesterName(), name) == 0) {
            user.setPhone(newPhoneNumber);
            dbFileTemp.seekp((long)dbFileTemp.tellg() - user.getRecordSize(), ios::beg);
            user.writeRecord(dbFileTemp);
            cout << "User phone number updated successfully." << endl;
            break;
        }
    }
    
}

bool CheckUserExists(const char* name) {
    fstream& dbFileTemp = DatabaseRecord::getFile();

    User user(name);
    
    while (user.readRecord(dbFileTemp)) {
        if (strcmp(user.getRequesterName(), name) == 0) {
            
            return true;
        }
    }
    
    return false;
}

void PrintUserInfo(const char* Name) {
    if (CheckUserExists(Name)) {
        fstream& dbFileTemp = DatabaseRecord::getFile();

        User user(Name);
        while (user.readRecord(dbFileTemp)) {
            if (strcmp(user.getRequesterName(), Name) == 0) {
                cout << user << endl;
                break;
            }
        }
        
    } else {
        cout << "User not found." << endl;
    }
}

void showUserInfo(const char* Name) {
    PrintUserInfo(Name);
}

// Change Item Management
int Init_ChangeItem(const char* product, const char* changeDescription) {
    ChangeItem newItem("");  // Generate a new ID internally
    newItem.setProductName(product);
    newItem.setChangeDescription(changeDescription);

    fstream& dbFileTemp = DatabaseRecord::getFile();

    if (!newItem.writeRecord(dbFileTemp)) {
        cerr << "Error writing change item to database." << endl;
        
        return -1;
    }
    
    return newItem.getID(); // Return generated ID
}

void UpdateChangeItemStatus(const char* changeID, const char* status) {
    ChangeItem::updStatus(changeID, status);
}

bool CheckChangeItemExists(const char* changeID) {
    fstream& dbFileTemp = DatabaseRecord::getFile();
    ChangeItem item;
    while (item.readRecord(dbFileTemp)) {
        if (strcmp(item.getChangeID(), changeID) == 0) {
            
            return true;
        }
    }
    
    return false;
}

void ViewChangeItem(int changeID) {
    fstream& dbFileTemp = DatabaseRecord::getFile();

    ChangeItem item;
    while (item.readRecord(dbFileTemp)) {
        if (item.getID() == changeID) {
            PrintChangeItem(item);
            break;
        }
    }
    
}

void UpdateChangeItemReleaseDate(int changeID, Date date) {
    fstream& dbFileTemp = DatabaseRecord::getFile();

    ChangeItem item;
    while (item.readRecord(dbFileTemp)) {
        if (item.getID() == changeID) {
            item.setDateFirstReported(date);
            dbFileTemp.seekp((long)dbFileTemp.tellg() - item.getRecordSize(), ios::beg);
            item.writeRecord(dbFileTemp);
            cout << "Change item release date updated successfully." << endl;
            break;
        }
    }
    
}

void UpdateChangeItemDescription(int changeID, const char* description) {
    fstream& dbFileTemp = DatabaseRecord::getFile();

    ChangeItem item;
    while (item.readRecord(dbFileTemp)) {
        if (item.getID() == changeID) {
            item.setChangeDescription(description);
            dbFileTemp.seekp((long)dbFileTemp.tellg() - item.getRecordSize(), ios::beg);
            item.writeRecord(dbFileTemp);
            cout << "Change item description updated successfully." << endl;
            break;
        }
    }
    
}

// Change Request Management
bool Init_ChangeRequest(const char* Name, const char* Product, const char* Version, const char* Description, int Priority, int& changeID) {
    changeID = generateUniqueChangeID(); // Generate a unique Change ID
    ChangeRequest newRequest(Name);
    newRequest.setRequesterName(Name);
    newRequest.setDescription(Description);
    newRequest.setPriority(Priority);
    newRequest.setDateFirstReported({2024, 7, 30}); // Example date

    // Convert changeID to string and set it
    char changeIDStr[7];
    snprintf(changeIDStr, sizeof(changeIDStr), "%06d", changeID);
    newRequest.setChangeID(changeIDStr);

    fstream& dbFileTemp = DatabaseRecord::getFile();

    if (!newRequest.writeRecord(dbFileTemp)) {
        cerr << "Error writing change request to database." << endl;
        
        return false;
    }
    
    return true;
}

void ShowChangeItems(const char* Product) {
    fstream& dbFileTemp = DatabaseRecord::getFile();

    ChangeItem item;
    while (item.readRecord(dbFileTemp)) {
        if (strcmp(item.getProductName(), Product) == 0) {
            PrintChangeItem(item);
        }
    }
    
}

void connectChangeRequest(const char* Name, int changeID) {
    cout << "Connecting Change Request by " << Name << " to Change Item ID: " << changeID << endl;
}

// Product Release Management
bool Init_ProductRelease(const char* Product, Date date) {
    ReleaseID releaseID;
    strncpy(releaseID.id, Product, sizeof(releaseID.id) - 1);
    releaseID.id[sizeof(releaseID.id) - 1] = '\0';

    ProductRelease newRelease(Product, releaseID, date);

    fstream& dbFileTemp = DatabaseRecord::getFile();

    if (!newRelease.writeRecord(dbFileTemp)) {
        cerr << "Error writing product release to database." << endl;
        
        return false;
    }
    
    return true;
}

bool CheckProductReleaseExists(const char* Product) {
    fstream& dbFileTemp = DatabaseRecord::getFile();

    ProductRelease release;
    while (release.readRecord(dbFileTemp)) {
        if (strcmp(release.getProductName(), Product) == 0) {
            
            return true;
        }
    }
    
    return false;
}

// Product Management
bool CheckProductExists(const char* Product) {
    return CheckProductReleaseExists(Product);
}

void PrintOpenBugs(const char* Product, Date start, Date end) {
    fstream& dbFileTemp = DatabaseRecord::getFile();

    ChangeItem item;
    while (item.readRecord(dbFileTemp)) {
        Date date = item.getDateFirstReported();
        if (strcmp(item.getProductName(), Product) == 0 &&
            date.y >= start.y && date.y <= end.y &&
            date.m >= start.m && date.m <= end.m &&
            date.d >= start.d && date.d <= end.d &&
            strcmp(item.getStatus(), "Closed") != 0) {
            PrintChangeItem(item);
        }
    }
    
}

// Backup Operation
bool BackUpDatabase(const std::string& outputFile) {
    DatabaseRecord::backupDatabase(outputFile);
    return true;
}
