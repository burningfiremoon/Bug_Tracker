#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include "ChangeRequest.h"
#include "User.h"

/* g++ -o testChangeReqUserandDatabaseRecord testChangeReqUserandDatabaseRecord.cpp ChangeRequest.cpp User.cpp DatabaseRecord.cpp

 ./testChangeReqUserandDatabaseRecord

 */

// Function to trim trailing spaces from a C-style string
std::string trim(const char* str) {
    std::string result(str);
    result.erase(result.find_last_not_of(' ') + 1);
    return result;
}

void testChangeRequest() {
    // Create a ChangeRequest object with a given ID
    ChangeRequest change("123456");

    // Set other fields using public methods
    change.setRequesterName("TestUser"); // Assuming 'Requester' is the intended name part
    Date reportedDate = {2024, 7, 30};
    change.setDateFirstReported(reportedDate);
    change.setDescription("Fix bug in code"); // Assuming 'Description' is the correct attribute
    change.setPriority(5);
    change.setStatus(StatusInProgress);

    // Assert checks for each field
    assert(strcmp(change.getChangeID(), "123456") == 0); // Assuming 'ChangeID' is the correct method
    assert(trim(change.getRequesterName()) == "TestUser"); // Correct method name for requester name
    assert(change.getDateFirstReported().y == reportedDate.y);
    assert(change.getDateFirstReported().m == reportedDate.m);
    assert(change.getDateFirstReported().d == reportedDate.d);
    assert(trim(change.getDescription()) == "Fix bug in code"); // Correct method name for description
    assert(change.getPriority() == 5);
    assert(strcmp(change.getStatus(), StatusInProgress) == 0);

    // Print values for verification
    std::cout << "Change ID: " << change.getChangeID() << std::endl; // Correct method name for ID
    std::cout << "Requester Name: " << change.getRequesterName() << std::endl; // Correct method name
    std::cout << "Reported Date: " << change.getDateFirstReported().y << "-"
              << change.getDateFirstReported().m << "-"
              << change.getDateFirstReported().d << std::endl;
    std::cout << "Description: " << change.getDescription() << std::endl; // Correct method name
    std::cout << "Priority: " << change.getPriority() << std::endl;
    std::cout << "Status: " << change.getStatus() << std::endl;

    // Test setting status to Done and check
    change.setStatus(StatusDone);
    assert(strcmp(change.getStatus(), StatusDone) == 0);

    // Additional test cases for other setters and getters can be added here
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
