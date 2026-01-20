#include "Voter.h"  
#include "colors.h"  
#include <iostream>  

using namespace std;

Voter::Voter() : User(), hasvoted(false) {}

Voter::Voter(int id, const char* name) : User(id, name), hasvoted(false) {}

bool Voter::getHasvoted() const {
    return hasvoted;
}

void Voter::setHasvoted(bool v) {
    hasvoted = v;
}

void Voter::displayInfo() {
    cout << CYAN << "======= VOTER INFO =======" << RESET << endl;
    cout << YELLOW << "Voter ID: " << userID << RESET << endl;
    cout << YELLOW << "Name: " << userName << RESET << endl;
    cout << YELLOW << "Status: " 
         << (hasvoted ? GREEN "Voted" : RED "Not Voted") 
         << RESET << endl;
    cout << CYAN << "==========================" << RESET << endl;
}
