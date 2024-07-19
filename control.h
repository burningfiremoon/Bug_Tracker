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



void StopAccepting();
void StartAccepting();
void CloseDatabase();
void OpenDatabase();


void UpdateUserName(char Name[31],char newName[31]);
void UpdateUserEmail(char Name[31], char newEmail[25]);
void UpdateUserPhoneNumber(char Name[31], char newPhoneNumber[18]);
void UpdateChangeItemStatus(int changeID, int status);
bool CheckUserExists(char Name[31]);
bool CheckChangeItemExists(int ChangeID);
bool CheckProductExists(char Product[11]);
bool CheckProductReleaseExists(char Productname[11]);
// -----
// Check Status report
// receive date range in the format (YYYY-MM-DD to YYYY-MM-DD) and couts all status reports in date range
// Date start (in)
// Date end (in)
// Open Change Items between date range (out)
void ViewStatusReport(Date start, Date end);

// -----
// showUserInfo
// Displays user information
void showUserInfo(char Name[31]);

// -----
// showChangeRequestReport
// Displays a report for change requests
void showChangeItemReport(int changeID);

// Show Change Items
// Displays All Change items for ProductID
void ShowChangeItems(char ProductID[31]);

// -----
// Connect Change Request
// Connects matching change request to change item
void connectChangeRequest(char Name[31], int changeID);

void ViewChangeItem(int changeID){
    // Check existence
    CheckChangeItemExists(changeID);
}
void PrintOpenBugs(char Product[11],Date start, Date end);
bool Init_ProductRelease(char Product[11], Date date);

// -----
// Init_ChangeItem
// creates a new change Item object using Product name and a change description and outputs a new unique changeID
int Init_ChangeItem(char Product[11], char ChangeDescription[31]);


bool Init_User(char Name[31], char PhoneNumber[18], char Email[25]);
bool Init_ChangeRequest(char Name[31], char ProductName[31], char ReleaseID[9], char Description[31], int Priority);

bool Init_Product();
void PrintChangeItem(int ChangeID);
bool PrintUserInfo(char Name[31]);
void UpdateChangeItemReleaseDate(int changeID, Date date);
void UpdateChangeItemDescription(int changeID, char Description[31]);

// -----
// BackUpChangeRequest
// Backs all ChangeRequests in database into a new file
bool BackUpChangeRequest();

// -----
// BackUpUsers
// Backs all Users in database into a new file
bool BackUpUsers();

// -----
// BackUpChangeItems
// Backs all Change Items in database into a new file
bool BackUpChangeItems();

// -----
// BackUpProductReleases
// Backs all Product Releases in database into a new file
bool BackUpProductReleases();

// -----
// BackUpProducts
// Backs all Products in database into a new file
bool BackUpProducts();

// -----
// BackUpEntireDatabase
// Backs all files in database into a new file
bool BackUpEntireDatabase(){
    BackUpChangeRequest();
    BackUpUsers();
    BackUpChangeItems();
    BackUpProductReleases();
    BackUpProducts();
}

#endif // CONTROL_H
