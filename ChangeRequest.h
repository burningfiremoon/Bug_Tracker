#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include "DatabaseRecord.h"

enum Status {
    REPORTED,
    IN_PROGRESS,
    DONE,
    CANCELLED
};

struct Date {
    int y;
    int m;
    int d;
};

class ChangeRequest : public DatabaseRecord {
public:
    ChangeRequest(const char* changeID, const char* requesterName); // constructor
    ChangeRequest(const ChangeRequest& data); // copy constructor
    ~ChangeRequest();

    void setChangeID(const char* changeID);
    const char* getChangeID() const;
    void setRequesterName(const char* requesterName);
    const char* getRequesterName() const;
    void setDescription(const char* description);
    const char* getDescription() const;
    void setReportedDate(Date date);
    Date getReportedDate() const;
    void setPriority(int priority);
    int getPriority() const;
    void setState(Status state);
    Status getState() const;

    bool writeRecord(fstream &dbFile) const override;
    bool readRecord(fstream &dbFile) override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

private:
    char changeID[7]; // 7 characters plus null terminator
    char requesterName[31]; // 30 characters plus null terminator
    char description[30];
    Date reportedDate;
    int priority;
    Status state;

    static const int recordSize;
};

#endif // CHANGEREQUEST_H