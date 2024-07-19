/*
    Revision History:
    1.0 - 03-05-2024 - Modified by Anthony

    print.cpp:
    This source file contains function definitions for printing various reports.
    It includes necessary headers and defines functions to print change items, open bugs, and status reports.
*/

//-------------------------------------
// List of #includes
#include "print.h"
#include "DatabaseRecord.h"
#include "ChangeItem.h"
#include "ChangeRequest.h"
#include <iostream>
#include <fstream>

using namespace std;

//-------------------------------------
// Function definitions

void printChangeItem(const ChangeItem& item) {
    cout << "Change ID: " << item.getChangeID() << endl;
    cout << "Product Name: " << item.getProductName() << endl;
    cout << "Change Description: " << item.getChangeDescription() << endl;
    cout << "Status: " << item.getStatus() << endl;
    cout << "Priority: " << item.getPriority() << endl;
    cout << "Release ID: " << item.getReleaseID().id << endl;
    cout << "Date First Reported: " << item.getDateFirstReported().y << "-"
         << item.getDateFirstReported().m << "-"
         << item.getDateFirstReported().d << endl;
}

void printOpenBugs(const char* productName, Date start, Date end) {
    fstream &dbFile = DatabaseRecord::getFile();
    ChangeItem item;
    DatabaseRecord::seekToBeginning();
    while (item.readRecord(dbFile)) {
        if (strcmp(item.getProductName(), productName) == 0) {
            Date date = item.getDateFirstReported();
            if (date.y >= start.y && date.y <= end.y &&
                date.m >= start.m && date.m <= end.m &&
                date.d >= start.d && date.d <= end.d && item.getStatus() != 3) { // Assuming 3 is the status code for closed bugs
                printChangeItem(item);
            }
        }
    }
}

void printStatusReport(Date start, Date end) {
    fstream &dbFile = DatabaseRecord::getFile();
    ChangeItem item;
    DatabaseRecord::seekToBeginning();
    while (item.readRecord(dbFile)) {
        Date date = item.getDateFirstReported();
        if (date.y >= start.y && date.y <= end.y &&
            date.m >= start.m && date.m <= end.m &&
            date.d >= start.d && date.d <= end.d) {
            printChangeItem(item);
        }
    }
}
