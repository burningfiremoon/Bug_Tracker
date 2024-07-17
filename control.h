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
void UpdateUserInfo();
void UpdateChangeRequest();
void CheckChangeRequestExists();
void CheckUserExists();
void CheckChangeItemExists();
void CheckProductExists();
void OpenBugs();
void CheckStatusReport();
// -----
// showUserInfo
// Displays user information
void showUserInfo();

// -----
// showChangeRequestReport
// Displays a report for change requests
void showChangeRequestReport();

// Show Change Items
// Displays All Change items for ProductID
void ShowChangeItems(string ProductID);

// -----
// Connect Change Request
// Connects matching change request to change item
void connectChangeRequest();

void PrintChangeItem();
void PrintOpenBugs();
void PrintStatusReport();
bool Init_ProductRelease();
bool Init_ChangeItem();
bool Init_User(string Name, string PhoneNumber, string Email);
bool Init_ChangeRequest(string ProductID);
bool Init_Product();
bool PrintChangeRequestReport();
bool PrintUserInfo();
void Add();

#endif // CONTROL_H
