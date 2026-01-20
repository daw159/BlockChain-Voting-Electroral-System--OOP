#ifndef VOTINGSYSTEM_H
#define VOTINGSYSTEM_H

#include "Database.h"
#include "Blockchain.h"
#include"admin.h"
#include <string>

class VotingSystem {
private:
    Database db;
    Blockchain blockchain;
    Admin admin;
    
   
    bool verifyAdmin();
    // void loadAdminPassword();
    // void saveAdminPassword();
    bool setupAdmin();
    
public:
    VotingSystem();
    ~VotingSystem();
    
    
    bool initialize();
    void run();
    void shutdown();
    
    
    void displayMainMenu();
    void displayAdminMenu();
    void displayVoterMenu();
    
    
    void adminPanel();
    void registerVoter();
    void addCandidate();
    void viewAllVoters();
    void viewAllCandidates();
    void viewStatistics();  
    void resetDatabase();
    void changeAdminPassword();
    
    
    void voterPanel();
    void castVote();
    void checkVotingStatus();
    
   
    void viewResults();
    
    
    void viewBlockchain();
    void exportBlockchain();
    void verifyBlockchainIntegrity();
};

#endif
