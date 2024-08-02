#include "control.h"
#include "ui.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Main menu for the application
int MainMenu() {
    int input;
    bool exit = false;

    while (!exit) {
        cout << "=== Main Menu ===" << endl;
        cout << "1) Create Customer Request" << endl;
        cout << "2) Modify Request" << endl;
        cout << "3) Print Reports and Inquiries" << endl;
        cout << "4) Backup Data" << endl;
        cout << "0) Exit" << endl;
        cout << "Enter your choice: ";
        cin >> input;

        switch (input) {
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
                exit = true;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return input;
}

// Function to handle the creation of customer requests
void CreateCustomerRequest() {
    int input;
    cout << "=== Create Customer Request ===" << endl;
    cout << "1) New Customer" << endl;
    cout << "2) Existing Customer" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> input;

    switch (input) {
        case 1: {
            char Name[31];
            char PhoneNumber[12];
            char Email[25];
            char confirmation;
            char Product[11];
            char ReleaseID[9];
            char Description[31];
            int Priority;

            // Collect customer information
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter the Customer Name (Length: 30 characters max): ";
            cin.getline(Name, 31);
            cout << "Enter the Phone Number (Length: 11 digits max): ";
            cin.getline(PhoneNumber, 12);
            cout << "Enter Email address: ";
            cin.getline(Email, 25);
            cout << "Are you sure you want to add " << Name << " as a customer (Y/N)? ";
            cin >> confirmation;
            if (tolower(confirmation) == 'y') {
                if (!Init_User(Name, PhoneNumber, Email)) {
                    cout << "Error creating user. Please try again." << endl;
                    return;
                }
                cout << "The Customer, " << Name << ", has been added." << endl;
            } else {
                cout << "Customer addition canceled." << endl;
                return;
            }

            // Collect change request information
            cout << "Enter the name of the product: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.getline(Product, 31);
            cout << "Enter the Release ID (Length: 8 characters max): ";
            cin.getline(ReleaseID, 9);
            cout << "Enter the Description of the Bug (Length: 30 characters max): ";
            cin.getline(Description, 31);
            cout << "Enter the Priority (Ranging: 1-5): ";
            cin >> Priority;

            cout << "Do you confirm the Release ID, Description, and Priority (Y/N)? ";
            cin >> confirmation;
            if (tolower(confirmation) == 'y') {
                int changeID = 0; // Initialize changeID to store the output
                if (Init_ChangeRequest(Name, Product, ReleaseID, Description, Priority, changeID)) {
                    cout << "Change request has been successfully created." << endl;
                    cout << "The Change ID is " << changeID << " for " << Name << "." << endl;
                } else {
                    cout << "Error creating change request. Please try again." << endl;
                }
            } else {
                cout << "Change request creation canceled." << endl;
            }
            break;
        }
        case 2: {
            char Product[11];
            char Version[9];
            char Description[31];
            int Priority;
            int decision;
            char Name[31];

            cout << "Enter User Name (max 30 characters): ";
            cin >> Name;

            cout << "Enter Product Name (max 10 characters): ";
            cin >> Product;
            cout << "Enter Version (max 8 characters): ";
            cin >> Version;
            cout << "Enter Description (max 30 characters): ";
            cin >> Description;
            cout << "Enter Priority (1-5): ";
            cin >> Priority;

            Init_ChangeRequest(Name, Product, Version, Description, Priority, decision);
            ShowChangeItems(Product);

            cout << "Is there a matching change item for the change request? (1 for Yes, 0 for No): ";
            cin >> decision;
            if (decision == 1) {
                int changeID;
                cout << "Enter Change ID: ";
                cin >> changeID;
                connectChangeRequest(Name, changeID);
            } else {
                char ChangeDescription[31];
                if (!CheckProductReleaseExists(Product)) {
                    Date date;
                    string strDate;
                    cout << "Enter Product Release Date (YYYY-MM-DD): ";
                    cin >> strDate;
                    try {
                        if (strDate.length() == 10 && strDate[4] == '-' && strDate[7] == '-') {
                            date.y = stoi(strDate.substr(0, 4));
                            date.m = stoi(strDate.substr(5, 2));
                            date.d = stoi(strDate.substr(8, 2));
                            Init_ProductRelease(Product, date);
                        } else {
                            throw std::invalid_argument("Invalid date format");
                        }
                    } catch (const std::invalid_argument& e) {
                        cerr << "Invalid date format: " << e.what() << endl;
                        return;
                    }
                }
                cout << "Enter Change Description (max 30 characters): ";
                cin >> ChangeDescription;
                connectChangeRequest(Name, Init_ChangeItem(Product, ChangeDescription));
            }
            break;
        }
        case 0:
            return;
        default:
            cout << "Invalid option. Please try again." << endl;
    }
}

// Function to modify existing requests
void ModifyRequest() {
    int input;
    cout << "=== Modify Request ===" << endl;
    cout << "1) Update Status" << endl;
    cout << "2) Update Anticipated Release Date" << endl;
    cout << "3) Update Description" << endl;
    cout << "4) Update Customer Information" << endl;
    cout << "5) Add New Product Release" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> input;

    switch (input) {
        case 1: {
            int changeID;
            char status[10];
            int decision;
            do {
                cout << "Enter Change ID: ";
                cin >> changeID;
                string changeIDStr = to_string(changeID);
                if (!CheckChangeItemExists(changeIDStr.c_str())) {
                    cout << "Change item not found." << endl;
                    return;
                }
                ViewChangeItem(changeID);
                cout << "Enter new status: ";
                cin >> status;
                UpdateChangeItemStatus(changeIDStr.c_str(), status);
                cout << "To repeat the process, enter '1' or go back to main menu, enter '0': ";
                cin >> decision;
            } while (decision);
            break;
        }
        case 2: {
            int changeID;
            string strDate;
            Date date;
            int decision;
            do {
                cout << "Enter Change ID: ";
                cin >> changeID;
                string changeIDStr = to_string(changeID);
                if (!CheckChangeItemExists(changeIDStr.c_str())) {
                    cout << "Change item not found." << endl;
                    return;
                }
                ViewChangeItem(changeID);
                cout << "Enter new release date (YYYY-MM-DD): ";
                cin >> strDate;
                try {
                    if (strDate.length() == 10 && strDate[4] == '-' && strDate[7] == '-') {
                        date.y = stoi(strDate.substr(0, 4));
                        date.m = stoi(strDate.substr(5, 2));
                        date.d = stoi(strDate.substr(8, 2));
                        UpdateChangeItemReleaseDate(changeID, date);
                    } else {
                        throw std::invalid_argument("Invalid date format");
                    }
                } catch (const std::invalid_argument& e) {
                    cerr << "Invalid date format: " << e.what() << endl;
                    return;
                }
                cout << "To repeat the process, enter '1' or go back to main menu, enter '0': ";
                cin >> decision;
            } while (decision);
            break;
        }
        case 3: {
            int changeID;
            char Description[31];
            int decision;
            do {
                cout << "Enter Change ID: ";
                cin >> changeID;
                string changeIDStr = to_string(changeID);
                if (!CheckChangeItemExists(changeIDStr.c_str())) {
                    cout << "Change item not found." << endl;
                    return;
                }
                ViewChangeItem(changeID);
                cout << "Enter new description (max 30 characters): ";
                cin >> Description;
                UpdateChangeItemDescription(changeID, Description);
                cout << "To repeat the process, enter '1' or go back to main menu, enter '0': ";
                cin >> decision;
            } while (decision);
            break;
        }
        case 4: {
            // Update customer information
            char Name[31];
            cout << "Enter Customer Name (max 30 characters): ";
            cin >> Name;

            int decision;
            cout << "1) Update Name" << endl;
            cout << "2) Update Email" << endl;
            cout << "3) Update Phone Number" << endl;
            cout << "0) Return to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> decision;

            switch (decision) {
                case 1: {
                    char newName[31];
                    cout << "Enter New Name: ";
                    cin >> newName;
                    UpdateUserName(Name, newName);
                    break;
                }
                case 2: {
                    char newEmail[25];
                    cout << "Enter New Email: ";
                    cin >> newEmail;
                    UpdateUserEmail(Name, newEmail);
                    break;
                }
                case 3: {
                    char newPhoneNumber[18];
                    cout << "Enter New Phone Number: ";
                    cin >> newPhoneNumber;
                    UpdateUserPhoneNumber(Name, newPhoneNumber);
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Invalid option. Please try again." << endl;
            }
            break;
        }
        case 5: {
            char Name[11];
            string strDate;
            Date date;
            cout << "Enter Product Name (max 10 characters): ";
            cin >> Name;
            cout << "Enter Release Date (YYYY-MM-DD): ";
            cin >> strDate;
            try {
                if (strDate.length() == 10 && strDate[4] == '-' && strDate[7] == '-') {
                    date.y = stoi(strDate.substr(0, 4));
                    date.m = stoi(strDate.substr(5, 2));
                    date.d = stoi(strDate.substr(8, 2));
                    Init_ProductRelease(Name, date);
                } else {
                    throw std::invalid_argument("Invalid date format");
                }
            } catch (const std::invalid_argument& e) {
                cerr << "Invalid date format: " << e.what() << endl;
                return;
            }
            break;
        }
        case 0:
            return;
        default:
            cout << "Invalid option. Please try again." << endl;
    }
}

// Function to print reports and inquiries
void PrintReportsAndInquiries() {
    int input;
    cout << "=== Print Reports and Inquiries ===" << endl;
    cout << "1) Print Open Change Items" << endl;
    cout << "2) Print Customer Information" << endl;
    cout << "3) View Change Item Status" << endl;
    cout << "4) View User Information" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> input;

    switch (input) {
        case 1: {
            char Product[11];
            string dateStart, dateEnd;
            Date start, end;

            cout << "Enter Product Name (max 10 characters): ";
            cin >> Product;
            if (!CheckProductExists(Product)) {
                cout << "Product not found." << endl;
                return;
            }
            cout << "Enter Start Date (YYYY-MM-DD): ";
            cin >> dateStart;
            cout << "Enter End Date (YYYY-MM-DD): ";
            cin >> dateEnd;
            try {
                if (dateStart.length() == 10 && dateStart[4] == '-' && dateStart[7] == '-' &&
                    dateEnd.length() == 10 && dateEnd[4] == '-' && dateEnd[7] == '-') {
                    start.y = stoi(dateStart.substr(0, 4));
                    start.m = stoi(dateStart.substr(5, 2));
                    start.d = stoi(dateStart.substr(8, 2));
                    end.y = stoi(dateEnd.substr(0, 4));
                    end.m = stoi(dateEnd.substr(5, 2));
                    end.d = stoi(dateEnd.substr(8, 2));
                    PrintOpenBugs(Product, start, end);
                } else {
                    throw std::invalid_argument("Invalid date format");
                }
            } catch (const std::invalid_argument& e) {
                cerr << "Invalid date format: " << e.what() << endl;
                return;
            }
            break;
        }
        case 2: {
            char Name[31];
            cout << "Enter Customer Name (max 30 characters): ";
            cin >> Name;
            PrintUserInfo(Name);
            break;
        }
        case 3: {
            int changeID;
            cout << "Enter Change ID: ";
            cin >> changeID;
            ViewChangeItem(changeID);
            break;
        }
        case 4: {
            char name[31];
            cout << "Enter User Name (max 30 characters): ";
            cin >> name;
            showUserInfo(name);
            break;
        }
        case 0:
            return;
        default:
            cout << "Invalid option. Please try again." << endl;
    }
}

// Function to handle data backup
void BackupData() {
    int input;
    cout << "=== Backup Data ===" << endl;
    cout << "1) Backup Entire Database" << endl;
    cout << "2) Backup Specific Data Sets" << endl;
    cout << "0) Return to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> input;

    switch (input) {
        case 1:
            BackUpDatabase("BackupDatabase.txt");
            break;
        case 2: {
            int decision;
            cout << "Which data set would you like to back up?" << endl;
            cout << "1) Change Requests" << endl;
            cout << "2) Users" << endl;
            cout << "3) Change Items" << endl;
            cout << "4) Product Releases" << endl;
            cout << "5) Products" << endl;
            cout << "0) Return" << endl;
            cout << "Enter your choice: ";
            cin >> decision;

            switch (decision) {
                case 1:
                    BackUpDatabase("BackupChangeRequests.txt");
                    break;
                case 2:
                    BackUpDatabase("BackupUsers.txt");
                    break;
                case 3:
                    BackUpDatabase("BackupChangeItems.txt");
                    break;
                case 4:
                    BackUpDatabase("BackupProductReleases.txt");
                    break;
                case 5:
                    BackUpDatabase("BackupProducts.txt");
                    break;
                case 0:
                    return;
                default:
                    cout << "Invalid option. Please try again." << endl;
            }
            break;
        }
        case 0:
            return;
        default:
            cout << "Invalid option. Please try again." << endl;
    }
}
