/*
    Revision History:
    1.0 - 03-05-2024 [Date] - Modified by Tanvir
    1.0 - 10-07-2024 [Date] - Modified by Charles

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
void CreateCustomerRequest();
void ModifyRequest();
int PrintReportsAndInquiries();
void BackupData();

//-------------------------------------
// Function prototypes

// -----
// mainMenu
// Handles user input
// returns: Bool, true if user chooses to exit, false otherwise (out)
bool TextUI(){
    switch(MainMenu())
    {
        case 1:
            CreateCustomerRequest();
            break;
        case 2:
            ModifyRequest();
            break;
        case 3:
            PrintReportsAndInquiries();
            break;
        case 4:
            BackupData();
            break;
        case 0:
            return true;
        default:
            // Error message
            cout << "Substitute Error Message" << endl;

    }

    return false;
};

// -----
// Main Menu
// Displays Main Menu, waits for User input, and 
// returns which menu is selected by User
// returns: int input (User Selection) (out)
int MainMenu(){
    int input;
    cout << "=== Main Menu ===" << endl;
    cout << "1) Create Customer Request" << endl;
    cout << "2) Modify Change/Feature Request" << endl;
    cout << "3) Print Reports and Inquiries" << endl;
    cout << "4) Backup Data" << endl;
    cout << "0) Exit" << endl;
    cout << "Input your selection (0-4) and hit Enter: ";
    cin >> input;
    return input;
}

// -----
// Create Customer Request
// Displays menu for Create Customer Request and waits for User input
void CreateCustomerRequest(){
    int input;
    cout << "=== Customer Request ===" << endl;
    cout << "1) New Customer" << endl;
    cout << "2) Existing Customer" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Input your selection (0-2) and hit Enter: ";
    cin >> input;
}

// -----
// Modify Change/Feature Request
// Displays Modify Change/Feature Request menu and waits for User input
void ModifyRequest(){
    int input;
    cout << "=== Modify Change/Feature Request ===" << endl;
    cout << "1) Update status" << endl;
    cout << "2) Update anticipated release date" << endl;
    cout << "3) Update description" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Input your selection (0-3) and hit Enter: ";
    cin >> input;
}

// -----
// PrintReportsAndInquiries
// Displays Menu for print reports and inquiries, waits for User input, and
// Returns which action is selected by user
// returns: int input (User Selection) (out)
int PrintReportsAndInquiries(){
    int input;
    cout << "=== Print Reports and Inquiries ===" << endl;
    cout << "1) Print Report for managers" << endl;
    cout << "2) Print Report for customer inquiries" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Input your selection (0-2) and hit Enter: ";
    cin >> input;
    return input;
}

// -----
// BackupData
// Displays Backup Data menu and waits for User input
void BackupData(){
    int input;
    cout << "=== Backup Data ===" << endl;
    cout << "1) Backup the entire database" << endl;
    cout << "2) Backup specific data sets" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Input your selection (0-2) and hit Enter: ";
    cin >> input;
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
