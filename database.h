// database.h
#ifndef DATABASE_H
#define DATABASE_H

openDatabase();
closeDatabase();

//class for objects with member functions
class ChangeRequest
{
public:
    // constructor ***need to change attribute 1 and 2 to real attributes
    ChangeRequest(int x, string y) : attribute1(x), attribute2(y) {}
    // destructor
    ~ChangeRequest()
    {
    }
    // member functions
    // add itself to database
    void add();
    // set attribute1 ***need to change attribute 1 to real attribute
    void setAttribute1(int x);
    // get attribute1 ***need to change attribute 1 to real attribute
    int getAttribute1();
    // set attribute2 ***need to change attribute 2 to real attribute
    void setAttribute2(string y);
    // get attribute2 ***need to change attribute 2 to real attribute
    string getAttribute2();

private:
    // ***need to add attributes
};

class User
{
};

class ChangeItem
{
};

class ProductRelease
{
};

class Product
{
};

#endif // DATABASE_H