#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include "Voter.h"
#include "Candidate.h"

class Database {
private:
    sqlite3* db;
    char* errorMessage;
    
    bool executeSQL(const char* sql);

public:
    Database();
    ~Database();
    
    bool openConnection(const char* dbName);
    void closeConnection();
    sqlite3* getConnection() { return db; }
    
    
    bool addVoter(int id, const char* name);
    bool voterExists(int id);
    bool hasVoted(int id);
    bool markAsVoted(int id);
    // Voter getVoter(int id);
    void displayAllVoters();
    // int getVoterCount();
    
    
    bool addCandidate(const char* name, const char* symbol);
    bool candidateExists(int id);
    // bool symbolExists(const char* symbol);  
    // Candidate getCandidate(int id);
    // Candidate* getAllCandidates(int& count);
    void displayAllCandidates();
    // int getCandidateCount();
    bool incrementCandidateVotes(int id);
    
    
    void displayResults();
    void resetElectionData();  // Clear all voters and candidates

};

#endif
