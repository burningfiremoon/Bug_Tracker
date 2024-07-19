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
#include "DatabaseRecordh."
#include "ChangeItem.h"
#include "ChangeRequest.h"
#include "ProductRelease.h"
#include "User.h"
#include "print.h"
#include "ui.h"

//-------------------------------------
// Function prototypes

//functions taking care of different scenarios

// -----
// StopAccepting
// Tells main To stop accepting User input
void StopAccepting()
{
    return;
}

// -----
// StartAccepting
// Tells main To start accepting User input
void StartAccepting()
{
    return;
}

// -----
// CloseDatabase
// Closes access to database
void CloseDatabase()
{
    return;
}

// -----
// OpenDatabase
// opens access to database
void OpenDatabase()
{
    return;
}

// -----
// UpdateUserName
// Updates User's name from Name to newName
// char[31] Name (in)
// char[31] newName (in)
void UpdateUserName(char* Name, char* newName)
{
    return;
}

// -----
// UpdateUserEmail
// Updates User's Email to newEmail
// char[31] Name (in)
// char[25] newEmail (in)
void UpdateUserEmail(char* Name, char* newEmail)
{
    return;
}

// -----
// UpdateUserPhoneNumber
// Updates User's phone number to newPhoneNumber
// char[31] Name (in)
// char[18] newPhoneNumber (in)
void UpdateUserPhoneNumber(char* Name, char* newPhoneNumber)
{
    return;
}

// -----
// UpdateChangeItemStatus
// Updates the status of change item with the matching ChangeID with status
// int changeID (in)
// int status (in)
void UpdateChangeItemStatus(int changeID, int status)
{
    return;
}

// -----
// CheckUserExists
// Checks if User object exists in database and returns a bool value indicating existence
// char[31] Name (in)
// bool value if object exists (out)
bool CheckUserExists(char* Name)
{
    return true;
}

// -----
// CheckChangeItemExists
// Checks if Change Item object exists in database and returns a bool value indicating existence
// int ChangeID (in)
// bool value if object exists (out)
bool CheckChangeItemExists(int ChangeID)
{
    return true;
}

// -----
// CheckProductExists
// Checks if Product object exists in database and returns a bool value indicating existence
// char[11] Product (in)
// bool value if object exists (out)
bool CheckProductExists(char* Product)
{
    return true;
}

// -----
// CheckProductReleaseExists
// Checks if Product Release object exists in database and returns a bool value indicating existence
// char[11] Productname (in)
// bool value if object exists (out)
bool CheckProductReleaseExists(char* Product)
{
    return true;
}

// -----
// ViewStatusReport
// Displays all open change items between start and end date range onto terminal
// Date start (in)
// Date end (in)
// Open Change Items between date range (out)
void ViewStatusReport(Date start, Date end)
{
    return;
}

// -----
// showUserInfo
// Displays User information with matching Name onto terminal
// char[31] Name (in)
void showUserInfo(char* Name)
{
    return;
}

// -----
// ShowChangeItems
// Displays all Change Items for Product onto terminal
// char[11] ProductID (in)
void ShowChangeItems(char* Product)
{
    return;
}

// -----
// connectChangeRequest
// Connects Change Request to Change Item
// char[31] Name (in)
// int changeID (in)
void connectChangeRequest(char* Name, int changeID)
{
    return;
}

// -----
// ViewChangeItem
// Displays Change Item information onto terminal
// int changeID (in)
void ViewChangeItem(int changeID)
{
    return;
}


// -----
// PrintOpenBugs
// Sends all open change items of product between start and end dates to printer
// char[11] Product (in)
// Date start (in)
// Date end (in)
void PrintOpenBugs(char* Product, Date start, Date end)
{
    return;
}

// -----
// Init_ProductRelease
// Initializes new Product Release object
// char[11] Product (in)
// Date date (in)
// bool value if initialization was successful (out)
bool Init_ProductRelease(char* Product, Date date)
{
    return;
}

// -----
// Init_ChangeItem
// Initializes new Change Item object
// char[11] Product (in)
// char[31] ChangeDescription (in)
// returns new unique (int) changeID (out)
int Init_ChangeItem(char* Product, char* ChangeDescription)
{
    return 1;
}

// -----
// Init_User
// Initializes new User object
// char[31] Name (in)
// char[18] PhoneNumber (in)
// char[25] Email (in)
// bool value if initialization was successful (out)
bool Init_User(char* Name, char* PhoneNumber, char* Email)
{
    return true;
}

// -----
// Init_ChangeRequest
// Initializes new Change Request object
// char[31] Name (in)
// char[11] Product (in)
// char[9] ReleaseID (in)
// char[31] Description (in)
// int Priority (in)
// bool value if initialization was successful (out)
bool Init_ChangeRequest(char* Name, char* Product, char* ReleaseID, char* Description, int Priority)
{
    return true;
}

// -----
// Init_Product
// Initializes new Product
// char[11] Product (in)
// bool value if initialization was successful (out)
bool Init_Product(char* Product)
{
    return true;
}

// -----
// PrintChangeItem
// Sends information for a specific change item to printer
// int ChangeID (in)
void PrintChangeItem(int ChangeID)
{
    return;
}

// -----
// PrintUserInfo
// Sends information for a specific user to printer
// char[31] Name (in)
void PrintUserInfo(char* Name)
{
    return;
}

// -----
// UpdateChangeItemReleaseDate
// Updates changeID's release date to date
// int changeID (in)
// Date date (in)
void UpdateChangeItemReleaseDate(int changeID, Date date)
{
    return;
}

// -----
// UpdateChangeItemDescription
// Updates changeID's Description
// int changeID (in)
// char[31] Description (in)
void UpdateChangeItemDescription(int changeID, char* Description)
{
    return;
}

// -----
// BackUpChangeRequest
// Backs up Change Request file in database
// bool value if back up was successful (out)
bool BackUpChangeRequest()
{
    return true;
}

// -----
// BackUpUsers
// Backs up Users file in database
// bool value if back up was successful (out)
bool BackUpUsers()
{
    return true;
}


// -----
// BackUpChangeItems
// Backs up Change Items file in database
// bool value if back up was successful (out)
bool BackUpChangeItems()
{
    return true;
}


// -----
// BackUpProductReleases
// Backs up Product Releases file in database
// bool value if back up was successful (out)
bool BackUpProductReleases()
{
    return true;
}


// -----
// BackUpProducts
// Backs up Products file in database
// bool value if back up was successful (out)
bool BackUpProducts()
{
    return true;
}


// -----
// BackUpEntireDatabase
// Backs up  file in database
// bool value if back up was successful (out)
bool BackUpEntireDatabase()
{
    BackUpChangeRequest();
    BackUpUsers();
    BackUpChangeItems();
    BackUpProductReleases();
    BackUpProducts();
    return true;
}


#endif // CONTROL_H
