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

/*
    void StopAccepting()
    - Purpose: Stops accepting user input.
*/
void StopAccepting() {
    // Implementation to stop accepting user input
}

/*
    void StartAccepting()
    - Purpose: Starts accepting user input.
*/
void StartAccepting() {
    // Implementation to start accepting user input
}

/*
    void CloseDatabase()
    - Purpose: Closes access to the database.
*/
void CloseDatabase() {
    closeDatabase();
}

/*
    void OpenDatabase(const string& fileName)
    - Purpose: Opens access to the database with the specified file name.
    - Parameters:
        - const string& fileName (in): The name of the database file to open.
*/
void OpenDatabase(const string& fileName) {
    openDatabase(fileName);
}

/*
    void UpdateUserName(char* Name, char* newName)
    - Purpose: Updates the user's name from the old name to the new name.
    - Parameters:
        - char* Name (in): The current name of the user.
        - char* newName (in): The new name to set for the user.
*/
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

/*
    void UpdateUserEmail(char* Name, char* newEmail)
    - Purpose: Updates the user's email address.
    - Parameters:
        - char* Name (in): The current name of the user.
        - char* newEmail (in): The new email address to set.
*/
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

/*
    void UpdateUserPhoneNumber(char* Name, char* newPhoneNumber)
    - Purpose: Updates the user's phone number.
    - Parameters:
        - char* Name (in): The current name of the user.
        - char* newPhoneNumber (in): The new phone number to set.
*/
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

/*
    void UpdateChangeItemStatus(int changeID, int status)
    - Purpose: Updates the status of a change item with the specified ID.
    - Parameters:
        - int changeID (in): The ID of the change item to update.
        - int status (in): The new status to set.
*/
void UpdateChangeItemStatus(int changeID, int status) {
    if (CheckChangeItemExists(changeID)) {
        ChangeItem::updStatus(to_string(changeID).c_str(), status);
    } else {
        cout << "Change Item not found." << endl;
    }
}

/*
    bool CheckUserExists(char* Name)
    - Purpose: Checks if a user with the specified name exists in the database.
    - Parameters:
        - char* Name (in): The name of the user to check.
    - Returns: bool (out): True if the user exists, false otherwise.
*/
bool CheckUserExists(char* Name) {
    User user(Name);
    fstream &dbFile = DatabaseRecord::getFile();
    return DatabaseRecord::findRecord(Name, user);
}

/*
    bool CheckChangeItemExists(int ChangeID)
    - Purpose: Checks if a change item with the specified ID exists in the database.
    - Parameters:
        - int ChangeID (in): The ID of the change item to check.
    - Returns: bool (out): True if the change item exists, false otherwise.
*/
bool CheckChangeItemExists(int ChangeID) {
    ChangeItem item(to_string(ChangeID).c_str());
    fstream &dbFile = DatabaseRecord::getFile();
    return DatabaseRecord::findRecord(to_string(ChangeID).c_str(), item);
}

/*
    bool CheckProductExists(char* Product)
    - Purpose: Checks if a product exists in the database.
    - Parameters:
        - char* Product (in): The name of the product to check.
    - Returns: bool (out): True if the product exists, false otherwise.
*/
bool CheckProductExists(char* Product) {
    ProductRelease pr;
    fstream &dbFile = DatabaseRecord::getFile();
    return DatabaseRecord::findRecord(Product, pr);
}

/*
    bool CheckProductReleaseExists(char* Product)
    - Purpose: Checks if a product release exists in the database.
    - Parameters:
        - char* Product (in): The name of the product release to check.
    - Returns: bool (out): True if the product release exists, false otherwise.
*/
bool CheckProductReleaseExists(char* Product) {
    ProductRelease pr;
    fstream &dbFile = DatabaseRecord::getFile();
    return DatabaseRecord::findRecord(Product, pr);
}

/*
    void ViewStatusReport(Date start, Date end)
    - Purpose: Displays all open change items within a specified date range.
    - Parameters:
        - Date start (in): The start date of the range.
        - Date end (in): The end date of the range.
*/
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

/*
    void showUserInfo(char* Name)
    - Purpose: Displays user information for the specified user name.
    - Parameters:
        - char* Name (in): The name of the user to display.
*/
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

/*
    void ShowChangeItems(char* Product)
    - Purpose: Displays all change items for the specified product.
    - Parameters:
        - char* Product (in): The name of the product to display change items for.
*/
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

/*
    void connectChangeRequest(char* Name, int changeID)
    - Purpose: Connects a change request to a change item.
    - Parameters:
        - char* Name (in): The name of the user requesting the change.
        - int changeID (in): The ID of the change item to connect.
*/
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

/*
    void ViewChangeItem(int changeID)
    - Purpose: Displays the information of a specific change item.
    - Parameters:
        - int changeID (in): The ID of the change item to view.
*/
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

/*
    void PrintOpenBugs(char* Product, Date start, Date end)
    - Purpose: Sends all open change items of a product between the specified date range to the printer.
    - Parameters:
        - char* Product (in): The name of the product.
        - Date start (in): The start date of the range.
        - Date end (in): The end date of the range.
*/
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

