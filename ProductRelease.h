#ifndef PRODUCT_RELEASE_H
#define PRODUCT_RELEASE_H

#include "DatabaseRecord.h"

struct Date {
    int y;
    int m;
    int d;
};

class ProductRelease : public DatabaseRecord {
public:
    ProductRelease();
    ProductRelease(const char* name, const char* releaseID, Date date);
    ~ProductRelease();

    void setProductName(const char* name);
    const char* getProductName() const;
    void setReleaseID(const char* releaseID);
    const char* getReleaseID() const;
    void setReleaseDate(Date date);
    Date getReleaseDate() const;

    bool writeRecord(fstream &dbFile) const override;
    bool readRecord(fstream &dbFile) override;
    int getRecordSize() const override;
    void readFromBuffer(const char* buffer) override;

    static bool addRelease(const ProductRelease& release);
    static bool addProduct(int id, const char* name);
    static bool showProduct(int id);
    static bool showRelease(int id);

private:
    char productName[11]; // 10 characters plus null terminator
    char releaseID[9]; // 8 characters plus null terminator
    Date releaseDate;

    static const int recordSize;
};

#endif // PRODUCT_RELEASE_H
