#include "ChangeItem.h"
#include <iostream>
#include <cassert>
/* g++ -o testDBCI DatabaseRecord.cpp ChangeItem.cpp testDBCI.cpp */
/* ./testDBCI */
using namespace std;

void testChangeItem() {
    // Create a ChangeItem with specific attributes
    ChangeItem item1("CHG001");
    item1.setProductName("Product A");
    item1.setChangeDescription("Initial description");
    item1.setStatus(StatusInProgress);
    item1.setPriority(5);
    ReleaseID rid = {"R001"};
    item1.setReleaseID(rid);
    Date dateFirstReported = {2023, 7, 20};
    item1.setDateFirstReported(dateFirstReported);

    // Expected values
    const char* expectedDescription = "Initial description           "; // 30 characters including padding
    int expectedDescriptionLength = 30;

    // Output the actual values for debugging
    std::cout << "Change ID: " << item1.getChangeID() << std::endl;
    std::cout << "Product Name: " << item1.getProductName() << std::endl;

    // Print ASCII values of the actual description
    std::cout << "Change Description ASCII Values: ";
    for (size_t i = 0; i < strlen(item1.getChangeDescription()); ++i) {
        std::cout << static_cast<int>(item1.getChangeDescription()[i]) << " ";
    }
    std::cout << std::endl;

    std::cout << "Actual Description Length Including Padding: " << strlen(item1.getChangeDescription()) << std::endl;
    std::cout << "Change Description: '" << item1.getChangeDescription() << "'" << std::endl;
    std::cout << "Status: " << item1.getStatus() << std::endl;
    std::cout << "Priority: " << item1.getPriority() << std::endl;
    std::cout << "Release ID: " << item1.getReleaseID().id << std::endl;
    std::cout << "Date First Reported: " << item1.getDateFirstReported().y << "-"
              << item1.getDateFirstReported().m << "-"
              << item1.getDateFirstReported().d << std::endl;

    // Expected output
    std::cout << "Expected Description: '" << expectedDescription << "'" << std::endl;
    std::cout << "Expected Description Length Including Padding: " << expectedDescriptionLength << std::endl;

    // Check for length mismatch
    if (strlen(item1.getChangeDescription()) != expectedDescriptionLength) {
        std::cout << "Length mismatch! Actual: " << strlen(item1.getChangeDescription())
                  << ", Expected: " << expectedDescriptionLength << std::endl;
    }

    // Compare character by character if there's a mismatch
    for (int i = 0; i < expectedDescriptionLength; ++i) {
        if (item1.getChangeDescription()[i] != expectedDescription[i]) {
            std::cout << "Difference at position " << i
                      << ": Actual(" << static_cast<int>(item1.getChangeDescription()[i]) << "), "
                      << "Expected(" << static_cast<int>(expectedDescription[i]) << ")" << std::endl;
            break;
        }
    }

    // Assertion to check if the description matches the expected description
    assert(strcmp(item1.getChangeDescription(), expectedDescription) == 0);
}

void testUpdateMethods() {
    // Open the database file
    DatabaseRecord::openFile("testDB.txt");

    // Create a ChangeItem and write to the file
    ChangeItem item2("CHG002");
    item2.setProductName("Product B");
    item2.setChangeDescription("Second description");
    item2.setStatus(StatusReported);
    item2.setPriority(3);
    ReleaseID rid2 = {"R002"};
    item2.setReleaseID(rid2);
    Date dateReported2 = {2023, 8, 5};
    item2.setDateFirstReported(dateReported2);
    item2.writeRecord(DatabaseRecord::getFile());

    // Update the status of the item in the database file
    const char* updatedStatus = StatusDone;
    bool statusUpdated = ChangeItem::updStatus("CHG002", updatedStatus);

    // Output the status of the update operation
    if (statusUpdated) {
        std::cout << "Status updated successfully for CHG002." << std::endl;
    } else {
        std::cout << "Status update failed for CHG002." << std::endl;
    }

    // Re-read the item from the file to check the update
    DatabaseRecord::seekToBeginning(); // Reset file pointer to the beginning
    item2.readRecord(DatabaseRecord::getFile());

    // Output the actual status read from the file
    std::cout << "Updated Status from file: '" << item2.getStatus() << "'" << std::endl;

    // Assertion to check if the status was updated correctly
    assert(strcmp(item2.getStatus(), StatusDone) == 0);

    // Close the database file
    DatabaseRecord::closeFile();
}


int main() {
    // Run the tests
    testChangeItem();
    testUpdateMethods();

    cout << "All tests passed!" << endl;
    return 0;
}
