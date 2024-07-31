/*
    Revision History:
    1.0 - 03-05-2024 [Date] - Modified by Anthony

    print.h:
    This header file contains function declarations for printing various reports.
*/
//-------------------------------------
#ifndef PRINT_H
#define PRINT_H

#include "DatabaseRecord.h"
#include "ChangeItem.h"

//-------------------------------------
// Function prototypes

/*
    void printChangeItem(const ChangeItem& item)
    - Purpose: Prints details of a change item.
    - Parameters:
        - const ChangeItem& item (in): The change item to print.
*/
void printChangeItem(const ChangeItem& item);

/*
    void printOpenBugs(const char* productName, Date start, Date end)
    - Purpose: Prints a list of open bugs for a product within a date range.
    - Parameters:
        - const char* productName (in): The name of the product.
        - Date start (in): The start date of the range.
        - Date end (in): The end date of the range.
*/
void printOpenBugs(const char* productName, Date start, Date end);

/*
    void printStatusReport(Date start, Date end)
    - Purpose: Prints a status report for change items within a date range.
    - Parameters:
        - Date start (in): The start date of the range.
        - Date end (in): The end date of the range.
*/
void printStatusReport(Date start, Date end);

#endif // PRINT_H
