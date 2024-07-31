/*
    Revision History:
    1.0 - 03-05-2024 - Modified by Skyler
    2.0 - 17-07-2024 - Modified by Charles

    control.cpp:
    This source file contains function definitions for handling different scenarios.
    It includes necessary headers and defines functions to handle various use cases.
*/

//-------------------------------------
// List of #includes
#include "control.h"
#include "DatabaseRecord.h"
#include "ChangeItem.h"
#include "ChangeRequest.h"
#include "ProductRelease.h"
#include "User.h"
#include "print.h"
#include "ui.h"

//-------------------------------------
// Function definitions

void StopAccepting() {
    // Implementation to stop accepting user input
}

void StartAccepting() {
    // Implementation to start accepting user input
}

void CloseDatabase() {
    closeDatabase();
}

void OpenDatabase() {
    openDatabase("database.txt");
}

void UpdateUserName(char* Name, char* newName) {
    if (CheckUserExists(Name)) {
        User user(Name);
        user.setRequesterName(newName);
        fstream &dbFile = DatabaseRecord::getFile();
        user.writeRecord(dbFile);
    } else {
        cout << "User not found." << endl;
    }
}

void UpdateUserEmail(char* Name, char* newEmail) {
    if (CheckUserExists(Name)) {
        User user(Name);
        user.setEmail(newEmail);
        fstream &dbFile = DatabaseRecord::getFile();
        user.writeRecord(dbFile);
    } else {
        cout << "User not found." << endl;
    }
}

void UpdateUserPhoneNumber(char* Name, char* newPhoneNumber) {
    if (CheckUserExists(Name)) {
        User user(Name);
        user.setPhone(newPhoneNumber);
        fstream &dbFile = DatabaseRecord::getFile();
        user.writeRecord(dbFile);
    } else {
        cout << "User not found." << endl;
    }
}

void UpdateChangeItemStatus(int changeID, int status) {
    if (CheckChangeItemExists(changeID)) {
        ChangeItem::updStatus(to_string(changeID).c_str(), status);
    } else {
        cout << "Change Item not found." << endl;
    }
}

bool CheckUserExists(char* Name) {
    User user(Name);
    fstream &dbFile = DatabaseRecord::getFile();
    return DatabaseRecord::findRecord(Name, user);
}

bool CheckChangeItemExists(int ChangeID) {
    ChangeItem item(to_string(ChangeID).c_str());
    fstream &dbFile = DatabaseRecord::getFile();
    return DatabaseRecord::findRecord(to_string(ChangeID).c_str(), item);
}

bool CheckProductExists(char* Product) {
    ProductRelease pr;
    fstream &dbFile = DatabaseRecord::getFile();
    return DatabaseRecord::findRecord(Product, pr);
}

bool CheckProductReleaseExists(char* Product) {
    ProductRelease pr;
    fstream &dbFile = DatabaseRecord::getFile();
    return DatabaseRecord::findRecord(Product, pr);
}

