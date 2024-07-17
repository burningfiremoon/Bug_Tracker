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
void UpdateChangeRequest(int changeID);
void CheckChangeRequestExists();
void CheckUserExists();
void CheckChangeItemExists(int ChangeID);
void CheckProductExists(char ProductID[16]);
void OpenBugs();
// -----
// Check Status report
// receive date range in the format (YYYY-MM-DD to YYYY-MM-DD) and couts all status reports in date range 
void CheckStatusReport(string dateRange);

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
void ShowChangeItems(char ProductID[31]);

// -----
// Connect Change Request
// Connects matching change request to change item
void connectChangeRequest();

void ViewChangeItem(int changeID){
    // Check existence
    void CheckChangeItemExists(int ChangeID);
}
void PrintOpenBugs();
void PrintStatusReport();
bool Init_ProductRelease();
bool Init_ChangeItem();
bool Init_User(char Name[31], char PhoneNumber[18], char Email[25]);
bool Init_ChangeRequest(char ProductName[31], char ReleaseID[9], char Description[31], int Priority);
bool Init_Product();
bool PrintChangeRequestReport();
bool PrintUserInfo();
void Add();

#endif // CONTROL_H
