#ifndef USER_H
#define USER_H

class User {
protected:
    int userID;           
    char userName[50];    

public:
    User();
    User(int id, const char* name);
    virtual ~User();
    virtual void displayInfo() = 0;
    int getID() const;
    const char* getName() const;
};

#endif