/*
    bool Init_ProductRelease(char* Product, Date date)
    - Purpose: Initializes a new product release object.
    - Parameters:
        - char* Product (in): The name of the product.
        - Date date (in): The release date.
    - Returns: bool (out): True if initialization was successful, false otherwise.
*/
bool Init_ProductRelease(char* Product, Date date) {
    ProductRelease pr(Product, {0}, date);
    fstream &dbFile = DatabaseRecord::getFile();
    return pr.writeRecord(dbFile);
}

/*
    int Init_ChangeItem(char* Product, char* ChangeDescription)
    - Purpose: Initializes a new change item object.
    - Parameters:
        - char* Product (in): The name of the product.
        - char* ChangeDescription (in): The description of the change.
    - Returns: int (out): The unique ID of the newly created change item.
*/
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

/*
    bool Init_User(char* Name, char* PhoneNumber, char* Email)
    - Purpose: Initializes a new user object.
    - Parameters:
        - char* Name (in): The name of the user.
        - char* PhoneNumber (in): The phone number of the user.
        - char* Email (in): The email address of the user.
    - Returns: bool (out): True if initialization was successful, false otherwise.
*/
bool Init_User(char* Name, char* PhoneNumber, char* Email) {
    User user(Name);
    user.setPhone(PhoneNumber);
    user.setEmail(Email);
    fstream &dbFile = DatabaseRecord::getFile();
    return user.writeRecord(dbFile);
}

/*
    bool Init_ChangeRequest(char* Name, char* Product, char* ReleaseID, char* Description, int Priority)
    - Purpose: Initializes a new change request object.
    - Parameters:
        - char* Name (in): The name of the requester.
        - char* Product (in): The name of the product.
        - char* ReleaseID (in): The release ID.
        - char* Description (in): The description of the change.
        - int Priority (in): The priority of the change request.
    - Returns: bool (out): True if initialization was successful, false otherwise.
*/
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

/*
    bool Init_Product(char* Product)
    - Purpose: Initializes a new product.
    - Parameters:
        - char* Product (in): The name of the product.
    - Returns: bool (out): True if initialization was successful, false otherwise.
*/
bool Init_Product(char* Product) {
    ProductRelease pr;
    strncpy(pr.getProductName(), Product, sizeof(pr.getProductName()));
    fstream &dbFile = DatabaseRecord::getFile();
    return pr.writeRecord(dbFile);
}

/*
    void PrintChangeItem(int ChangeID)
    - Purpose: Sends information for a specific change item to the printer.
    - Parameters:
        - int ChangeID (in): The ID of the change item to print.
*/
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

/*
    void PrintUserInfo(char* Name)
    - Purpose: Sends information for a specific user to the printer.
    - Parameters:
        - char* Name (in): The name of the user to print.
*/
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

/*
    void UpdateChangeItemReleaseDate(int changeID, Date date)
    - Purpose: Updates the release date of a change item.
    - Parameters:
        - int changeID (in): The ID of the change item.
        - Date date (in): The new release date.
*/
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

/*
    void UpdateChangeItemDescription(int changeID, char* Description)
    - Purpose: Updates the description of a change item.
    - Parameters:
        - int changeID (in): The ID of the change item.
        - char* Description (in): The new description to set.
*/
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

/*
    bool BackUpChangeRequest()
    - Purpose: Backs up the change request file in the database.
    - Returns: bool (out): True if the backup was successful, false otherwise.
*/
bool BackUpChangeRequest() {
    return backupFile("ChangeRequest.txt");
}

/*
    bool BackUpUsers()
    - Purpose: Backs up the users file in the database.
    - Returns: bool (out): True if the backup was successful, false otherwise.
*/
bool BackUpUsers() {
    return backupFile("Users.txt");
}

/*
    bool BackUpChangeItems()
    - Purpose: Backs up the change items file in the database.
    - Returns: bool (out): True if the backup was successful, false otherwise.
*/
bool BackUpChangeItems() {
    return backupFile("ChangeItems.txt");
}

/*
    bool BackUpProductReleases()
    - Purpose: Backs up the product releases file in the database.
    - Returns: bool (out): True if the backup was successful, false otherwise.
*/
bool BackUpProductReleases() {
    return backupFile("ProductReleases.txt");
}

/*
    bool BackUpProducts()
    - Purpose: Backs up the products file in the database.
    - Returns: bool (out): True if the backup was successful, false otherwise.
*/
bool BackUpProducts() {
    return backupFile("Products.txt");
}

/*
    bool BackUpEntireDatabase()
    - Purpose: Backs up the entire database.
    - Returns: bool (out): True if the backup was successful, false otherwise.
*/
bool BackUpEntireDatabase() {
    bool success = true;
    success &= BackUpChangeRequest();
    success &= BackUpUsers();
    success &= BackUpChangeItems();
    success &= BackUpProductReleases();
    success &= BackUpProducts();
    return success;
}
