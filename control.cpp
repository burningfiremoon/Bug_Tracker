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

using namespace std;

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

    fstream dbFile("testDB.txt", ios::out | ios::app);
    if (!dbFile) {
        cerr << "Error opening database file for writing." << endl;
        return false;
    }

    if (!newUser.writeRecord(dbFile)) {
        cerr << "Error writing user record to database." << endl;
        dbFile.close();
        return false;
    }
    dbFile.close();
    return true;
}

void UpdateUserName(const char* oldName, const char* newName) {
    fstream dbFile("testDB.txt", ios::in | ios::out);
    if (!dbFile) {
        cerr << "Error opening database file." << endl;
        return;
    }

    User user(oldName);
    while (user.readRecord(dbFile)) {
        if (strcmp(user.getRequesterName(), oldName) == 0) {
            user.setRequesterName(newName);
            dbFile.seekp((long)dbFile.tellg() - user.getRecordSize(), ios::beg);
            user.writeRecord(dbFile);
            cout << "User name updated successfully." << endl;
            break;
        }
    }
    dbFile.close();
}

void UpdateUserEmail(const char* name, const char* newEmail) {
    fstream dbFile("testDB.txt", ios::in | ios::out);
    if (!dbFile) {
        cerr << "Error opening database file." << endl;
        return;
    }

    User user(name);
    while (user.readRecord(dbFile)) {
        if (strcmp(user.getRequesterName(), name) == 0) {
            user.setEmail(newEmail);
            dbFile.seekp((long)dbFile.tellg() - user.getRecordSize(), ios::beg);
            user.writeRecord(dbFile);
            cout << "User email updated successfully." << endl;
            break;
        }
    }
    dbFile.close();
}

void UpdateUserPhoneNumber(const char* name, const char* newPhoneNumber) {
    fstream dbFile("testDB.txt", ios::in | ios::out);
    if (!dbFile) {
        cerr << "Error opening database file." << endl;
        return;
    }

    User user(name);
    while (user.readRecord(dbFile)) {
        if (strcmp(user.getRequesterName(), name) == 0) {
            user.setPhone(newPhoneNumber);
            dbFile.seekp((long)dbFile.tellg() - user.getRecordSize(), ios::beg);
            user.writeRecord(dbFile);
            cout << "User phone number updated successfully." << endl;
            break;
        }
    }
    dbFile.close();
}

bool CheckUserExists(const char* name) {
    fstream dbFile("testDB.txt", ios::in);
    if (!dbFile) {
        cerr << "Error opening database file." << endl;
        return false;
    }

    User user(name);
    while (user.readRecord(dbFile)) {
        if (strcmp(user.getRequesterName(), name) == 0) {
            dbFile.close();
            return true;
        }
    }
    dbFile.close();
    return false;
}

