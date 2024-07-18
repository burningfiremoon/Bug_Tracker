#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include "DatabaseRecord.h"
#include <fstream>

class ChangeItem : public DatabaseRecord {
public:
    ChangeItem(const char* changeID);
    ChangeItem(const ChangeItem& data);
    ~ChangeItem();

    void setChangeID(const char* changeID);
    const char* getChangeID() const;
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

    bool writeRecord(std::fstream &dbFile) const override;
    bool readRecord(std::fstream &dbFile) override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

    static bool updStatus(const char* id, int newStatus);
    static bool updRelease(const char* id, int newRelease);
    static bool updPriority(const char* id, int newPriority);
    static bool updDesc(const char* id, const char* newDescription);

private:
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
