//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 15-July-2024 - Created by Tanvir
Initial creation and setup of ChangeRequest class
2.0 - 16-July-2024 - Modified by Anthony
2.1 - 18-July-2024 - Modified by Skyler
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    ChangeRequest.h

    This header file contains the definition of the ChangeRequest class, which represents a change request record.
    The ChangeRequest class inherits from the DatabaseRecord class and encapsulates details such as change ID, 
    requester name, description, reported date, priority, and state. The purpose of this class is to provide a cohesive 
    representation of a change request and manage its read and write operations to a file. The attributes and methods 
    are placed together to provide high cohesion and facilitate easy management of change request records.

    Includes:
    - ChangeRequest constructors and destructor
    - Getter and setter methods for various attributes
    - Methods to read and write records from/to a file
*/

#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include "DatabaseRecord.h"

//-------------------------------------
// Enum Definitions
//-------------------------------------
enum Status { REPORTED, IN_PROGRESS, DONE, CANCELLED };

//-------------------------------------
// Class Definition
//-------------------------------------

class ChangeRequest : public DatabaseRecord {
public:
    //-------------------------------------
    // Constructors and Destructor
    //-------------------------------------
    /*
        ChangeRequest(const char* changeID, const char* requesterName)
        - Purpose: Initialize a ChangeRequest object with a given change ID and requester name.
        - Parameters:
            - const char* changeID (in): The change ID to initialize the ChangeRequest with.
            - const char* requesterName (in): The requester name to initialize the ChangeRequest with.
    */
    ChangeRequest(const char* changeID, const char* requesterName);

    /*
        ChangeRequest(const ChangeRequest& data)
        - Purpose: Copy constructor to create a copy of an existing ChangeRequest object.
        - Parameters:
            - const ChangeRequest& data (in): The ChangeRequest object to copy.
    */
    ChangeRequest(const ChangeRequest& data);

    /*
        ~ChangeRequest()
        - Purpose: Destructor to clean up resources used by the ChangeRequest object.
    */
    ~ChangeRequest();

    //-------------------------------------
    // Setters and Getters
    //-------------------------------------
    /*
        void setChangeID(const char* changeID)
        - Purpose: Set the change ID for the ChangeRequest.
        - Parameters:
            - const char* changeID (in): The change ID to set.
    */
    void setChangeID(const char* changeID);

    /*
        const char* getChangeID() const
        - Purpose: Get the change ID of the ChangeRequest.
        - Returns: const char* (out): The change ID of the ChangeRequest.
    */
    const char* getChangeID() const;

    /*
        void setRequesterName(const char* requesterName)
        - Purpose: Set the requester name for the ChangeRequest.
        - Parameters:
            - const char* requesterName (in): The requester name to set.
    */
    void setRequesterName(const char* requesterName);

    /*
        const char* getRequesterName() const
        - Purpose: Get the requester name of the ChangeRequest.
        - Returns: const char* (out): The requester name of the ChangeRequest.
    */
    const char* getRequesterName() const;

    /*
        void setDescription(const char* description)
        - Purpose: Set the description for the ChangeRequest.
        - Parameters:
            - const char* description (in): The description to set.
    */
    void setDescription(const char* description);

    /*
        const char* getDescription() const
        - Purpose: Get the description of the ChangeRequest.
        - Returns: const char* (out): The description of the ChangeRequest.
    */
    const char* getDescription() const;

    /*
        void setReportedDate(Date date)
        - Purpose: Set the reported date for the ChangeRequest.
        - Parameters:
            - Date date (in): The reported date to set.
    */
    void setReportedDate(Date date);

    /*
        Date getReportedDate() const
        - Purpose: Get the reported date of the ChangeRequest.
        - Returns: Date (out): The reported date of the ChangeRequest.
    */
    Date getReportedDate() const;

    /*
        void setPriority(int priority)
        - Purpose: Set the priority for the ChangeRequest.
        - Parameters:
            - int priority (in): The priority to set.
    */
    void setPriority(int priority);

    /*
        int getPriority() const
        - Purpose: Get the priority of the ChangeRequest.
        - Returns: int (out): The priority of the ChangeRequest.
    */
    int getPriority() const;

    /*
        void setState(Status state)
        - Purpose: Set the state for the ChangeRequest.
        - Parameters:
            - Status state (in): The state to set.
    */
    void setState(Status state);

    /*
        Status getState() const
        - Purpose: Get the state of the ChangeRequest.
        - Returns: Status (out): The state of the ChangeRequest.
    */
    Status getState() const;

    //-------------------------------------
    // File Operations
    //-------------------------------------
    /*
        bool writeRecord(fstream &dbFile) const override
        - Purpose: Write the ChangeRequest record to the given file stream.
        - Parameters:
            - fstream &dbFile (in/out): The file stream to write the record to.
        - Returns: bool (out): True if the record is written successfully, false otherwise.
    */
    bool writeRecord(fstream &dbFile) const override;

    /*
        bool readRecord(fstream &dbFile) override
        - Purpose: Read a ChangeRequest record from the given file stream.
        - Parameters:
            - fstream &dbFile (in/out): The file stream to read the record from.
        - Returns: bool (out): True if the record is read successfully, false otherwise.
    */
    bool readRecord(fstream &dbFile) override;

    /*
        int getRecordSize() const override
        - Purpose: Get the size of the ChangeRequest record.
        - Returns: int (out): The size of the ChangeRequest record.
    */
    int getRecordSize() const override;

    /*
        void readFromBuffer(const char* buffer) override
        - Purpose: Read the ChangeRequest record from a buffer.
        - Parameters:
            - const char* buffer (in): The buffer to read the record from.
    */
    void readFromBuffer(const char* buffer) override;

private:
    //-------------------------------------
    // Member Variables
    //-------------------------------------
    char changeID[7]; // 6 characters plus null terminator
    char requesterName[31]; // 30 characters plus null terminator
    char description[31]; // 30 characters plus null terminator
    Date reportedDate;
    int priority;
    Status state;

    static const int recordSize;
};

#endif // CHANGEREQUEST_H
