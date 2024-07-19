//-------------------------------------
// Revision History
//-------------------------------------
/*
1.0 - 14-July-2024 - Created by Charles
Initial creation and setup of ProductRelease class
2.0 - 16-July-2024 - Modified by Anthony
2.1 - 18-July-2024 - Modified by Skyler
*/

//-------------------------------------
// Explanation
//-------------------------------------
/*
    ProductRelease.h

    This header file contains the definition of the ProductRelease class, which represents a product release record.
    The ProductRelease class inherits from the DatabaseRecord class and encapsulates details such as product name, 
    release ID, and release date. The purpose of this class is to provide a cohesive representation of a product 
    release and manage its read and write operations to a file. The attributes and methods are placed together to 
    provide high cohesion and facilitate easy management of product release records.

    Includes:
    - ProductRelease constructors and destructor
    - Getter and setter methods for various attributes
    - Methods to read and write records from/to a file
*/

#ifndef PRODUCTRELEASE_H
#define PRODUCTRELEASE_H

#include "DatabaseRecord.h"

//-------------------------------------
// Class Definition
//-------------------------------------

class ProductRelease : public DatabaseRecord {
public:
    //-------------------------------------
    // Constructors and Destructor
    //-------------------------------------
    /*
        ProductRelease()
        - Purpose: Default constructor to initialize a ProductRelease object with default values.
    */
    ProductRelease();

    /*
        ProductRelease(const char* name, ReleaseID id, Date date)
        - Purpose: Parameterized constructor to initialize a ProductRelease object with given values.
        - Parameters:
            - const char* name (in): The name of the product.
            - ReleaseID id (in): The release ID of the product.
            - Date date (in): The release date of the product.
    */
    ProductRelease(const char* name, ReleaseID id, Date date);

    //-------------------------------------
    // Setters and Getters
    //-------------------------------------
    /*
        void setProductName(const char* name)
        - Purpose: Set the product name for the ProductRelease.
        - Parameters:
            - const char* name (in): The product name to set.
    */
    void setProductName(const char* name);

    /*
        const char* getProductName() const
        - Purpose: Get the product name of the ProductRelease.
        - Returns: const char* (out): The product name of the ProductRelease.
    */
    const char* getProductName() const;

    /*
        void setReleaseID(ReleaseID id)
        - Purpose: Set the release ID for the ProductRelease.
        - Parameters:
            - ReleaseID id (in): The release ID to set.
    */
    void setReleaseID(ReleaseID id);

    /*
        ReleaseID getReleaseID() const
        - Purpose: Get the release ID of the ProductRelease.
        - Returns: ReleaseID (out): The release ID of the ProductRelease.
    */
    ReleaseID getReleaseID() const;

    /*
        void setReleaseDate(Date date)
        - Purpose: Set the release date for the ProductRelease.
        - Parameters:
            - Date date (in): The release date to set.
    */
    void setReleaseDate(Date date);

    /*
        Date getReleaseDate() const
        - Purpose: Get the release date of the ProductRelease.
        - Returns: Date (out): The release date of the ProductRelease.
    */
    Date getReleaseDate() const;

    //-------------------------------------
    // File Operations
    //-------------------------------------
    /*
        bool writeRecord(fstream &dbFile) const override
        - Purpose: Write the ProductRelease record to the given file stream.
        - Parameters:
            - fstream &dbFile (in/out): The file stream to write the record to.
        - Returns: bool (out): True if the record is written successfully, false otherwise.
    */
    bool writeRecord(fstream &dbFile) const override;

    /*
        bool readRecord(fstream &dbFile) override
        - Purpose: Read a ProductRelease record from the given file stream.
        - Parameters:
            - fstream &dbFile (in/out): The file stream to read the record from.
        - Returns: bool (out): True if the record is read successfully, false otherwise.
    */
    bool readRecord(fstream &dbFile) override;

    /*
        int getRecordSize() const override
        - Purpose: Get the size of the ProductRelease record.
        - Returns: int (out): The size of the ProductRelease record.
    */
    int getRecordSize() const override;

    /*
        void readFromBuffer(const char* buffer) override
        - Purpose: Read the ProductRelease record from a buffer.
        - Parameters:
            - const char* buffer (in): The buffer to read the record from.
    */
    void readFromBuffer(const char* buffer) override;

private:
    //-------------------------------------
    // Member Variables
    //-------------------------------------
    char productName[31]; // 30 characters plus null terminator
    ReleaseID releaseID;
    Date releaseDate;

    static const int recordSize;
};

#endif // PRODUCTRELEASE_H
