#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include "ChangeRequest.h"
#include "User.h"

/* to compile the databaserecord, change request, user, and this file do the following*/
/* g++ -o test testChangeReqUserandDatabaseRecord.cpp ChangeRequest.cpp User.cpp DatabaseRecord.cpp
./test */

void testChangeRequest() {
    Date reportedDate = {2024, 7, 17};
    ChangeRequest change("123456", "TestUser");

    // Set the reportedDate to the expected value
    change.setReportedDate(reportedDate);

    // Debugging output
    std::cout << "Change ID after construction: " << change.getChangeID() << std::endl;
    std::cout << "Reported Date after setting: " << change.getReportedDate().y << "-" << change.getReportedDate().m << "-" << change.getReportedDate().d << std::endl;

    // Test constructor and getters
    assert(strcmp(change.getChangeID(), "123456") == 0);
    assert(strcmp(change.getRequesterName(), "TestUser") == 0);
    assert(change.getReportedDate().y == reportedDate.y);
    assert(change.getReportedDate().m == reportedDate.m);
    assert(change.getReportedDate().d == reportedDate.d);
    assert(change.getState() == REPORTED);

    // Test setting and getting description
    change.setDescription("Fix bug in code");
    assert(strcmp(change.getDescription(), "Fix bug in code") == 0);

    // Test setting and getting priority
    change.setPriority(3);
    assert(change.getPriority() == 3);

    // Test setting and getting state
    change.setState(DONE);
    assert(change.getState() == DONE);

    // Test writing and reading from file
    std::fstream file("test_change_request.dat", std::ios::out | std::ios::binary);
    change.writeRecord(file);
    file.close();

    ChangeRequest readChange("000000", "DummyUser");
    file.open("test_change_request.dat", std::ios::in | std::ios::binary);
    readChange.readRecord(file);
    file.close();

    // Debugging output
    std::cout << "Change ID after reading from file: " << readChange.getChangeID() << std::endl;
    std::cout << "Reported Date after reading from file: " << readChange.getReportedDate().y << "-" << readChange.getReportedDate().m << "-" << readChange.getReportedDate().d << std::endl;

    assert(strcmp(readChange.getChangeID(), "123456") == 0);
    assert(strcmp(readChange.getRequesterName(), "TestUser") == 0);
    assert(strcmp(readChange.getDescription(), "Fix bug in code") == 0);
    assert(readChange.getPriority() == 3);
    assert(readChange.getState() == DONE);

    assert(readChange.getReportedDate().y == reportedDate.y);
    assert(readChange.getReportedDate().m == reportedDate.m);
    assert(readChange.getReportedDate().d == reportedDate.d);

    // Clean up test file
    std::remove("test_change_request.dat");
}

void testUser() {
    User user("TestUser");

    // Test constructor and getters
    assert(strcmp(user.getRequesterName(), "TestUser") == 0);
    assert(strcmp(user.getPhone(), "") == 0);
    assert(strcmp(user.getEmail(), "") == 0);
    assert(strcmp(user.getAddress(), "") == 0);

    // Test setting and getting phone
    user.setPhone("1234567890");
    assert(strcmp(user.getPhone(), "1234567890") == 0);

    // Test setting and getting email
    user.setEmail("test@example.com");
    assert(strcmp(user.getEmail(), "test@example.com") == 0);

    // Test setting and getting address
    user.setAddress("123 Test St");
    assert(strcmp(user.getAddress(), "123 Test St") == 0);

    // Test writing and reading from file
    std::fstream file("test_user.dat", std::ios::out | std::ios::binary);
    user.writeRecord(file);
    file.close();

    User readUser("DummyUser");
    file.open("test_user.dat", std::ios::in | std::ios::binary);
    readUser.readRecord(file);
    file.close();

    assert(strcmp(readUser.getRequesterName(), "TestUser") == 0);
    assert(strcmp(readUser.getPhone(), "1234567890") == 0);
    assert(strcmp(readUser.getEmail(), "test@example.com") == 0);
    assert(strcmp(readUser.getAddress(), "123 Test St") == 0);

    // Clean up test file
    std::remove("test_user.dat");

    // Output the user to verify the << operator
    std::cout << readUser << std::endl;
}

int main() {
    testChangeRequest();
    testUser();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
