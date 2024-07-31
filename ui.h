/*
    Revision History:
    1.0 - 03-05-2024 - Created by Tanvir
    1.0 - 10-07-2024 - Modified by Charles
    1.0 - 17-07-2024 - Modified by Charles

    ui.h:
    This header file contains function declarations for the user interface.
    It includes the main menu and other UI functions.
*/

#ifndef UI_H
#define UI_H

#include "control.h"
#include <iostream>

// Function declarations

// Displays the main menu and handles user input.
int MainMenu();

// Handles the creation of a customer request.
void CreateCustomerRequest();

// Modifies an existing request.
void ModifyRequest();

// Prints reports and inquiries.
void PrintReportsAndInquiries();

// Handles data backup operations.
void BackupData();

// Main text-based UI function that directs to appropriate menu actions.
bool TextUI();

#endif // UI_H
