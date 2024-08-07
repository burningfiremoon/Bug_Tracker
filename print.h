/*
    Revision History:
    1.0 - 03-05-2024 [Date] - Modified by Anthony

    print.h:
    This header file contains function declarations for printing various reports.
*/
//-------------------------------------
#ifndef PRINT_H
#define PRINT_H

//-------------------------------------
// Function prototypes

// -----
// printChangeItem
// Prints details of a change item
void printChangeItem(const ChangeItem& item);

// -----
// printOpenBugs
// Prints a list of open bugs
void printOpenBugs(const char* productName, Date start, Date end);

// -----
// printStatusReport
// Prints a status report
void printStatusReport(Date start, Date end);

#endif // PRINT_H
