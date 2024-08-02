#ifndef USER_H
#define USER_H

#include "DatabaseRecord.h"

//-------------------------------------
// Class Definition
//-------------------------------------

class User : public DatabaseRecord {
public:
    User(const char* requesterName);
    User(const User& data);
    ~User();

    void setRequesterName(const char* requesterName);
    const char* getRequesterName() const;

    void setPhone(const char* phone);
    const char* getPhone() const;

    void setEmail(const char* email);
    const char* getEmail() const;

    void setAddress(const char* address);
    const char* getAddress() const;

    bool writeRecord(fstream &dbFile) const override;
    bool readRecord(fstream &dbFile) override;
    bool findUser(fstream &dbFile, const char* Name);

    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

    friend ostream& operator<<(ostream& os, const User& user);

private:
    char requesterName[31]; // 30 characters plus null terminator
    char phone[12]; // 11 characters plus null terminator
    char email[25]; // 24 characters plus null terminator
    char address[31]; // 30 characters plus null terminator

    static const int recordSize;
};

#endif // USER_H
