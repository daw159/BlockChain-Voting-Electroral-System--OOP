#include "Blockchain.h"
#include "colors.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

Blockchain::Blockchain() {}

Blockchain::~Blockchain() {}

int Blockchain::encryptVote(int plainVote) const
{
    return (plainVote + ENCRYPTION_KEY) % 100;
}
int Blockchain::getBlockCount() const
{
    return chain.size();
}
int Blockchain::decryptVote(int encryptedVote) const
{
    int d = (encryptedVote - ENCRYPTION_KEY) % 100;
    if (d < 0)
    {
        d += 100;
    }
    return d;
}

void Blockchain::generateTimestamp(char *buffer)
{
    time_t now = time(0);
    struct tm *tstruct = localtime(&now);
    strftime(buffer, 50, "%Y-%m-%d %X", tstruct);
}

void Blockchain::calculateHash(const char *prev, int voterId, int vote, const char *time, char *output)
{
    unsigned long hash = 5381;
    char combined[256];

    sprintf(combined, "%s|%d|%d|%s", prev, voterId, vote, time);

    for (int i = 0; combined[i] != '\0'; i++)
        hash = ((hash << 5) + hash) + combined[i];

    sprintf(output, "HASH%06lu", hash % 1000000);
}

void Blockchain::addBlock(int voteid, int cvote)
{
    Block b;
    char prevhash[50];

    if (chain.empty())
    {
        strcpy(prevhash, "GENESIS");
    }
    else
    {
        strcpy(prevhash, chain.back().getCurrenthash());
    }

    char timestamp[50];
    generateTimestamp(timestamp);

    int encrypted = encryptVote(cvote);
    char currenthash[50];
    calculateHash(prevhash, voteid, encrypted, timestamp, currenthash);
    b.setBlockdata(chain.size(), prevhash, currenthash, voteid, encrypted, timestamp);
    chain.push_back(b);

    // cout << GREEN << " Block #" << (chain.size() - 1) << " added to blockchain!" << RESET << endl;
}

void Blockchain::displayChain() const
{
    // cout << BLUE << "\n------------- BLOCKCHAIN -------------" << RESET << endl;

    if (chain.empty())
    {
        cout << RED << "Blockchain is empty." << RESET << endl;
        return;
    }

    for (int i = 0; i < chain.size(); i++)
    {
        chain[i].display();
    }

    cout << CYAN << "Total Blocks: " << chain.size() << RESET << endl;
}

Block *Blockchain::searchBlock(int blockNumber)
{
    for (auto &block : chain)
    {
        if (block.getBlocknumber() == blockNumber)
        {
            return &block;
        }
    }
    return nullptr;
}

void Blockchain::saveToFile() const
{
    ofstream fout("blockchain.dat", ios::binary);

    if (!fout)
    {
        cout << RED << " Failed to save blockchain!" << RESET << endl;
        return;
    }

    int count = chain.size();
    fout.write((char *)&count, sizeof(int));

    for (int i = 0; i < count; i++)
    {
        fout.write((char *)&chain[i], sizeof(Block));
    }

    fout.close();
    // cout << GREEN << " Blockchain saved to blockchain.dat (" << count << " blocks)" << RESET << endl;
}

void Blockchain::loadFromFile()
{
    ifstream fin("blockchain.dat", ios::binary);

    if (!fin)
    {
        cout << YELLOW << "No existing blockchain found. Starting fresh." << RESET << endl;
        return;
    }

    int count;
    fin.read((char *)&count, sizeof(int));

    chain.clear();

    for (int i = 0; i < count; i++)
    {
        Block b;
        fin.read((char *)&b, sizeof(Block));
        chain.push_back(b);
    }

    fin.close();
}

