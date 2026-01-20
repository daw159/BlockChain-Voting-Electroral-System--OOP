#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "User.h"

class Candidate : public User
{
private:
    int votecount;
    char symbol[50];

public:
    Candidate();
    Candidate(int id, const char *name);
    Candidate(int id, const char* name, const char* sym);

    void displayInfo() override;

    void incrementVotes();
    int getVotecount() const;

    const char* getSymbol() const;
    void setSymbol(const char* sym);
    
};

#endif
