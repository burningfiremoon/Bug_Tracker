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
    cout << "3) Print/View Reports and Inquiries" << endl;
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
    // needed variables
    int input;


    // Print initial selection Menu
    cout << "=== Customer Request ===" << endl;
    cout << "1) New Customer" << endl;
    cout << "2) Existing Customer" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Input your selection (0-2) and hit Enter: ";
    cin >> input;
    switch (input)
    {
    case 1:
        {
        char Name[31];
        char PhoneNumber[18];
        char Email[25];
        char ProductID[31];
        char Version[9];
        char Description[31];
        int decision;
        int Priority;
    
        cout << "Enter the Customer Name (Length: 30 characters max, Format: FirstName, LastName):" << endl;
        cin >> Name;
        cout << "Enter the Phone Number (Length: 11 digits max, Format: +D (DDD)-DDD-DDDD):" << endl;
        cin >> PhoneNumber;
        cout << "Enter Email address:" << endl;
        cin >> Email;
        if (Init_User(Name, PhoneNumber, Email)){
            cout << "Enter the ProductID which needs a change Request: ";
            // Ask for ProductID to create a Change Request for product
            cin >> ProductID;
            cout <<"Enter the Release ID (Length: 8 characters max):" << endl;
            cin >> Version;
            cout << "Enter the Description of the Bug (Length: 30 characters max):" << endl;
            cin >> Description;
            cout << "Enter the Priority (Ranging: 1-5):" << endl;
            cin >> Priority;

            Init_ChangeRequest(ProductID, Version, Description, Priority);
            // Show list of Change Items with matching Product ID
            ShowChangeItems(ProductID);
            // If There is a matching Change Item, connect change request to change item
            cout << "Is there a matching change item for the change request (Y/N)?" << endl;
            cin >> decision;
            if (decision)
            {
                // connect change request to change item
                connectChangeRequest();
            } else if (!decision){
                // else create a new change item
                Init_ChangeItem();
                Init_ProductRelease();
            } else{
                cout << "Insert Error Here";
            }
        }
        }
        break;
    case 2:
        {
        char Product[11];
        char Version[9];
        char Description[31];
        int Priority;
        char decision;
        
        cout << "Enter the Product Name which needs a change Request: ";
        // Ask for ProductID to create a Change Request for product
        cin >> Product;
        cout <<"Enter the Release ID (Length: 8 characters max):" << endl;
        cin >> Version;
        cout << "Enter the Description of the Bug (Length: 30 characters max):" << endl;
        cin >> Description;
        cout << "Enter the Priority (Ranging: 1-5):" << endl;
        cin >> Priority;
        cout << "Do you confirm the Release ID, Description, and Priority (Y/N)?" << endl;

        if (decision == 'Y')
        {
            Init_ChangeRequest(Product, Version, Description, Priority);

        } else if (decision == 'N'){
            cout << "Insert Event here" << endl;
        }
        // Show list of Change Items with matching Product ID
        ShowChangeItems(Product);
        // If There is a matching Change Item, connect change request to change item
        cout << "Is there a matching change item for the change request (Y/N)?" << endl;
        if (decision == 'Y')
        {
            // connect change request to change item
            connectChangeRequest();
        } else if (decision == 'N'){
            // else create a new change item
            Init_ChangeItem();
            Init_ProductRelease();
        } else{
            cout << "Insert Error Here";
        }

        break;
        }
    case 0:
        return;
    default:
        break;
    }
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
    cout << "4) Add new product release" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Input your selection (0-3) and hit Enter: ";
    cin >> input;

    switch (input)
    {
    case 1:
        {
        int changeID;
        int decision;
        do 
        {
        cout << "Enter ChangeID to view status (6 digits):" << endl;
        cin >> changeID;
        showChangeRequestReport(changeID);
        cout << "Enter the desired status:\n0) Reported\n1) InProgress\n2) Done\n3) Cancelled";
        cin >> decision;
        UpdateChangeRequestStatus(changeID, decision);
        cout << "To repeat the process, enter '1' or go back to main menu, enter '0'" << endl;
        cin >> decision;
        } while (decision);
        break;
        }
    case 2:
        
        break;
    case 3:
        
        break;
    case 4:

        break;
    case 0:
        return;
    default:
        break;
    }
}

// -----
// PrintReportsAndInquiries
// Displays Menu for print reports and inquiries, waits for User input, and
// Returns which action is selected by user
// returns: int input (User Selection) (out)
int PrintReportsAndInquiries(){
    int input;
    cout << "=== Print/View Reports and Inquiries ===" << endl;
    cout << "1) Print Report for managers" << endl;
    cout << "2) Print Report for customer inquiries" << endl;
    cout << "3) View status" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Input your selection (0-2) and hit Enter: ";
    cin >> input;
    return input;
        switch (input)
    {
    case 1:

        break;
    case 2:
        {
        char ProductID[16];
        string dateStart;
        string dateEnd;
        Date start;
        Date end;
        cout << "Enter the Product ID [Must be between 5 to 15 characters]:" << endl;
        cin >> ProductID;
        CheckProductExists(ProductID);
        cout << "Enter start date for date range (YYYY-MM-DD): ";
        cin >> dateStart;
        cout << "Enter end date for date range (YYYY-MM-DD): ";
        cin >> dateEnd;
        start.y = stoi(dateStart.substr(0,4));
        start.m = stoi(dateStart.substr(5,6));
        start.d = stoi(dateStart.substr(8,9));
        end.y = stoi(dateEnd.substr(0,4));
        end.m = stoi(dateEnd.substr(5,6));
        end.d = stoi(dateEnd.substr(8,9));

        CheckStatusReport(start, end);
        break;
        }
    case 3:
        {
        int changeID;
        cout << "Enter ChangeID to view status (6 digits):" << endl;
        cin >> changeID;
        ViewChangeItem(changeID);
        break;
        }
    case 0:
        return;
    default:
        break;
    }
    return 0;
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
        switch (input)
    {
    case 1:

        break;
    case 2:
        
        break;
    case 3:
        
        break;
    case 0:
        
        break;
    default:
        break;
    }
}




#endif // UI_H
