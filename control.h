/*
    Revision History:
    1.0 - 03-05-2024 [Date] - Modified by Skyler

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
// showUserInfo
// Displays user information
void showUserInfo();

// -----
// showChangeRequestReport
// Displays a report for change requests
void showChangeRequestReport();


#endif // CONTROL_H
