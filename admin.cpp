#include"admin.h"
#include<iostream>
#include<fstream>
#include<cstring>
#include"colors.h"

using namespace std;

Admin:: Admin() {
    strcpy(password, "admin123"); // Default password
}
Admin:: Admin(const char* pass) {
    strncpy(password, pass, sizeof(password) - 1);
    password[sizeof(password) - 1] = '\0'; 
}

bool Admin:: verifyPassword(const char* inputPass) const {
    return strcmp(password, inputPass) == 0;
}

void Admin::changePassword(const char* oldPass, const char* newPass) {
    if (verifyPassword(oldPass)) {
        strncpy(password, newPass, 49);
        password[49] = '\0';
        cout << GREEN << " Password changed successfully!" << RESET << endl;
        saveToFile();
    } else {
        cout << RED << " Incorrect old password!" << RESET << endl;
    }
}
void Admin:: saveToFile() const {
    ofstream fout("admin.dat", ios::binary);
    if (!fout) {
        cout << RED << " Failed to save admin data!" << RESET << endl;
        return;
    }
    fout.write((char*)password, sizeof(password));
    fout.close();
}

void Admin:: loadFromFile() {
    ifstream fin("admin.dat", ios::binary);
    if (!fin) {
        cout << RED << " Admin data file not found!" << RESET << endl;
        return;
    }
    fin.read((char*)password, sizeof(password));
    fin.close();
}

// const char* Admin::getPassword() const {
//     return password;
// }