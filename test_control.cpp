#include <iostream>
#include <cassert>
#include "control.h"
#include "User.h"
#include "DatabaseRecord.h"

using namespace std;

/*
 g++ -std=c++11 -o test_control test_control.cpp control.cpp ChangeItem.cpp ChangeRequest.cpp User.cpp DatabaseRecord.cpp print.cpp ProductRelease.cpp -I.
./test_control

 */

void testStopStartAccepting() {
    // Test if these functions are callable (currently placeholders)
    StopAccepting();
    StartAccepting();
    // Since these are placeholders, we don't have assertions here
}

void testUpdateUserName() {
    const char oldName[31] = "OldName";
    const char newName[31] = "NewName";

    // Initialize user for testing
    assert(Init_User(oldName, "1234567890", "old@example.com"));

    // Verify user exists before update
    assert(CheckUserExists(oldName));

    // Update user name
    UpdateUserName(oldName, newName);

    // Verify user name has been updated
    User user(newName);
    fstream &dbFile = DatabaseRecord::getFile();
    if (user.readRecord(dbFile)) {
        assert(strcmp(user.getRequesterName(), newName) == 0);
    } else {
        cerr << "Error: Failed to read updated user record from database." << endl;
    }

    DatabaseRecord::closeFile();
}

void testCheckUserExists() {
    const char userName[31] = "TestUser";
    
    // Ensure the user is in the database for testing
    assert(Init_User(userName, "9876543210", "test@example.com"));

    // Check if the user exists
    bool exists = CheckUserExists(userName);
    if (exists) {
        cout << "User " << userName << " exists in the database." << endl;
    } else {
        cerr << "User " << userName << " does not exist in the database." << endl;
    }
    assert(exists == true);

    // Test with a non-existing user
    const char nonExistentUser[31] = "NonExistent";
    assert(CheckUserExists(nonExistentUser) == false);
}

int main() {
    // Run tests
    testStopStartAccepting();
    testUpdateUserName();
    testCheckUserExists();

    cout << "All control tests passed!" << endl;
    return 0;
}
