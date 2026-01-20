#ifndef BLOCK_H
#define BLOCK_H

class Block {
private:
    int blocknumber;
    char previoushash[50];
    char currenthash[50];
    int voterid;
    int candidatevote;
    char timestamp[50];

public:
    
    Block();
    Block(int num, const char* prevhash, int voterID, int vote);
    
    // Getters
    int getBlocknumber() const;
    const char* getPrevioushash() const;
    const char* getCurrenthash() const;
    int getVoterid() const;
    int getCandidatevote() const;
    const char* getTimestamp() const;
    
   
    void setBlockdata(int num, const char* prevhash, 
                      const char* currhash, int voterID, 
                      int vote, const char* time);
    void setCurrenthash(const char* hash);
    
    void display() const;
};

#endif
