#ifndef CHANGE_ITEM_H
#define CHANGE_ITEM_H

#include "DatabaseRecord.h"

struct Date {
    int y;
    int m;
    int d;
};

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
    void setReleaseID(const char* releaseID);
    const char* getReleaseID() const;
    void setDateFirstReported(Date date);
    Date getDateFirstReported() const;

    bool writeRecord(fstream &dbFile) const override;
    bool readRecord(fstream &dbFile) override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

    static bool updStatus(const char* id, int newStatus);
    static bool updRelease(const char* id, const char* newRelease);
    static bool updPriority(const char* id, int newPriority);
    static bool updDesc(const char* id, const char* newDescription);

private:
    char changeID[6];
    char productName[31];
    char changeDescription[31];
    int status;
    int priority;
    char releaseID[9]; // 8 digits plus null terminator
    Date dateFirstReported;

    static const int recordSize;
};

#endif // CHANGE_ITEM_H