void PrintUserInfo(const char* Name) {
    if (CheckUserExists(Name)) {
        fstream dbFile("testDB.txt", ios::in);
        if (!dbFile) {
            cerr << "Error opening database file." << endl;
            return;
        }

        User user(Name);
        while (user.readRecord(dbFile)) {
            if (strcmp(user.getRequesterName(), Name) == 0) {
                cout << user << endl;
                break;
            }
        }
        dbFile.close();
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

    fstream dbFile("ChangeItems.txt", ios::out | ios::app);
    if (!dbFile) {
        cerr << "Error opening ChangeItems file for writing." << endl;
        return -1;
    }

    if (!newItem.writeRecord(dbFile)) {
        cerr << "Error writing change item to database." << endl;
        dbFile.close();
        return -1;
    }
    dbFile.close();
    return newItem.getID(); // Return generated ID
}

void UpdateChangeItemStatus(const char* changeID, const char* status) {
    ChangeItem::updStatus(changeID, status);
}

bool CheckChangeItemExists(const char* changeID) {
    fstream dbFile("ChangeItems.txt", ios::in);
    if (!dbFile) {
        cerr << "Error opening ChangeItems file." << endl;
        return false;
    }

    ChangeItem item;
    while (item.readRecord(dbFile)) {
        if (strcmp(item.getChangeID(), changeID) == 0) {
            dbFile.close();
            return true;
        }
    }
    dbFile.close();
    return false;
}

void ViewChangeItem(int changeID) {
    fstream dbFile("ChangeItems.txt", ios::in);
    if (!dbFile) {
        cerr << "Error opening ChangeItems file." << endl;
        return;
    }

    ChangeItem item;
    while (item.readRecord(dbFile)) {
        if (item.getID() == changeID) {
            PrintChangeItem(item);
            break;
        }
    }
    dbFile.close();
}

void UpdateChangeItemReleaseDate(int changeID, Date date) {
    fstream dbFile("ChangeItems.txt", ios::in | ios::out);
    if (!dbFile) {
        cerr << "Error opening ChangeItems file." << endl;
        return;
    }

    ChangeItem item;
    while (item.readRecord(dbFile)) {
        if (item.getID() == changeID) {
            item.setDateFirstReported(date);
            dbFile.seekp((long)dbFile.tellg() - item.getRecordSize(), ios::beg);
            item.writeRecord(dbFile);
            cout << "Change item release date updated successfully." << endl;
            break;
        }
    }
    dbFile.close();
}

void UpdateChangeItemDescription(int changeID, const char* description) {
    fstream dbFile("ChangeItems.txt", ios::in | ios::out);
    if (!dbFile) {
        cerr << "Error opening ChangeItems file." << endl;
        return;
    }

    ChangeItem item;
    while (item.readRecord(dbFile)) {
        if (item.getID() == changeID) {
            item.setChangeDescription(description);
            dbFile.seekp((long)dbFile.tellg() - item.getRecordSize(), ios::beg);
            item.writeRecord(dbFile);
            cout << "Change item description updated successfully." << endl;
            break;
        }
    }
    dbFile.close();
}

// Change Request Management
bool Init_ChangeRequest(const char* Name, const char* Product, const char* Version, const char* Description, int Priority) {
    ChangeRequest newRequest(Name);
    newRequest.setRequesterName(Name);
    newRequest.setDescription(Description);
    newRequest.setPriority(Priority);
    newRequest.setDateFirstReported({2024, 7, 30}); // Example date

    fstream dbFile("ChangeRequests.txt", ios::out | ios::app);
    if (!dbFile) {
        cerr << "Error opening ChangeRequests file for writing." << endl;
        return false;
    }

    if (!newRequest.writeRecord(dbFile)) {
        cerr << "Error writing change request to database." << endl;
        dbFile.close();
        return false;
    }
    dbFile.close();
    return true;
}

void ShowChangeItems(const char* Product) {
    fstream dbFile("ChangeItems.txt", ios::in);
    if (!dbFile) {
        cerr << "Error opening ChangeItems file." << endl;
        return;
    }

    ChangeItem item;
    while (item.readRecord(dbFile)) {
        if (strcmp(item.getProductName(), Product) == 0) {
            PrintChangeItem(item);
        }
    }
    dbFile.close();
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

    fstream dbFile("ProductReleases.txt", ios::out | ios::app);
    if (!dbFile) {
        cerr << "Error opening ProductReleases file for writing." << endl;
        return false;
    }

    if (!newRelease.writeRecord(dbFile)) {
        cerr << "Error writing product release to database." << endl;
        dbFile.close();
        return false;
    }
    dbFile.close();
    return true;
}

bool CheckProductReleaseExists(const char* Product) {
    fstream dbFile("ProductReleases.txt", ios::in);
    if (!dbFile) {
        cerr << "Error opening ProductReleases file." << endl;
        return false;
    }

    ProductRelease release;
    while (release.readRecord(dbFile)) {
        if (strcmp(release.getProductName(), Product) == 0) {
            dbFile.close();
            return true;
        }
    }
    dbFile.close();
    return false;
}

// Product Management
bool CheckProductExists(const char* Product) {
    return CheckProductReleaseExists(Product);
}

void PrintOpenBugs(const char* Product, Date start, Date end) {
    fstream dbFile("ChangeItems.txt", ios::in);
    if (!dbFile) {
        cerr << "Error opening ChangeItems file." << endl;
        return;
    }

    ChangeItem item;
    while (item.readRecord(dbFile)) {
        Date date = item.getDateFirstReported();
        if (strcmp(item.getProductName(), Product) == 0 &&
            date.y >= start.y && date.y <= end.y &&
            date.m >= start.m && date.m <= end.m &&
            date.d >= start.d && date.d <= end.d &&
            strcmp(item.getStatus(), "Closed") != 0) {
            PrintChangeItem(item);
        }
    }
    dbFile.close();
}

// Backup Operation
bool BackUpDatabase(const std::string& outputFile) {

    DatabaseRecord::backupDatabase(outputFile);
    return true;
}
