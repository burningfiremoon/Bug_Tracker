/*
    Revision History:
    1.0 - 03-07-2024 [Date] - Modified by Skyler
    2.0 - 16-07-2024 [Date] - Modified by Anthony

    database.h:
    This header file contains class definitions and function declarations for database operations.
    It includes necessary headers and defines classes and functions to interact with the database.
    The purpose of this header file is to abstract the database interaction, ensuring that the main logic
    of the application remains separate from the database-specific code. This design promotes cohesion by 
    grouping all database-related functionality together.
*/
//-------------------------------------
#ifndef DATABASE_H
#define DATABASE_H

//-------------------------------------
// List of #includes
#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>  
#include <fcntl.h>

using namespace std;


//-------------------------------------
// Base class definition

class DatabaseRecord {
public:
    DatabaseRecord();
    int getID() const;

    virtual ~DatabaseRecord() = default;
    virtual bool writeRecord() const = 0;
    virtual bool readRecord() = 0;
    virtual int getRecordSize() const = 0;
    virtual void readFromBuffer(const char* buffer) = 0;

    static void openFile();
    static void closeFile();
    static bool findRecord(int id, DatabaseRecord& record);
    static bool deleteRecord(int id);
   
protected:
    static fstream dbFile;
    int id;

    static void seekToBeginning();
};

/*
//-------------------------------------
// Derived class definitions

class ChangeRequest : public DatabaseRecord {
public:
    ChangeRequest();
    ChangeRequest(int id, const char* description);
    ~ChangeRequest();

    void setID(int id) override;
    int getID() const override;
    void setDescription(const char* description);
    const char* getDescription() const;

    bool writeRecord() const override;
    bool readRecord() override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

private:
    int id;
    char description[31];

    static const int recordSize = sizeof(int) + 31 * sizeof(char);
};

class User : public DatabaseRecord {
public:
    User();
    User(int id, const char* name);
    ~User();

    void setInfo(const char* name);
    const char* getInfo() const;
    void setID(int id) override;
    int getID() const override;

    bool writeRecord() const override;
    bool readRecord() override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

private:
    int id;
    char name[31];

    static const int recordSize = sizeof(int) + 31 * sizeof(char);
};

class ChangeItem : public DatabaseRecord {
public:
    ChangeItem();
    ChangeItem(int id, const char* productID, const char* description, int status, int priority, const char* requester);
    ~ChangeItem();

    void setID(int id) override;
    int getID() const override;
    void setProductID(const char* productID);
    const char* getProductID() const;
    void setDescription(const char* description);
    const char* getDescription() const;
    void setStatus(int status);
    int getStatus() const;
    void setPriority(int priority);
    int getPriority() const;
    void setRequester(const char* requester);
    const char* getRequester() const;

    bool writeRecord() const override;
    bool readRecord() override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

    static bool updStatus(int id, int newStatus);
    static bool updRelease(int id, int newRelease);
    static bool updPriority(int id, int newPriority);
    static bool updDesc(int id, const char* newDescription);
    static bool showRequester(int id);

private:
    int id;
    char productID[31];
    char description[31];
    int status;
    int priority;
    char requester[31];

    static const int recordSize = sizeof(int) + 31 * sizeof(char) * 3 + sizeof(int) * 2;
};

class ProductRelease : public DatabaseRecord {
public:
    ProductRelease();
    ProductRelease(int id, const char* name, const char* version);
    ~ProductRelease();

    void setID(int id) override;
    int getID() const override;
    void setName(const char* name);
    const char* getName() const;
    void setVersion(const char* version);
    const char* getVersion() const;

    bool writeRecord() const override;
    bool readRecord() override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

    static bool addRelease(const ProductRelease& release);
    static bool addProduct(int id, const char* name);
    static bool showProduct(int id);
    static bool showRelease(int id);

private:
    int id;
    char name[31];
    char version[31];

    static const int recordSize = sizeof(int) + 31 * sizeof(char) * 2;
};
*/

//-------------------------------------
// Derived class definitions
struct Date {
    int y;
    int m;
    int d;
};

class ChangeRequest : public DatabaseRecord {
public:
    ChangeRequest(int changeID, const char* requesterName); //constructor
    ChangeRequest(const ChangeRequest& data); //copy constructor
    ~ChangeRequest();

    void setChangeID(int changeID);
    int getChangeID() const;
    void setRequesterName(const char* requesterName);
    const char* getRequesterName() const;
    void setDescription(const char* description);
    const char* getDescription() const;
    void setReportedDate(Date date);
    const Date getReportedDate() const;
    void setPriority(int priority);
    const int getPriority() const;

    bool writeRecord() const override;
    bool readRecord() override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

private:
    int changeID; //key
    char requesterName[31]; //key
    char description[31];
    Date reportedDate;
    int priority;

    static const int recordSize = sizeof(int) + sizeof(int) + 31 * sizeof(char)+ 31 * sizeof(char) + sizeof(Date) + sizeof(int);
};

class User : public DatabaseRecord {
public:
    User(const char* requesterName); //constructor
    User(const User& data); //copy consructor
    ~User();

    void setRequesterName(const char* requesterName);
    const char* getRequesterName() const;
    void setPhone(int phone);
    const int getPhone() const;
    void setEmail(const char* email);
    const char* getEmail() const;

    bool writeRecord() const override;
    bool readRecord() override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

private:
    char requesterName[31]; //key
    int phone;
    char email[31];

    static const int recordSize = sizeof(int) + 31 * sizeof(char) + sizeof(int) + 31 * sizeof(char);
};

struct ReleaseID {
    int big;
    int med;
    int sml;
}

class ChangeItem : public DatabaseRecord {
public:
    ChangeItem(int changeID);
    ChangeItem(const ChangeItem& data);
    ~ChangeItem();

    void setChangeID(int changeID);
    int getChangeID() const;
    void setProductName(const char* productName);
    const char* getProductName() const;
    void setChangeDescription(const char* changeDescription);
    const char* getChangeDescription() const;
    void setStatus(int status);
    int getStatus() const;
    void setPriority(int priority);
    int getPriority() const;
    void setReleaseID(ReleaseID releaseID);
    ReleaseID getReleaseID() const;
    void setDateFirstReported(Date date);
    Date getDateFirstReported() const;

    bool writeRecord() const override;
    bool readRecord() override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

    static bool updStatus(int id, int newStatus);
    static bool updRelease(int id, int newRelease);
    static bool updPriority(int id, int newPriority);
    static bool updDesc(int id, const char* newDescription);

private:
    int changeID; //key
    char productName[31];
    char changeDescription[31];
    int status;
    int priority;
    ReleaseID releaseID;
    Date dateFirstReported;

    static const int recordSize = /*to be done*/;
};

class ProductRelease : public DatabaseRecord {
public:
    ProductRelease();
    ProductRelease(int id, const char* name, const char* version);
    ~ProductRelease();

    void setProductName(const char* name);
    const char* getProductName() const;
    void setReleaseID(ReleaseID id);
    ReleaseID getReleaseID() const;
    void setReleaseDate(Date date);
    Date getReleaseDate() const;

    bool writeRecord() const override;
    bool readRecord() override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

    static bool addRelease(const ProductRelease& release);
    static bool addProduct(int id, const char* name);
    static bool showProduct(int id);
    static bool showRelease(int id);

private:
    char productName[31]; //key
    ReleaseID releaseID; //key
    Date releasedate;

    static const int recordSize = /*to be done*/;
};

//-------------------------------------
// Function prototypes

void openDatabase();
void closeDatabase();
int truncateFile(const char* path, off_t length);

#endif // DATABASE_H
