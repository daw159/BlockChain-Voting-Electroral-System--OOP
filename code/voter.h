#ifndef VOTER_H
#define VOTER_H

#include "User.h"  // ✅ Capital U, quotes

class Voter : public User
{
private:
    bool hasvoted;

public:
    Voter();
    Voter(int id, const char *name);

    void displayInfo() override;

    bool getHasvoted() const;      // ✅ Lowercase 'h'
    void setHasvoted(bool status); // ✅ Lowercase 'h'
};

#endif
