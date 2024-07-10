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
#include <bits/stdc++.h>
using namespace std;

//-------------------------------------
// Declairing functions
int MainMenu();


//-------------------------------------
// Function prototypes

// -----
// mainMenu
// Displays the main menu and handles user input
// returns: true if user chooses to exit, false otherwise (out)
bool TextUI(){
    MainMenu();

    return true;
};

// -----
// Main Menu
// Prints Main Menu, waits for input, and returns
// which menu is selected by User
int MainMenu(){
    cout << "=== Main Menu ===" << endl;
    cout << "1) Create Customer Request" << endl;
    cout << "2) Modify/Update Change/Feature Request" << endl;
    cout << "3) Print Reports and Inquiries" << endl;
    cout << "4) Backup Data" << endl;
    cout << "0) Exit" << endl;

    return 1;
}



// -----
// showUserInfo
// Displays user information
void showUserInfo();

// -----
// showChangeRequestReport
// Displays a report for change requests
void showChangeRequestReport();

#endif // UI_H
