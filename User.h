//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 15-July-2024 - Created by Tanvir
Initial creation and setup of User class
2.0 - 17-July-2024 - Modified by Skyler
Added detailed comments and explanations
2.1 - 18-July-2024 - Modified by Skyler
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    User.h

    This header file contains the definition of the User class, which represents a user record.
    The User class inherits from the DatabaseRecord class and encapsulates details such as requester name, 
    phone number, email, and address. The purpose of this class is to provide a cohesive representation 
    of a user and manage its read and write operations to a file. The attributes and methods are placed 
    together to provide high cohesion and facilitate easy management of user records.

    Includes:
    - User constructors and destructor
    - Getter and setter methods for various attributes
    - Methods to read and write records from/to a file
    - Operator overload for output stream
*/

#ifndef USER_H
#define USER_H

#include "DatabaseRecord.h"

//-------------------------------------
// Class Definition
//-------------------------------------

class User : public DatabaseRecord {
public:
    //-------------------------------------
    // Constructors and Destructor
    //-------------------------------------
    /*
        User(const char* requesterName)
        - Purpose: Constructor to initialize a User object with a given requester name.
        - Parameters:
            - const char* requesterName (in): The requester name to initialize the User with.
    */
    User(const char* requesterName);

    /*
        User(const User& data)
        - Purpose: Copy constructor to create a copy of an existing User object.
        - Parameters:
            - const User& data (in): The User object to copy.
    */
    User(const User& data);

    //-------------------------------------
    // Setters and Getters
    //-------------------------------------
    /*
        void setRequesterName(const char* requesterName)
        - Purpose: Set the requester name for the User.
        - Parameters:
            - const char* requesterName (in): The requester name to set.
    */
    void setRequesterName(const char* requesterName);

    /*
        const char* getRequesterName() const
        - Purpose: Get the requester name of the User.
        - Returns: const char* (out): The requester name of the User.
    */
    const char* getRequesterName() const;

    /*
        void setPhone(const char* phone)
        - Purpose: Set the phone number for the User.
        - Parameters:
            - const char* phone (in): The phone number to set.
    */
    void setPhone(const char* phone);

    /*
        const char* getPhone() const
        - Purpose: Get the phone number of the User.
        - Returns: const char* (out): The phone number of the User.
    */
    const char* getPhone() const;

    /*
        void setEmail(const char* email)
        - Purpose: Set the email address for the User.
        - Parameters:
            - const char* email (in): The email address to set.
    */
    void setEmail(const char* email);

    /*
        const char* getEmail() const
        - Purpose: Get the email address of the User.
        - Returns: const char* (out): The email address of the User.
    */
    const char* getEmail() const;

    /*
        void setAddress(const char* address)
        - Purpose: Set the address for the User.
        - Parameters:
            - const char* address (in): The address to set.
    */
    void setAddress(const char* address);

    /*
        const char* getAddress() const
        - Purpose: Get the address of the User.
        - Returns: const char* (out): The address of the User.
    */
    const char* getAddress() const;

    //-------------------------------------
    // File Operations
    //-------------------------------------
    /*
        bool writeRecord(fstream &dbFile) const override
        - Purpose: Write the User record to the given file stream.
        - Parameters:
            - fstream &dbFile (in/out): The file stream to write the record to.
        - Returns: bool (out): True if the record is written successfully, false otherwise.
    */
    bool writeRecord(fstream &dbFile) const override;

    /*
        bool readRecord(fstream &dbFile) override
        - Purpose: Read a User record from the given file stream.
        - Parameters:
            - fstream &dbFile (in/out): The file stream to read the record from.
        - Returns: bool (out): True if the record is read successfully, false otherwise.
    */
    bool readRecord(fstream &dbFile) override;

    /*
        int getRecordSize() const override
        - Purpose: Get the size of the User record.
        - Returns: int (out): The size of the User record.
    */
    int getRecordSize() const override;

    /*
        void readFromBuffer(const char* buffer) override
        - Purpose: Read the User record from a buffer.
        - Parameters:
            - const char* buffer (in): The buffer to read the record from.
    */
    void readFromBuffer(const char* buffer) override;

    //-------------------------------------
    // Friend Functions
    //-------------------------------------
    /*
        ostream& operator<<(ostream& os, const User& user)
        - Purpose: Output stream operator to print the User details.
        - Parameters:
            - ostream& os (out): The output stream.
            - const User& user (in): The User object to print.
        - Returns: ostream& (out): The output stream with the User details.
    */
    friend ostream& operator<<(ostream& os, const User& user);

private:
    //-------------------------------------
    // Member Variables
    //-------------------------------------
    char requesterName[31]; // 30 characters plus null terminator
    char phone[12]; // 11 characters plus null terminator
    char email[25]; // 24 characters plus null terminator
    char address[31]; // 30 characters plus null terminator

    static const int recordSize;
};

#endif // USER_H
