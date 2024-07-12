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
void PrintChangeItem();
void PrintOpenBugs();
void PrintStatusReport();
void Init_ProductRelease();
void Init_ChangeItem();
void Init_User();
void Init_ChangeRequest();
void Init_Product();
void PrintChangeRequestReport();
void PrintUserInfo();
void Add();

#endif // CONTROL_H
