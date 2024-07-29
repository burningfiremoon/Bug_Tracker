#include <iostream>
#include "DatabaseRecord.h"
#include "ChangeItem.h"

using namespace std;

/*  This is a test for DatabaseRecord and ChangeItem */
/* To test this use the following commands */
/*
g++ -o testDBCI DatabaseRecord.cpp ChangeItem.cpp testDBCI.cpp
./testDBCI
 */

void testDatabaseRecord() {
    cout << "Testing DatabaseRecord Class..." << endl;
    
    ChangeItem record("TEST01");
    cout << "Generated Record ID: Converted ID " << record.getID() << endl;

    DatabaseRecord::openFile("testDB.txt");
    cout << "Database file testDB.txt opened successfully." << endl;

    DatabaseRecord::closeFile();
    DatabaseRecord::openFile("testDB.txt");
    cout << "Database file testDB.txt opened successfully." << endl;

    DatabaseRecord::closeFile();
    cout << "Finding record with ID 'TEST01': " 
         << (DatabaseRecord::findRecord("TEST01", record) ? "Found" : "Not Found") << endl;

    DatabaseRecord::closeFile();
    cout << "Deleting record with ID 'TEST01': " 
         << (DatabaseRecord::deleteRecord("TEST01") ? "Deleted" : "Not Found") << endl;

    DatabaseRecord::closeFile();
    cout << "DatabaseRecord Class Testing Completed." << endl;
}

void testChangeItem() {
    cout << "Testing ChangeItem Class..." << endl;
    
    // First ChangeItem
    ChangeItem item1("CHG001");
    item1.setProductName("ProductA");
    item1.setChangeDescription("DescriptionA");
    item1.setStatus(1);
    item1.setPriority(2);
    ReleaseID releaseID1 = {"REL001"};
    item1.setReleaseID(releaseID1);
    Date date1 = {2024, 7, 28};
    item1.setDateFirstReported(date1);

    cout << "Change ID: " << item1.getChangeID() << endl;
    cout << "Product Name: " << item1.getProductName() << endl;
    cout << "Change Description: " << item1.getChangeDescription() << endl;
    cout << "Status: " << item1.getStatus() << endl;
    cout << "Priority: " << item1.getPriority() << endl;
    cout << "Release ID: " << item1.getReleaseID().id << endl;
    cout << "Date First Reported: " << item1.getDateFirstReported().y << "-" 
         << item1.getDateFirstReported().m << "-" << item1.getDateFirstReported().d << endl;

    // Second ChangeItem
    ChangeItem item2("CHG002");
    item2.setProductName("ProductB");
    item2.setChangeDescription("DescriptionB");
    item2.setStatus(3);
    item2.setPriority(4);
    ReleaseID releaseID2 = {"REL002"};
    item2.setReleaseID(releaseID2);
    Date date2 = {2024, 7, 29};
    item2.setDateFirstReported(date2);

    cout << "Change ID: " << item2.getChangeID() << endl;
    cout << "Product Name: " << item2.getProductName() << endl;
    cout << "Change Description: " << item2.getChangeDescription() << endl;
    cout << "Status: " << item2.getStatus() << endl;
    cout << "Priority: " << item2.getPriority() << endl;
    cout << "Release ID: " << item2.getReleaseID().id << endl;
    cout << "Date First Reported: " << item2.getDateFirstReported().y << "-" 
         << item2.getDateFirstReported().m << "-" << item2.getDateFirstReported().d << endl;

    DatabaseRecord::openFile("testDB.txt");
    cout << "Database file testDB.txt opened successfully." << endl;

    item1.writeRecord(DatabaseRecord::getFile());
    item2.writeRecord(DatabaseRecord::getFile());
    DatabaseRecord::closeFile();

    DatabaseRecord::openFile("testDB.txt");
    cout << "Returning database file stream." << endl;

    ChangeItem readItem("CHG001");
    readItem.readRecord(DatabaseRecord::getFile());
    cout << "Read Change ID: " << readItem.getChangeID() << endl;
    cout << "Read Product Name: " << readItem.getProductName() << endl;
    cout << "Read Change Description: " << readItem.getChangeDescription() << endl;
    cout << "Read Status: " << readItem.getStatus() << endl;
    cout << "Read Priority: " << readItem.getPriority() << endl;
    cout << "Read Release ID: " << readItem.getReleaseID().id << endl;
    cout << "Read Date First Reported: " << readItem.getDateFirstReported().y << "-" 
         << readItem.getDateFirstReported().m << "-" << readItem.getDateFirstReported().d << endl;

    DatabaseRecord::closeFile();
    cout << "ChangeItem Class Testing Completed." << endl;
}

void testUpdateMethods() {
    cout << "Testing Update Methods in ChangeItem Class..." << endl;
    
    ChangeItem::updStatus("CHG002", 5);
    ChangeItem::updPriority("CHG002", 6);

    DatabaseRecord::closeFile();
    DatabaseRecord::openFile("testDB.txt");

    cout << "Database file testDB.txt opened successfully." << endl;
    fstream& dbFile = DatabaseRecord::getFile();
    DatabaseRecord::seekToBeginning();

    string line;
    while (getline(dbFile, line)) {
        ChangeItem item("TEMP");  // Temporary ID for reading from buffer
        item.readFromBuffer(line.c_str());
        cout << "Buffer read: " << line << endl;  // Debug output
        cout << "Parsed changeID: " << item.getChangeID() 
             << ", productName: " << item.getProductName() 
             << ", changeDescription: " << item.getChangeDescription()
             << ", status: " << item.getStatus() 
             << ", priority: " << item.getPriority() 
             << ", releaseID: " << item.getReleaseID().id 
             << ", dateFirstReported: " << item.getDateFirstReported().y 
             << "-" << item.getDateFirstReported().m 
             << "-" << item.getDateFirstReported().d << endl;  // Debug output
    }

    DatabaseRecord::closeFile();
    cout << "Update Methods Testing Completed." << endl;
}

int main() {
    testDatabaseRecord();
    testChangeItem();
    testUpdateMethods();
    return 0;
}
