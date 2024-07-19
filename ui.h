/*
    Revision History:
    1.0 - 03-05-2024 [Date] - Modified by Tanvir
    1.0 - 10-07-2024 - Modified by Charles
    1.0 - 17-07-2024 - Modified by Charles

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
        char Product[11];
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
            cout << "Enter the name of the Product which needs a change Request: ";
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
                Init_ChangeRequest(Name, Product, Version, Description, Priority);

            } else if (decision == 'N'){
                cout << "Insert Event here" << endl;
            }

            // Show list of Change Items with matching Product ID
            ShowChangeItems(Product);
            // If There is a matching Change Item, connect change request to change item
            cout << "Is there a matching change item for the change request (Y/N)?" << endl;
            cout << "Note: if yes, please remember the changeID" << endl;
            cout << "Enter Decision: ";
            cin >> decision;
            if (decision == 'Y')
            {
                int changeID;
                cout << "Enter changeID for change item: ";
                cin >> changeID;
                // connect change request to change item
                connectChangeRequest(Name, changeID);
            } 
            else if (decision == 'N')
            {
                char ChangeDescription[31];
                // else create a new change item
                if (!CheckProductReleaseExists(Product))
                {
                    // Creating a new Product Release if there's no product release for product name
                    string strDate;
                    Date date;
                    cout << "There's no product release for " << Product << endl;
                    cout << "Enter a date of release for product(YYYY-MM-DD): ";
                    cin >> strDate;
                    date.y = stoi(strDate.substr(0,4));
                    date.m = stoi(strDate.substr(5,6));
                    date.d = stoi(strDate.substr(8,9));

                    Init_ProductRelease(Product, date);
                }

                cout << "Enter the change description for new change Item (length: 30 characters max):"<< endl;
                cin >> ChangeDescription;

                connectChangeRequest(Name, Init_ChangeItem(Product, ChangeDescription));
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
        char Name[31];
        
        // Ask for name to connect change request to user
        cout << "Enter User's full Name (Format: FirstName, LastName): ";
        cin >> Name;
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
            Init_ChangeRequest(Name, Product, Version, Description, Priority);

        } else if (decision == 'N'){
            cout << "Insert Event here" << endl;
        }
        // Show list of Change Items with matching Product ID
        ShowChangeItems(Product);
        // If There is a matching Change Item, connect change request to change item
        cout << "Is there a matching change item for the change request (Y/N)?" << endl;
        cout << "Note: if yes, please remember the changeID" << endl;
        cout << "Enter Decision: ";
        cin >> decision;
        if (decision == 'Y')
        {
            int changeID;
            cout << "Enter changeID for change item: ";
            cin >> changeID;
            // connect change request to change item
            connectChangeRequest(Name, changeID);
        } else if (decision == 'N'){
            char ChangeDescription[31];
            // else create a new change item
            if (!CheckProductReleaseExists(Product)){
                // Creating a new Product Release if there's no product release for product name
                string strDate;
                Date date;
                cout << "There's no product release for " << Product << endl;
                cout << "Enter a date of release for product(YYYY-MM-DD): ";
                cin >> strDate;
                date.y = stoi(strDate.substr(0,4));
                date.m = stoi(strDate.substr(5,6));
                date.d = stoi(strDate.substr(8,9));

                Init_ProductRelease(Product, date);
            }
            // input for Change Description for new Change Item
            cout << "Enter the change description for new change Item (length: 30 characters max):"<< endl;
            cin >> ChangeDescription;

            connectChangeRequest(Name, Init_ChangeItem(Product, ChangeDescription));
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
    cout << "4) Update customer information" << endl;
    cout << "5) Add new product release" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Input your selection (0-3) and hit Enter: ";
    cin >> input;

    switch (input)
    {
    case 1:
        // Update Status for change Item
        {
        int changeID;
        int decision;
        do 
        {
            cout << "Enter ChangeID to view status (6 digits):" << endl;
            cin >> changeID;
            if (!CheckChangeItemExists(changeID)) 
            {
                cout << "The change Item with " << changeID << " changeID doesn't exist" << endl;
                return;
            }
            showChangeItemReport(changeID);
            cout << "Enter the desired status:\n0) Reported\n1) InProgress\n2) Done\n3) Cancelled";
            cout << "Input your selection (0-3) and hit Enter: ";
            cin >> decision;
            UpdateChangeItemStatus(changeID, decision);
            cout << "To repeat the process, enter '1' or go back to main menu, enter '0'" << endl;
            cin >> decision;
        } while (decision);
        break;
        }
    case 2:
        // update release Date for change item
        {
            int changeID;
            string strDate;
            Date date;
            int decision;
            do
            {
                cout << "Enter ChangeID to view status (6 digits):" << endl;
                cin >> changeID;
                if (!CheckChangeItemExists(changeID)) 
                {
                    cout << "The change Item with " << changeID << " changeID doesn't exist" << endl;
                    return;
                }
                showChangeItemReport(changeID);
                cout << "Enter the new release date for " << changeID <<" (YYYY-MM-DD): ";
                cin >> strDate;
                date.y = stoi(strDate.substr(0,4));
                date.m = stoi(strDate.substr(5,6));
                date.d = stoi(strDate.substr(8,9));

                UpdateChangeItemReleaseDate(changeID, date);
                cout << "To repeat the process, enter '1' or go back to main menu, enter '0'" << endl;
                cin >> decision;
            } while (decision);
            break;
        }
    case 3:
        // Update description for Change Item
        {
            int changeID;
            char Description[31];
            int decision;
            do
            {
                cout << "Enter ChangeID to view status (6 digits):" << endl;
                cin >> changeID;
                if (!CheckChangeItemExists(changeID)) 
                {
                    cout << "The change Item with " << changeID << " changeID doesn't exist" << endl;
                    return;
                }

                showChangeItemReport(changeID);
                cout << "Enter the new description for " << changeID <<" (Length: max 30 characters): ";
                cin >> Description;
                UpdateChangeItemDescription(changeID, Description);
                cout << "To repeat the process, enter '1' or go back to main menu, enter '0'" << endl;
                cin >> decision;
            } while (decision);
            break;
        }


        break;
    case 4:
    {
        char Name[31];
        cout << "Enter the name of the customer who's information you wish to update (Format: FirstName, LastName):" << endl;
        cin >> Name;
        if (CheckUserExists(Name)){
            int decision;
            cout << "What would you like to update?" << endl;
            cout << "1) Name" << endl;
            cout << "2) Email" << endl;
            cout << "3) Phone Number" << endl;
            cout << "0) Return to Main menu" << endl;
            cout << "Input your selection (0-3) and hit Enter: ";
            cin >> decision;
            switch (decision)
            {
            case 1:
                char newName[31];
                char decision;
                // Update name
                cout << "Enter the new name for " << Name << ": ";
                cin >> newName;
                cout << "Updating " << Name << " to " << newName <<". are you sure? (Y/N): ";
                cin >> decision;
                if (decision == 'Y'){
                    UpdateUserName(Name, newName);
                } else {
                    return;
                }
                break;
            case 2:
                char newEmail[25];
                char decision;
                // Update Email
                cout << "Enter the new Email for " << Name << ": ";
                cin >> newEmail;
                cout << "Updating Email to " << newEmail <<". are you sure? (Y/N): ";
                cin >> decision;
                if (decision == 'Y'){
                    UpdateUserEmail(Name, newEmail);
                } else {
                    return;
                }
                break;
            case 3:
                char newPhoneNumber[18];
                char decision;
                // Update Phone Number
                cout << "Enter the new phone number for " << Name << ": ";
                cin >> newName;
                cout << "Updating phone number to " << newPhoneNumber <<". are you sure? (Y/N): ";
                cin >> decision;
                if (decision == 'Y'){
                    UpdateUserPhoneNumber(Name, newPhoneNumber);
                } else {
                    return;
                }
                break;
            default:
                break;
            }

        } else {
            cout << Name << "Doesn't exist in our database, please create a new customer" << endl;
        }
        break;
    }
    case 5:
    {       
        char Name[11];
        string strDate;
        Date date;
        // new Product Release case 6
        cout << "Enter name of new product release (Length: 10 characters max): ";
        cin >> Name;
        cout << "Enter date of release (YYYY-MM-DD): ";
        cin >> strDate;
        date.y = stoi(strDate.substr(0,4));
        date.m = stoi(strDate.substr(5,6));
        date.d = stoi(strDate.substr(8,9));
        Init_ProductRelease(Name, date);
        break;
    }
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
int PrintReportsAndInquiries()
{    
    int input;
    cout << "=== Print/View Reports and Inquiries ===" << endl;
    cout << "1) Print Report for managers" << endl;
    cout << "2) Print Report for customer inquiries" << endl;
    cout << "3) View status" << endl;
    cout << "4) View User Information" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Input your selection (0-4) and hit Enter: ";
    cin >> input;
    switch (input)
    {
    case 1:
    {
        int decision;
        cout << "=== Print Reports for manager ===" << endl;
        cout << "1) Print open Change Items for product\n2) Print Change Item information\n0) return to main menu" << endl;
        cout << "Input your selection (0-2) and hit Enter: ";
        cin >> decision;
        switch (decision)
        {
        case 1:
        {
            // Print open Change Items for a product
            char Product[11];
            string dateStart;
            string dateEnd;
            Date start;
            Date end;
            cout << "Enter the Product name:" << endl;
            cin >> Product;
            if (!CheckProductExists(Product)) {
                cout << "Product doesn't exist in our system" << endl;
                return 1;
            }
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

            PrintOpenBugs(Product, start, end);
            char temp;
            cout << "Enter any character to return: ";
            cin >> temp;
            break;
        }
        case 2:
        {
            // Print Information for a specific change item
            int changeID;
            cout << "Enter ChangeID to view status (6 digits):" << endl;
            cin >> changeID;

            PrintChangeItem(changeID);
            char temp;
            cout << "Enter any character to return: ";
            cin >> temp;
            break;
        }
        default:
            return;
        }
        
        break;
    }
    case 2:
        {
            char Name[31];
            cout << "Enter Customer's full name (Format: FirstName, LastName): ";
            cin >> Name;
            PrintUserInfo(Name);
            char temp;
            cout << "Enter any character to return: ";
            cin >> temp;
            break;
        }
    case 3:
        {
            int changeID;
            cout << "Enter ChangeID to view status (6 digits):" << endl;
            cin >> changeID;
            ViewChangeItem(changeID);

            char temp;
            cout << "Enter any character to return: ";
            cin >> temp;
        break;
        }
    case 4:
        {
            char name[31];
            cout << "Enter the full name of the user to view their information (Format: FirstName, LastName): " << endl;
            cin >> name;

            showUserInfo(name);

            char temp;
            cout << "Enter any character to return: ";
            cin >> temp;

            break;
        }
    case 0:
        return 0;
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
        BackUpEntireDatabase();
        break;
    case 2:
        int decision;
        cout << "Which data set would you like to back up?" << endl;
        cout << "1) Change Requests" << endl;
        cout << "2) Users" << endl;
        cout << "3) Change Items" << endl;
        cout << "4) Product Releases" << endl;
        cout << "5) Products" << endl;
        cout << "0) Return" << endl;
        cout << "Input your selection (0-5) and hit Enter: ";
        cin >> decision;
        switch(decision){
        case 1:
            BackUpChangeRequest();
            break;
        case 2:
            BackUpUsers();
            break;
        case 3:
            BackUpChangeItems();
            break;
        case 4:
            BackUpProductReleases();
            break;
        case 5:
            BackUpProducts();
            break;
        case 0:
            return;
        default:
            return;
        }
        break;
    case 0:
        return;
    default:
        break;
    }
}




#endif // UI_H
