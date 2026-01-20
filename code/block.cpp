#include<iostream>
#include"colors.h"
#include"block.h"
#include<cstring>

using namespace std;

Block::Block() {
    blocknumber = 0;
    strcpy(previoushash, "");
    strcpy(currenthash, "");
    voterid = 0;
    candidatevote = 0;
    strcpy(timestamp, "");
}

Block::Block(int num, const char* prevhash, int voterID, int vote) {
    blocknumber = num;
    strcpy(previoushash, prevhash);
    voterid = voterID;
    candidatevote = vote;
    strcpy(currenthash, "");
    strcpy(timestamp, "");
}


int Block::getBlocknumber() const {
    return blocknumber;
}
const char* Block::getPrevioushash() const {
    return previoushash;
}
const  char* Block::getCurrenthash() const {
    return currenthash;
}

int Block::getVoterid() const {
    return voterid;
}

int Block::getCandidatevote() const{
    return candidatevote;
}
const char *Block:: getTimestamp() const {
    return timestamp;
}

void Block::display() const {
    cout << CYAN << "Block #" << blocknumber << RESET << endl;
    cout << YELLOW << "Previous Hash: " << previoushash << RESET << endl;
    cout << YELLOW << "Current Hash: " << currenthash << RESET << endl;
    cout << YELLOW << "Voter ID: " << voterid << RESET << endl;
    cout << YELLOW << "Encrypted Vote: " << candidatevote << RESET << endl;
    cout << YELLOW << "Timestamp: " << timestamp << RESET << endl;
    cout << BOLDWHITE << "-----------------------------------" << RESET << endl;
}

void Block:: setCurrenthash(const char * hash){
    strncpy(currenthash, hash, 49);
    currenthash[49] = '\0'; 
}

void Block::setBlockdata(int num, const char* prevhash,  const char* currhash, int voterID, int vote, const char* time) {
    blocknumber = num;
    strncpy(previoushash, prevhash, 49);
    previoushash[49] = '\0';
    strncpy(currenthash, currhash, 49);
    currenthash[49] = '\0';
    voterid = voterID;
    candidatevote = vote;
    strncpy(timestamp, time, 49);
    timestamp[49] = '\0';
}

