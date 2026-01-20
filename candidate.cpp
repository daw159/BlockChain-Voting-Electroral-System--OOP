#include"Candidate.h"
#include"colors.h"
#include<iostream>
#include<cstring>


using namespace std;

Candidate::Candidate() : User(), votecount(0) {
    strcpy(symbol, "");  
}

Candidate::Candidate(int id,const char*name):User(id,name),votecount(0){

}

Candidate::Candidate(int id, const char* name, const char* sym): User(id, name), votecount(0) {
    strncpy(symbol, sym, 49);
    symbol[49] = '\0';
}

void Candidate::displayInfo() {
    cout << GREEN << userID << ". " << userName  << " (" << votecount << " votes)" << RESET << endl;
}

void Candidate::incrementVotes(){
    votecount++;

}

int Candidate::getVotecount() const{
    return votecount;
}

const char* Candidate::getSymbol() const{
    return symbol;
}
void Candidate::setSymbol(const char* sym){
    strncpy(symbol, sym, sizeof(symbol) - 1);
    symbol[sizeof(symbol) - 1] = '\0'; 
}