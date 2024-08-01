/*
    Revision History:
    1.0 - 03-05-2024 - Created by Anthony

    control.h:
    This header file contains function declarations for handling various database operations.
    It includes necessary headers and defines functions to manipulate user and change item records.
*/

#ifndef CONTROL_H
#define CONTROL_H

#include "DatabaseRecord.h"
#include "ChangeItem.h"
#include "ChangeRequest.h"
#include "User.h"
#include "StatusConstants.h"
#include <iostream>
#include <fstream>
#include <cstring>

// Function declarations

// User input control
void StopAccepting();
void StartAccepting();

// Database file management
void OpenDatabase(const char* filename);
void CloseDatabase();

// User management
bool Init_User(const char* name, const char* phone, const char* email);
void UpdateUserName(const char* oldName, const char* newName);
void UpdateUserEmail(const char* name, const char* newEmail);
void UpdateUserPhoneNumber(const char* name, const char* newPhoneNumber);
bool CheckUserExists(const char* name);
void PrintUserInfo(const char* Name);
void showUserInfo(const char* Name);

// Change Item management
int Init_ChangeItem(const char* product, const char* changeDescription);
void UpdateChangeItemStatus(const char* changeID, const char* status);
bool CheckChangeItemExists(const char* changeID);
void ViewChangeItem(int changeID);
void UpdateChangeItemReleaseDate(int changeID, Date date);
void UpdateChangeItemDescription(int changeID, const char* description);
void PrintChangeItem(int changeID);

// Change Request management
bool Init_ChangeRequest(const char* Name, const char* Product, const char* Version, const char* Description, int Priority);
void ShowChangeItems(const char* Product);
void connectChangeRequest(const char* Name, int changeID);

// Product Release management
bool Init_ProductRelease(const char* Product, Date date);
bool CheckProductReleaseExists(const char* Product);

// Product management
bool CheckProductExists(const char* Product);
void PrintOpenBugs(const char* Product, Date start, Date end);

// Backup operation
bool BackUpDatabase(const std::string& outputFile);

#endif // CONTROL_H
