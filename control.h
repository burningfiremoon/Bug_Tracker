/*
    Revision History:
    1.0 - 03-05-2024 [Date] - Modified by Skyler
    1.0 - 12-07-2024 [Date] - Modified by Charles

    control.h:
    This header file contains function declarations for handling different scenarios.
    It includes necessary headers and defines functions to handle various use cases.
*/
//-------------------------------------
#ifndef CONTROL_H
#define CONTROL_H

//-------------------------------------
// List of #includes
#include "database.h"
#include "print.h"
#include "ui.h"

//-------------------------------------
// Function prototypes

//functions taking care of different scenarios

// -----
// StopAccepting
// Tells main To stop accepting User input
void StopAccepting();

// -----
// StartAccepting
// Tells main To start accepting User input
void StartAccepting();

// -----
// CloseDatabase
// Closes access to database
void CloseDatabase();

// -----
// OpenDatabase
// opens access to database
void OpenDatabase();

// -----
// UpdateUserName
// Updates User's name from Name to newName
// char[31] Name (in)
// char[31] newName (in)
void UpdateUserName(char Name[31], char newName[31]);

// -----
// UpdateUserEmail
// Updates User's Email to newEmail
// char[31] Name (in)
// char[25] newEmail (in)
void UpdateUserEmail(char Name[31], char newEmail[25]);

// -----
// UpdateUserPhoneNumber
// Updates User's phone number to newPhoneNumber
// char[31] Name (in)
// char[18] newPhoneNumber (in)
void UpdateUserPhoneNumber(char Name[31], char newPhoneNumber[18]);

// -----
// UpdateChangeItemStatus
// Updates the status of change item with the matching ChangeID with status
// int changeID (in)
// int status (in)
void UpdateChangeItemStatus(int changeID, int status);

// -----
// CheckUserExists
// Checks if User object exists in database and returns a bool value indicating existence
// char[31] Name (in)
// bool value if object exists (out)
bool CheckUserExists(char Name[31]);

// -----
// CheckChangeItemExists
// Checks if Change Item object exists in database and returns a bool value indicating existence
// int ChangeID (in)
// bool value if object exists (out)
bool CheckChangeItemExists(int ChangeID);

// -----
// CheckProductExists
// Checks if Product object exists in database and returns a bool value indicating existence
// char[11] Product (in)
// bool value if object exists (out)
bool CheckProductExists(char Product[11]);

// -----
// CheckProductReleaseExists
// Checks if Product Release object exists in database and returns a bool value indicating existence
// char[11] Productname (in)
// bool value if object exists (out)
bool CheckProductReleaseExists(char Product[11]);

// -----
// ViewStatusReport
// Displays all open change items between start and end date range onto terminal
// Date start (in)
// Date end (in)
// Open Change Items between date range (out)
void ViewStatusReport(Date start, Date end);

// -----
// showUserInfo
// Displays User information with matching Name onto terminal
// char[31] Name (in)
void showUserInfo(char Name[31]);

// -----
// ShowChangeItems
// Displays all Change Items for Product onto terminal
// char[11] ProductID (in)
void ShowChangeItems(char Product[11]);

// -----
// connectChangeRequest
// Connects Change Request to Change Item
// char[31] Name (in)
// int changeID (in)
void connectChangeRequest(char Name[31], int changeID);

// -----
// ViewChangeItem
// Displays Change Item information onto terminal
// int changeID (in)
void ViewChangeItem(int changeID){
    // Check existence
    CheckChangeItemExists(changeID);
}

// -----
// PrintOpenBugs
// Sends all open change items of product between start and end dates to printer
// char[11] Product (in)
// Date start (in)
// Date end (in)
void PrintOpenBugs(char Product[11], Date start, Date end);

// -----
// Init_ProductRelease
// Initializes new Product Release object
// char[11] Product (in)
// Date date (in)
// bool value if initialization was successful (out)
bool Init_ProductRelease(char Product[11], Date date);

// -----
// Init_ChangeItem
// Initializes new Change Item object
// char[11] Product (in)
// char[31] ChangeDescription (in)
// returns new unique (int) changeID (out)
int Init_ChangeItem(char Product[11], char ChangeDescription[31]);

// -----
// Init_User
// Initializes new User object
// char[31] Name (in)
// char[18] PhoneNumber (in)
// char[25] Email (in)
// bool value if initialization was successful (out)
bool Init_User(char Name[31], char PhoneNumber[18], char Email[25]);

// -----
// Init_ChangeRequest
// Initializes new Change Request object
// char[31] Name (in)
// char[11] Product (in)
// char[9] ReleaseID (in)
// char[31] Description (in)
// int Priority (in)
// bool value if initialization was successful (out)
bool Init_ChangeRequest(char Name[31], char Product[11], char ReleaseID[9], char Description[31], int Priority);

// -----
// Init_Product
// Initializes new Product
// char[11] Product (in)
// bool value if initialization was successful (out)
bool Init_Product(char Product[11]);

// -----
// PrintChangeItem
// Sends information for a specific change item to printer
// int ChangeID (in)
void PrintChangeItem(int ChangeID);

// -----
// PrintUserInfo
// Sends information for a specific user to printer
// char[31] Name (in)
void PrintUserInfo(char Name[31]);

// -----
// UpdateChangeItemReleaseDate
// Updates changeID's release date to date
// int changeID (in)
// Date date (in)
void UpdateChangeItemReleaseDate(int changeID, Date date);

// -----
// UpdateChangeItemDescription
// Updates changeID's Description
// int changeID (in)
// char[31] Description (in)
void UpdateChangeItemDescription(int changeID, char Description[31]);

// -----
// BackUpChangeRequest
// Backs up Change Request file in database
// bool value if back up was successful (out)
bool BackUpChangeRequest();

// -----
// BackUpUsers
// Backs up Users file in database
// bool value if back up was successful (out)
bool BackUpUsers();

// -----
// BackUpChangeItems
// Backs up Change Items file in database
// bool value if back up was successful (out)
bool BackUpChangeItems();

// -----
// BackUpProductReleases
// Backs up Product Releases file in database
// bool value if back up was successful (out)
bool BackUpProductReleases();

// -----
// BackUpProducts
// Backs up Products file in database
// bool value if back up was successful (out)
bool BackUpProducts();

// -----
// BackUpEntireDatabase
// Backs up all file in database
// bool value if back up was successful (out)
bool BackUpEntireDatabase(){
    BackUpChangeRequest();
    BackUpUsers();
    BackUpChangeItems();
    BackUpProductReleases();
    BackUpProducts();
}


#endif // CONTROL_H
