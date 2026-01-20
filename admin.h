#ifndef ADMIN_H
#define ADMIN_H

class Admin {
private:
    char password[50];

public:
    Admin();
    Admin(const char* pass);
    
    bool verifyPassword(const char* inputPass) const;
    void changePassword(const char* oldPass, const char* newPass);
    
    void saveToFile() const;
    void loadFromFile();
    // const char* Admin::getPassword() const ;
    
    
};

#endif
