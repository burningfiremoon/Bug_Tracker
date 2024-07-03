/*
    Revision History:
    1.0 - 03-05-2024 [Date] - Modified by Tanvir

    ui.h:
    This header file contains function declarations for the user interface.
    It includes the main menu and other UI functions.
*/
//-------------------------------------
#ifndef UI_H
#define UI_H

//-------------------------------------
// List of #includes
#include "control.h"

//-------------------------------------
// Function prototypes

// -----
// mainMenu
// Displays the main menu and handles user input
// returns: true if user chooses to exit, false otherwise (out)
bool mainMenu();

// -----
// showUserInfo
// Displays user information
void showUserInfo();

// -----
// showChangeRequestReport
// Displays a report for change requests
void showChangeRequestReport();

#endif // UI_H