void Blockchain::exportToFile() const
{
    ofstream fout("blockchain_export.txt");

    if (!fout)
    {
        cout << RED << " Failed to create export file!" << RESET << endl;
        return;
    }

    fout << "===========================================\n";
    fout << "  BLOCKCHAIN VOTING SYSTEM - EXPORT\n";
    fout << "===========================================\n\n";

    char exportTime[50];
    time_t now = time(0);
    strftime(exportTime, 50, "%Y-%m-%d %H:%M:%S", localtime(&now));
    fout << "Export Timestamp: " << exportTime << "\n";
    fout << "Total Blocks: " << chain.size() << "\n\n";

    for (int i = 0; i < chain.size(); i++)
    {
        fout << "Block Number: " << chain[i].getBlocknumber() << "\n";
        fout << "Previous Hash: " << chain[i].getPrevioushash() << "\n";
        fout << "Current Hash: " << chain[i].getCurrenthash() << "\n";
        fout << "Voter ID: " << chain[i].getVoterid() << "\n";
        fout << "Encrypted Vote: " << chain[i].getCandidatevote() << "\n";
        fout << "Decrypted Vote (Candidate ID): " << decryptVote(chain[i].getCandidatevote()) << "\n";
        fout << "Timestamp: " << chain[i].getTimestamp() << "\n";
        fout << "-----------------------------------\n";
    }

    fout.close();
    cout << GREEN << " Blockchain exported to blockchain_export.txt" << RESET << endl;
}

bool Blockchain::verifyChain()
{
    if (chain.empty())
    {
        cout << YELLOW << "   Blockchain is empty. Nothing to verify." << RESET << endl;
        return true;
    }

    bool allValid = true;

    for (int i = 0; i < chain.size(); i++)
    {
        cout << "   Checking Block " << i << ": " << flush;

        // Recalculate hash
        char re_hash[50];
        calculateHash(
            chain[i].getPrevioushash(), 
            chain[i].getVoterid(), 
            chain[i].getCandidatevote(), 
            chain[i].getTimestamp(), 
            re_hash
        );

        // Verify current hash matches recalculated hash
        if (strcmp(chain[i].getCurrenthash(), re_hash) != 0)
        {
            cout << RED << "Invalid (Hash Mismatch)" << RESET << endl;
            allValid = false;
            continue;
        }

        // Verify chain linkage (except genesis block)
        if (i > 0 && strcmp(chain[i].getPrevioushash(), chain[i - 1].getCurrenthash()) != 0)
        {
            cout << RED << "Invalid (Chain Break)" << RESET << endl;
            allValid = false;
            continue;
        }

        cout << GREEN << "Valid" << RESET << endl;
    }

    // Summary message
    if (allValid)
    {
        cout << GREEN << "\n   ✓ All blocks verified successfully!" << RESET << endl;
    }
    else
    {
        cout << RED << "\n   ✗ Blockchain integrity compromised!" << RESET << endl;
    }

    return allValid;
}

// ✅ NEW: Silent validation (no console output)
bool Blockchain::isChainValid_Silent()
{
    if (chain.empty())
    {
        return true;
    }

    for (int i = 0; i < chain.size(); i++)
    {
        // Recalculate hash
        char re_hash[50];
        calculateHash(
            chain[i].getPrevioushash(), 
            chain[i].getVoterid(), 
            chain[i].getCandidatevote(), 
            chain[i].getTimestamp(), 
            re_hash
        );

        // Check hash mismatch
        if (strcmp(chain[i].getCurrenthash(), re_hash) != 0)
        {
            return false;
        }

        // Check chain linkage (except genesis)
        if (i > 0 && strcmp(chain[i].getPrevioushash(), chain[i - 1].getCurrenthash()) != 0)
        {
            return false;
        }
    }

    return true;  // All blocks valid
}
void Blockchain::clearChain()
{
    chain.clear();  // Clear in-memory chain
    
    // Delete blockchain file
    if (remove("blockchain.dat") == 0)
    {
        cout << GREEN << "   ✓ Blockchain file deleted." << RESET << endl;
    }
    else
    {
        cout << YELLOW << "   (No blockchain file to delete)" << RESET << endl;
    }
}