void ViewStatusReport(Date start, Date end) {
    fstream &dbFile = DatabaseRecord::getFile();
    ChangeItem item;
    DatabaseRecord::seekToBeginning();
    while (item.readRecord(dbFile)) {
        Date date = item.getDateFirstReported();
        if (date.y >= start.y && date.y <= end.y && 
            date.m >= start.m && date.m <= end.m && 
            date.d >= start.d && date.d <= end.d) {
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
    }
}

void showUserInfo(char* Name) {
    if (CheckUserExists(Name)) {
        User user(Name);
        fstream &dbFile = DatabaseRecord::getFile();
        if (user.readRecord(dbFile)) {
            cout << "Requester Name: " << user.getRequesterName() << endl;
            cout << "Phone: " << user.getPhone() << endl;
            cout << "Email: " << user.getEmail() << endl;
            cout << "Address: " << user.getAddress() << endl;
        }
    } else {
        cout << "User not found." << endl;
    }
}

void ShowChangeItems(char* Product) {
    fstream &dbFile = DatabaseRecord::getFile();
    ChangeItem item;
    DatabaseRecord::seekToBeginning();
    while (item.readRecord(dbFile)) {
        if (strcmp(item.getProductName(), Product) == 0) {
            cout << "Change ID: " << item.getChangeID() << endl;
            cout << "Change Description: " << item.getChangeDescription() << endl;
            cout << "Status: " << item.getStatus() << endl;
            cout << "Priority: " << item.getPriority() << endl;
            cout << "Release ID: " << item.getReleaseID().id << endl;
            cout << "Date First Reported: " << item.getDateFirstReported().y << "-"
                 << item.getDateFirstReported().m << "-"
                 << item.getDateFirstReported().d << endl;
        }
    }
}

void connectChangeRequest(char* Name, int changeID) {
    // Assuming connecting a change request means associating a user with a change item
    if (CheckUserExists(Name) && CheckChangeItemExists(changeID)) {
        User user(Name);
        ChangeRequest cr(to_string(changeID).c_str(), Name);
        fstream &dbFile = DatabaseRecord::getFile();
        cr.writeRecord(dbFile);
    } else {
        cout << "User or Change Item not found." << endl;
    }
}

void ViewChangeItem(int changeID) {
    if (CheckChangeItemExists(changeID)) {
        ChangeItem item(to_string(changeID).c_str());
        fstream &dbFile = DatabaseRecord::getFile();
        if (item.readRecord(dbFile)) {
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
    } else {
        cout << "Change Item not found." << endl;
    }
}

void PrintOpenBugs(char* Product, Date start, Date end) {
    fstream &dbFile = DatabaseRecord::getFile();
    ChangeItem item;
    DatabaseRecord::seekToBeginning();
    while (item.readRecord(dbFile)) {
        if (strcmp(item.getProductName(), Product) == 0) {
            Date date = item.getDateFirstReported();
            if (date.y >= start.y && date.y <= end.y && 
                date.m >= start.m && date.m <= end.m && 
                date.d >= start.d && date.d <= end.d) {
                printChangeItem(item);
            }
        }
    }
}

bool Init_ProductRelease(char* Product, Date date) {
    ProductRelease pr(Product, {0}, date);
    fstream &dbFile = DatabaseRecord::getFile();
    return pr.writeRecord(dbFile);
}

int Init_ChangeItem(char* Product, char* ChangeDescription) {
    static int changeIDCounter = 1; // Static counter to generate unique change IDs
    int changeID = changeIDCounter++;
    ChangeItem item(to_string(changeID).c_str());
    item.setProductName(Product);
    item.setChangeDescription(ChangeDescription);
    fstream &dbFile = DatabaseRecord::getFile();
    item.writeRecord(dbFile);
    return changeID;
}

bool Init_User(char* Name, char* PhoneNumber, char* Email) {
    User user(Name);
    user.setPhone(PhoneNumber);
    user.setEmail(Email);
    fstream &dbFile = DatabaseRecord::getFile();
    return user.writeRecord(dbFile);
}

bool Init_ChangeRequest(char* Name, char* Product, char* ReleaseID, char* Description, int Priority) {
    ChangeRequest cr(Name, Product);
    cr.setDescription(Description);
    cr.setPriority(Priority);
    struct ReleaseID rid;
    strncpy(rid.id, ReleaseID, sizeof(rid.id));
    cr.setReleaseID(rid);
    fstream &dbFile = DatabaseRecord::getFile();
    return cr.writeRecord(dbFile);
}

bool Init_Product(char* Product) {
    ProductRelease pr;
    strncpy(pr.getProductName(), Product, sizeof(pr.getProductName()));
    fstream &dbFile = DatabaseRecord::getFile();
    return pr.writeRecord(dbFile);
}

void PrintChangeItem(int ChangeID) {
    if (CheckChangeItemExists(ChangeID)) {
        ChangeItem item(to_string(ChangeID).c_str());
        fstream &dbFile = DatabaseRecord::getFile();
        if (item.readRecord(dbFile)) {
            printChangeItem(item);
        }
    } else {
        cout << "Change Item not found." << endl;
    }
}

void PrintUserInfo(char* Name) {
    if (CheckUserExists(Name)) {
        User user(Name);
        fstream &dbFile = DatabaseRecord::getFile();
        if (user.readRecord(dbFile)) {
            printUserInfo(user);
        }
    } else {
        cout << "User not found." << endl;
    }
}

void UpdateChangeItemReleaseDate(int changeID, Date date) {
    if (CheckChangeItemExists(changeID)) {
        ChangeItem item(to_string(changeID).c_str());
        item.setDateFirstReported(date);
        fstream &dbFile = DatabaseRecord::getFile();
        item.writeRecord(dbFile);
    } else {
        cout << "Change Item not found." << endl;
    }
}

void UpdateChangeItemDescription(int changeID, char* Description) {
    if (CheckChangeItemExists(changeID)) {
        ChangeItem item(to_string(changeID).c_str());
        item.setChangeDescription(Description);
        fstream &dbFile = DatabaseRecord::getFile();
        item.writeRecord(dbFile);
    } else {
        cout << "Change Item not found." << endl;
    }
}

bool BackUpChangeRequest() {
    return backupFile("ChangeRequest.txt");
}

bool BackUpUsers() {
    return backupFile("Users.txt");
}

bool BackUpChangeItems() {
    return backupFile("ChangeItems.txt");
}

bool BackUpProductReleases() {
    return backupFile("ProductReleases.txt");
}

bool BackUpProducts() {
    return backupFile("Products.txt");
}

bool BackUpEntireDatabase() {
    bool success = true;
    success &= BackUpChangeRequest();
    success &= BackUpUsers();
    success &= BackUpChangeItems();
    success &= BackUpProductReleases();
    success &= BackUpProducts();
    return success;
}