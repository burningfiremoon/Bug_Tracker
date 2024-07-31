#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 14-July-2024 - Created by Tanvir
Initial creation and setup of ChangeRequest class
2.0 - 17-July-2024 - Modified by Charles
3.0 - 26-July-2024 - Modified by Anthony
4.0 - 29 July-2024 - Modified by Anthony
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    ChangeRequest.h

    This header file contains the definition of the ChangeRequest class, which represents a change request record.
    The ChangeRequest class inherits from the DatabaseRecord class and encapsulates details such as change ID,
    requester name, description, status, priority, and the date first reported. The purpose of this class is to
    provide a cohesive representation of a change request and manage its read and write operations to a file.
    The attributes and methods are placed together to provide high cohesion and facilitate easy management of
    change request records.

    Includes:
    - ChangeRequest constructors and destructor
    - Getter and setter methods for various attributes
    - Methods to read and write records from/to a file
    - Static methods to update specific fields in a change request record
*/

#include "DatabaseRecord.h"
#include "StatusConstants.h" // Include shared status constants
#include "ProductRelease.h"

//-------------------------------------
// Class Definition
//-------------------------------------

class ChangeRequest : public DatabaseRecord {
public:
    //-------------------------------------
    // Constructors and Destructor
    //-------------------------------------
    /*
        ChangeRequest(const char* changeID)
        - Purpose: Initialize a ChangeRequest object with a given change ID.
        - Parameters:
            - const char* changeID (in): The change ID to initialize the ChangeRequest with.
    */
    ChangeRequest(const char* changeID);

    /*
        ChangeRequest(const ChangeRequest& data)
        - Purpose: Copy constructor to create a copy of an existing ChangeRequest object.
        - Parameters:
            - const ChangeRequest& data (in): The ChangeRequest object to copy.
    */
    ChangeRequest(const ChangeRequest& data);

    /*
        ChangeRequest()
        - Purpose: Default constructor to initialize a blank ChangeRequest object.
        - Parameters:
            - None
    */
    ChangeRequest();

    /*
        ~ChangeRequest()
        - Purpose: Destructor to clean up resources used by the ChangeRequest object.
    */
    ~ChangeRequest() override;

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
        void setStatus(const char* status)
        - Purpose: Set the status for the ChangeRequest.
        - Parameters:
            - const char* status (in): The status to set.
    */
    void setStatus(const char* status);

    /*
        const char* getStatus() const
        - Purpose: Get the status of the ChangeRequest.
        - Returns: const char* (out): The status of the ChangeRequest.
    */
    const char* getStatus() const;

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
        void setDateFirstReported(Date date)
        - Purpose: Set the date first reported for the ChangeRequest.
        - Parameters:
            - Date date (in): The date first reported to set.
    */
    void setDateFirstReported(Date date);

    /*
        Date getDateFirstReported() const
        - Purpose: Get the date first reported of the ChangeRequest.
        - Returns: Date (out): The date first reported of the ChangeRequest.
    */
    Date getDateFirstReported() const;

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

    //-------------------------------------
    // Static Methods for Updating Records
    //-------------------------------------
    /*
        static bool updStatus(const char* id, const char* newStatus)
        - Purpose: Update the status of a ChangeRequest record with the given ID.
        - Parameters:
            - const char* id (in): The ID of the ChangeRequest record to update.
            - const char* newStatus (in): The new status to set.
        - Returns: bool (out): True if the status is updated successfully, false otherwise.
    */
    static bool updStatus(const char* id, const char* newStatus);

    /*
        static bool updDescription(const char* id, const char* newDescription)
        - Purpose: Update the description of a ChangeRequest record with the given ID.
        - Parameters:
            - const char* id (in): The ID of the ChangeRequest record to update.
            - const char* newDescription (in): The new description to set.
        - Returns: bool (out): True if the description is updated successfully, false otherwise.
    */
    static bool updDescription(const char* id, const char* newDescription);

private:
    //-------------------------------------
    // Member Variables
    //-------------------------------------
    char changeID[7]; // 6 characters plus null terminator
    char requesterName[31]; // 30 characters plus null terminator
    char description[51]; // 50 characters plus null terminator
    char status[StatusStringLength + 1]; // Fixed-length status C-string
    int priority;
    Date dateFirstReported;

    static const int recordSize;
};

#endif // CHANGEREQUEST_H
