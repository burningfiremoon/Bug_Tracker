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
void StopAccepting();

// -----
// StartAccepting
void StartAccepting();

// -----
// CloseDatabase
void CloseDatabase();

// -----
// OpenDatabase
void OpenDatabase();

// -----
// UpdateUserName
// char[31] Name (in)
// char[31] newName (in)
void UpdateUserName(char Name[31], char newName[31]);

// -----
// UpdateUserEmail
// char[31] Name (in)
// char[25] newEmail (in)
void UpdateUserEmail(char Name[31], char newEmail[25]);

// -----
// UpdateUserPhoneNumber
// char[31] Name (in)
// char[18] newPhoneNumber (in)
void UpdateUserPhoneNumber(char Name[31], char newPhoneNumber[18]);

// -----
// UpdateChangeItemStatus
// int changeID (in)
// int status (in)
void UpdateChangeItemStatus(int changeID, int status);

// -----
// CheckUserExists
// char[31] Name (in)
// bool value if object exists (out)
bool CheckUserExists(char Name[31]);

// -----
// CheckChangeItemExists
// int ChangeID (in)
// bool value if object exists (out)
bool CheckChangeItemExists(int ChangeID);

// -----
// CheckProductExists
// char[11] Product (in)
// bool value if object exists (out)
bool CheckProductExists(char Product[11]);

// -----
// CheckProductReleaseExists
// char[11] Productname (in)
// bool value if object exists (out)
bool CheckProductReleaseExists(char Product[11]);

// -----
// ViewStatusReport
// Date start (in)
// Date end (in)
// Open Change Items between date range (out)
void ViewStatusReport(Date start, Date end);

// -----
// showUserInfo
// char[31] Name (in)
void showUserInfo(char Name[31]);

// -----
// showChangeItemReport
// int changeID (in)
void showChangeItemReport(int changeID);

// -----
// ShowChangeItems
// char[31] ProductID (in)
void ShowChangeItems(char ProductID[31]);

// -----
// connectChangeRequest
// char[31] Name (in)
// int changeID (in)
void connectChangeRequest(char Name[31], int changeID);

// -----
// ViewChangeItem
// int changeID (in)
void ViewChangeItem(int changeID){
    // Check existence
    CheckChangeItemExists(changeID);
}

// -----
// PrintOpenBugs
// char[11] Product (in)
// Date start (in)
// Date end (in)
void PrintOpenBugs(char Product[11], Date start, Date end);

// -----
// Init_ProductRelease
// char[11] Product (in)
// Date date (in)
// bool value if initialization was successful (out)
bool Init_ProductRelease(char Product[11], Date date);

// -----
// Init_ChangeItem
// char[11] Product (in)
// char[31] ChangeDescription (in)
// returns new unique (int) changeID (out)
int Init_ChangeItem(char Product[11], char ChangeDescription[31]);

// -----
// Init_User
// char[31] Name (in)
// char[18] PhoneNumber (in)
// char[25] Email (in)
// bool value if initialization was successful (out)
bool Init_User(char Name[31], char PhoneNumber[18], char Email[25]);

// -----
// Init_ChangeRequest
// char[31] Name (in)
// char[11] Product (in)
// char[9] ReleaseID (in)
// char[31] Description (in)
// int Priority (in)
// bool value if initialization was successful (out)
bool Init_ChangeRequest(char Name[31], char Product[11], char ReleaseID[9], char Description[31], int Priority);

// -----
// Init_Product
// char[11] Product (in)
// bool value if initialization was successful (out)
bool Init_Product(char Product[11]);

// -----
// PrintChangeItem
// int ChangeID (in)
void PrintChangeItem(int ChangeID);

// -----
// PrintUserInfo
// char[31] Name (in)
void PrintUserInfo(char Name[31]);

// -----
// UpdateChangeItemReleaseDate
// int changeID (in)
// Date date (in)
void UpdateChangeItemReleaseDate(int changeID, Date date);

// -----
// UpdateChangeItemDescription
// int changeID (in)
// char[31] Description (in)
void UpdateChangeItemDescription(int changeID, char Description[31]);

// -----
// BackUpChangeRequest
// bool value if back up was successful (out)
bool BackUpChangeRequest();

// -----
// BackUpUsers
// bool value if back up was successful (out)
bool BackUpUsers();

// -----
// BackUpChangeItems
// bool value if back up was successful (out)
bool BackUpChangeItems();

// -----
// BackUpProductReleases
// bool value if back up was successful (out)
bool BackUpProductReleases();

// -----
// BackUpProducts
// bool value if back up was successful (out)
bool BackUpProducts();

// -----
// BackUpEntireDatabase
// bool value if back up was successful (out)
bool BackUpEntireDatabase(){
    BackUpChangeRequest();
    BackUpUsers();
    BackUpChangeItems();
    BackUpProductReleases();
    BackUpProducts();
}


#endif // CONTROL_H
