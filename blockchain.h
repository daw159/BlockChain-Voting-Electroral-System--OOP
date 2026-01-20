#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <vector>

using namespace std;

class Blockchain
{
private:
    vector<Block> chain;
    static const int ENCRYPTION_KEY = 17;

    void calculateHash(const char *prev, int voterID,int vote, const char *time, char *output);
    void generateTimestamp(char *buffer);

public:
    // Constructors
    Blockchain();
    ~Blockchain();

    
    void addBlock(int voterID, int candidateVote);
    bool verifyChain();
    void displayChain() const;
    Block *searchBlock(int blockNumber);
    void exportToFile() const;

    
    int encryptVote(int plainVote) const;
    int decryptVote(int encryptedVote) const;

    
    void saveToFile() const;
    void loadFromFile();

    
    int getBlockCount() const;
    bool isChainValid_Silent();  
    void clearChain();
};

#endif
