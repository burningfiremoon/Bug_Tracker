//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 14-July-2024 - Created by Tanvir
Initial creation and setup of ChangeItem class
2.0 - 17-July-2024 - Modified by Charles
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    ChangeItem.h

    This header file contains the definition of the ChangeItem class, which represents a change item record.
    The ChangeItem class inherits from the DatabaseRecord class and encapsulates details such as change ID, 
    product name, change description, status, priority, release ID, and the date first reported. The purpose of 
    this class is to provide a cohesive representation of a change item and manage its read and write operations 
    to a file. The attributes and methods are placed together to provide high cohesion and facilitate easy management 
    of change item records.

    Includes:
    - ChangeItem constructors and destructor
    - Getter and setter methods for various attributes
    - Methods to read and write records from/to a file
    - Static methods to update specific fields in a change item record
*/

#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include "DatabaseRecord.h"

//-------------------------------------
// Class Definition
//-------------------------------------

class ChangeItem : public DatabaseRecord {
public:
    //-------------------------------------
    // Constructors and Destructor
    //-------------------------------------
    /*
        ChangeItem(const char* changeID)
        - Purpose: Initialize a ChangeItem object with a given change ID.
        - Parameters:
            - const char* changeID (in): The change ID to initialize the ChangeItem with.
    */
    ChangeItem(const char* changeID);

    /*
        ChangeItem(const ChangeItem& data)
        - Purpose: Copy constructor to create a copy of an existing ChangeItem object.
        - Parameters:
            - const ChangeItem& data (in): The ChangeItem object to copy.
    */
    ChangeItem(const ChangeItem& data);


    void setChangeID(const char* changeID);

    /*
        const char* getChangeID() const
        - Purpose: Get the change ID of the ChangeItem.
        - Returns: const char* (out): The change ID of the ChangeItem.
    */
    const char* getChangeID() const;

    /*
        void setProductName(const char* productName)
        - Purpose: Set the product name for the ChangeItem.
        - Parameters:
            - const char* productName (in): The product name to set.
    */
    void setProductName(const char* productName);

    /*
        const char* getProductName() const
        - Purpose: Get the product name of the ChangeItem.
        - Returns: const char* (out): The product name of the ChangeItem.
    */
    const char* getProductName() const;

    /*
        void setChangeDescription(const char* changeDescription)
        - Purpose: Set the change description for the ChangeItem.
        - Parameters:
            - const char* changeDescription (in): The change description to set.
    */
    void setChangeDescription(const char* changeDescription);

    /*
        const char* getChangeDescription() const
        - Purpose: Get the change description of the ChangeItem.
        - Returns: const char* (out): The change description of the ChangeItem.
    */
    const char* getChangeDescription() const;

    /*
        void setStatus(int status)
        - Purpose: Set the status for the ChangeItem.
        - Parameters:
            - int status (in): The status to set.
    */
    void setStatus(int status);

    /*
        int getStatus() const
        - Purpose: Get the status of the ChangeItem.
        - Returns: int (out): The status of the ChangeItem.
    */
    int getStatus() const;

    /*
        void setPriority(int priority)
        - Purpose: Set the priority for the ChangeItem.
        - Parameters:
            - int priority (in): The priority to set.
    */
    void setPriority(int priority);

    /*
        int getPriority() const
        - Purpose: Get the priority of the ChangeItem.
        - Returns: int (out): The priority of the ChangeItem.
    */
    int getPriority() const;

    /*
        void setReleaseID(ReleaseID releaseID)
        - Purpose: Set the release ID for the ChangeItem.
        - Parameters:
            - ReleaseID releaseID (in): The release ID to set.
    */
    void setReleaseID(ReleaseID releaseID);

    /*
        ReleaseID getReleaseID() const
        - Purpose: Get the release ID of the ChangeItem.
        - Returns: ReleaseID (out): The release ID of the ChangeItem.
    */
    ReleaseID getReleaseID() const;

    /*
        void setDateFirstReported(Date date)
        - Purpose: Set the date first reported for the ChangeItem.
        - Parameters:
            - Date date (in): The date first reported to set.
    */
    void setDateFirstReported(Date date);

    /*
        Date getDateFirstReported() const
        - Purpose: Get the date first reported of the ChangeItem.
        - Returns: Date (out): The date first reported of the ChangeItem.
    */
    Date getDateFirstReported() const;

    //-------------------------------------
    // File Operations
    //-------------------------------------
    /*
        bool writeRecord(fstream &dbFile) const override
        - Purpose: Write the ChangeItem record to the given file stream.
        - Parameters:
            - fstream &dbFile (in/out): The file stream to write the record to.
        - Returns: bool (out): True if the record is written successfully, false otherwise.
    */
    bool writeRecord(fstream &dbFile) const override;

    /*
        bool readRecord(fstream &dbFile) override
        - Purpose: Read a ChangeItem record from the given file stream.
        - Parameters:
            - fstream &dbFile (in/out): The file stream to read the record from.
        - Returns: bool (out): True if the record is read successfully, false otherwise.
    */
    bool readRecord(fstream &dbFile) override;

    /*
        int getRecordSize() const override
        - Purpose: Get the size of the ChangeItem record.
        - Returns: int (out): The size of the ChangeItem record.
    */
    int getRecordSize() const override;

    /*
        void readFromBuffer(const char* buffer) override
        - Purpose: Read the ChangeItem record from a buffer.
        - Parameters:
            - const char* buffer (in): The buffer to read the record from.
    */
    void readFromBuffer(const char* buffer) override;

    //-------------------------------------
    // Static Methods for Updating Records
    //-------------------------------------
    /*
        static bool updStatus(const char* id, int newStatus)
        - Purpose: Update the status of a ChangeItem record with the given ID.
        - Parameters:
            - const char* id (in): The ID of the ChangeItem record to update.
            - int newStatus (in): The new status to set.
        - Returns: bool (out): True if the status is updated successfully, false otherwise.
    */
    static bool updStatus(const char* id, int newStatus);

    /*
        static bool updRelease(const char* id, int newRelease)
        - Purpose: Update the release ID of a ChangeItem record with the given ID.
        - Parameters:
            - const char* id (in): The ID of the ChangeItem record to update.
            - int newRelease (in): The new release ID to set.
        - Returns: bool (out): True if the release ID is updated successfully, false otherwise.
    */
    static bool updRelease(const char* id, int newRelease);

    /*
        static bool updPriority(const char* id, int newPriority)
        - Purpose: Update the priority of a ChangeItem record with the given ID.
        - Parameters:
            - const char* id (in): The ID of the ChangeItem record to update.
            - int newPriority (in): The new priority to set.
        - Returns: bool (out): True if the priority is updated successfully, false otherwise.
    */
    static bool updPriority(const char* id, int newPriority);

    /*
        static bool updDesc(const char* id, const char* newDescription)
        - Purpose: Update the description of a ChangeItem record with the given ID.
        - Parameters:
            - const char* id (in): The ID of the ChangeItem record to update.
            - const char* newDescription (in): The new description to set.
        - Returns: bool (out): True if the description is updated successfully, false otherwise.
    */
    static bool updDesc(const char* id, const char* newDescription);

private:
    //-------------------------------------
    // Member Variables
    //-------------------------------------
    char changeID[7]; // 6 characters plus null terminator
    char productName[31]; // 30 characters plus null terminator
    char changeDescription[31]; // 30 characters plus null terminator
    int status;
    int priority;
    ReleaseID releaseID;
    Date dateFirstReported;

    static const int recordSize;
};

#endif // CHANGEITEM_H
