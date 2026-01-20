#include "User.h"
#include <cstring>
#include <iostream>

using namespace std;

User::User() : userID(0) {
    userName[0] = '\0';  
}


User::User(int id, const char* name) : userID(id) {
    strncpy(userName, name, 49);
    userName[49] = '\0';  
}

User::~User() {
}


int User::getID() const {
    return userID;
}

const char* User::getName() const {
    return userName;
}
