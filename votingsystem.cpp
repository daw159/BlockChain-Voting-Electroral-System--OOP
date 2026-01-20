#include "VotingSystem.h"
#include "colors.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "sqlite3.h"
#include <iomanip>

using namespace std;

void clearscreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause()
{
    cout << YELLOW << "\nPress Enter to continue..." << RESET;

    cin.clear();

    cin.ignore(10000, '\n');

    string temp;
    getline(cin, temp);
}

VotingSystem::VotingSystem() {}

VotingSystem::~VotingSystem()
{
    shutdown();
}

bool VotingSystem::initialize()
{
    cout << CYAN << "\n|================================================+" << RESET << endl;
    cout << CYAN << "|  BLOCKCHAIN VOTING SYSTEM - INITIALIZING        |" << RESET << endl;
    cout << CYAN << "|=================================================" << RESET << endl;

    admin.loadFromFile();

    if (!db.openConnection("voting_system.db"))
    {
        cerr << RED << "Error: Could not open database connection." << RESET << endl;
        return false;
    }

    blockchain.loadFromFile();
    cout << GREEN << "Initialization complete." << RESET << endl;
    pause();
    return true;
}
void VotingSystem::shutdown()
{

    cout << YELLOW << "\nShutting down system..." << RESET << endl;
    blockchain.saveToFile();
    db.closeConnection();
    admin.saveToFile();
    cout << GREEN << "Shutdown complete. Goodbye!" << RESET << endl;
}

bool VotingSystem::verifyAdmin()
{
    clearscreen();
    cout << CYAN << "\n|===============================================+" << RESET << endl;
    cout << CYAN << "|        ADMIN VERIFICATION REQUIRED            |" << RESET << endl;
    cout << CYAN << "|===============================================|" << RESET << endl;
    cout << BLUE << "\n----- Admin Verification -----\n"
         << RESET << endl;

    char enteredPassword[50];
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    cout << YELLOW << "Enter admin password: " << RESET;
    cin >> enteredPassword;

    while (attempts < MAX_ATTEMPTS && !admin.verifyPassword(enteredPassword))
    {
        attempts++;

        if (attempts >= MAX_ATTEMPTS)
        {
            cout << RED << "\n Incorrect password! Maximum attempts reached." << RESET << endl;
            cout << RED << " Access denied for security reasons." << RESET << endl;
            pause();
            return false;
        }

        cout << RED << "\n Incorrect password. Try again ("
             << (MAX_ATTEMPTS - attempts) << " attempts remaining): " << RESET;
        cin >> enteredPassword;
    }

    cout << GREEN << "\n Verification successful!" << RESET << endl;
    pause();
    return true;
}

void VotingSystem::displayMainMenu()
{
    clearscreen();
    cout << CYAN << "\n|===============================================+" << RESET << endl;
    cout << CYAN << "|         BLOCKCHAIN VOTING SYSTEM              |" << RESET << endl;
    cout << CYAN << "|===============================================|" << RESET << endl;

    cout << YELLOW << "\n1. Admin Panel" << RESET << endl;
    cout << YELLOW << "2. Voter Panel" << RESET << endl;
    cout << YELLOW << "3. View Results" << RESET << endl;
    cout << YELLOW << "4. Blockchain Operations" << RESET << endl;
    cout << YELLOW << "5. Exit" << RESET << endl;
    cout << GREEN << "\nEnter your choice: " << RESET;
}

void VotingSystem::displayAdminMenu()
{
    clearscreen();
    cout << CYAN << "\n|===============================================+" << RESET << endl;
    cout << CYAN << "|              ADMINISTRATOR MENU               |" << RESET << endl;
    cout << CYAN << "|===============================================|" << RESET << endl;

    cout << YELLOW << "1. Register Voter" << RESET << endl;
    cout << YELLOW << "2. Add Candidate" << RESET << endl;
    cout << YELLOW << "3. View All Voters" << RESET << endl;
    cout << YELLOW << "4. View All Candidates" << RESET << endl;
    cout << YELLOW << "5. View Election Statistics" << RESET << endl;
    cout << YELLOW << "6. Change Admin Password" << RESET << endl;
    cout << YELLOW << "7. Reset Database" << RESET << endl;
    cout << YELLOW << "8. Back to Main Menu" << RESET << endl;
    cout << GREEN << "\nEnter your choice: " << RESET;
}

void VotingSystem::displayVoterMenu()
{
    clearscreen();
    cout << CYAN << "\n|===============================================+" << RESET << endl;
    cout << CYAN << "|                 VOTER MENU                    |" << RESET << endl;
    cout << CYAN << "|===============================================|" << RESET << endl;

    cout << YELLOW << "1. Cast Vote" << RESET << endl;
    cout << YELLOW << "2. Check Voting Status" << RESET << endl;
    cout << YELLOW << "3. Back to Main Menu" << RESET << endl;
    cout << GREEN << "\nEnter your choice: " << RESET;
}

void VotingSystem::adminPanel()
{
    if (!verifyAdmin())
    {
        return;
    }

    while (true)
    {
        clearscreen();
        displayAdminMenu();
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            registerVoter();
            break;
        case 2:
            addCandidate();
            break;
        case 3:
            viewAllVoters();
            break;
        case 4:
            viewAllCandidates();
            break;
        case 5:
            viewStatistics();
            break;
        case 6:
            changeAdminPassword();
            break;
        case 7:
            resetDatabase();
            break;
        case 8:
            return;
        default:
            cout << RED << "Invalid choice!" << RESET << endl;
            pause();
        }
    }
}

void VotingSystem::registerVoter()
{
    clearscreen();
    cout << CYAN << "\n========== REGISTER VOTER ==========" << RESET << endl;
    int id;
    char name[100];

    cout << YELLOW << "Enter Voter ID: " << RESET;
    cin >> id;

    if (db.voterExists(id))
    {
        cout << RED << " Voter ID already exists!" << RESET << endl;
        pause();
        return;
    }

    cout << YELLOW << "Enter Voter Name: " << RESET;
    cin.ignore();
    cin.getline(name, 100);

    if (db.addVoter(id, name))
    {
        cout << GREEN << " Voter registered successfully!" << RESET << endl;
    }
    else
    {
        cout << RED << " Error registering voter." << RESET << endl;
    }

    pause();
}

void VotingSystem::addCandidate()
{
    clearscreen();
    cout << CYAN << "\n========== ADD CANDIDATE ==========" << RESET << endl;

    char name[100];
    char symbol[50];
    cout << YELLOW << "Enter Candidate Name: " << RESET;
    cin.ignore();
    cin.getline(name, 100);
    cout << YELLOW << "Enter Candidate Symbol: " << RESET;

    cin.getline(symbol, 50);

    cin.clear();

    if (db.addCandidate(name, symbol))
    {
        cout << GREEN << " Candidate added successfully!" << RESET << endl;
    }
    else
    {
        cout << RED << " Error adding candidate." << RESET << endl;
    }
    pause();
}

void VotingSystem::viewAllCandidates()
{
    clearscreen();
    cout << CYAN << "\n========== ALL CANDIDATES ==========" << RESET << endl;
    db.displayAllCandidates();
    pause();
}

void VotingSystem::viewAllVoters()
{
    clearscreen();
    cout << CYAN << "\n========== ALL VOTERS ==========" << RESET << endl;
    db.displayAllVoters();
    pause();
}

void VotingSystem::changeAdminPassword()
{
    clearscreen();
    cout << CYAN << "\n========== CHANGE ADMIN PASSWORD ==========" << RESET << endl;

    char oldPass[50];
    char newPass[50];
    char confirm[50];

    cout << YELLOW << "Enter current password: " << RESET;
    cin >> oldPass;
    if (!admin.verifyPassword(oldPass))
    {
        cout << RED << " Incorrect current password!" << RESET << endl;
        pause();
        return;
    }
    cout << YELLOW << "Enter new password: " << RESET;
    cin >> newPass;
    cout << YELLOW << "Confirm new password: " << RESET;
    cin >> confirm;
    if (strcmp(newPass, confirm) != 0)
    {
        cout << RED << " New passwords do not match!" << RESET << endl;
        pause();
        return;
    }
    if (strcmp(newPass, oldPass) == 0)
    {
        cout << RED << " New password cannot be the same as the old password!" << RESET << endl;
        pause();
        return;
    }
    admin.changePassword(oldPass, newPass);
    // cout << GREEN << " Password changed successfully!" << RESET << endl;
    pause();
}

void VotingSystem::resetDatabase()
{
    clearscreen();
    cout << CYAN << "\n========== RESET ELECTION DATA ==========" << RESET << endl;
    cout << RED << "\n  WARNING: This will delete ALL election data!" << RESET << endl;
    cout << RED << "   - All voters" << RESET << endl;
    cout << RED << "   - All candidates" << RESET << endl;
    cout << RED << "   - All votes" << RESET << endl;
    cout << RED << "   - Entire blockchain" << RESET << endl;

    cout << YELLOW << "\nAre you sure? (y/n): " << RESET;

    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm == 'y' || confirm == 'Y')
    {
        cout << YELLOW << "\n Resetting data..." << RESET << endl;

        // Reset database
        db.resetElectionData();

        blockchain.clearChain();

        cout << GREEN << "\n All election data has been reset!" << RESET << endl;
        cout << GREEN << " System is ready for a new election." << RESET << endl;
    }
    else
    {
        cout << YELLOW << "\n Reset cancelled." << RESET << endl;
    }

    pause();
}

void VotingSystem::voterPanel()
{
    while (true)
    {
        clearscreen();
        displayVoterMenu();
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            castVote();
            break;
        case 2:
            checkVotingStatus();
            break;
        case 3:
            return;
        default:
            cout << RED << "Invalid choice!" << RESET << endl;
            pause();
        }
    }
}

void VotingSystem::checkVotingStatus()
{
    clearscreen();
    cout << CYAN << "\n========== CHECK VOTING STATUS ==========" << RESET << endl;
    int vid;
    cout << YELLOW << "Enter your Voter ID: " << RESET;
    cin >> vid;

    if (!db.voterExists(vid))
    {
        cout << RED << " Voter ID not found!" << RESET << endl;
        pause();
        return;
    }

    if (db.hasVoted(vid))
    {
        cout << GREEN << " You have already cast your vote." << RESET << endl;
    }
    else
    {
        cout << YELLOW << " You have not voted yet." << RESET << endl;
    }

    pause();
}

void VotingSystem::castVote()
{
    clearscreen();
    cout << CYAN << "\n========== CAST YOUR VOTE ==========" << RESET << endl;
    int vid, cid;
    cout << YELLOW << "Enter your Voter ID: " << RESET;
    cin >> vid;
    if (!db.voterExists(vid))
    {
        cout << RED << " Voter ID not found!" << RESET << endl;
        pause();
        return;
    }
    if (db.hasVoted(vid))
    {
        cout << RED << " You have already voted!" << RESET << endl;
        pause();
        return;
    }
    db.displayAllCandidates();
    cout << YELLOW << "Enter Candidate ID to vote for: " << RESET;
    cin >> cid;
    if (!db.candidateExists(cid))
    {
        cout << RED << " Candidate ID not found!" << RESET << endl;
        pause();
        return;
    }
    if (db.incrementCandidateVotes(cid) && db.markAsVoted(vid))
    {

        blockchain.addBlock(vid, cid);
        blockchain.saveToFile();

        cout << GREEN << "\n Vote cast successfully!" << RESET << endl;
        cout << CYAN << " Your vote has been recorded securely in the blockchain." << RESET << endl;
        // cout << CYAN << " Block #" << blockchain.getBlockCount() << " added to blockchain" << RESET << endl;
    }
    else
    {
        cout << RED << " Failed to cast vote!" << RESET << endl;
    }
    pause();
}

void VotingSystem::viewResults()
{
    clearscreen();
    db.displayResults();
    pause();
}

void VotingSystem::viewBlockchain()
{
    clearscreen();
    cout << CYAN << "\n========== BLOCKCHAIN DATA ==========" << RESET << endl;
    blockchain.displayChain();
    pause();
}

void VotingSystem::exportBlockchain()
{
    clearscreen();
    blockchain.exportToFile();
    cout << GREEN << " Blockchain exported to file!" << RESET << endl;
    pause();
}

void VotingSystem::verifyBlockchainIntegrity()
{
    clearscreen();
    cout << CYAN << "\n|====================================|" << RESET << endl;
    cout << "|         VERIFY BLOCKCHAIN INTEGRITY         |" << RESET << endl;
    cout << CYAN << "|=====================================|" << RESET << endl;
    if (blockchain.verifyChain())
    {
        cout << GREEN << "\n Blockchain is valid and intact!" << RESET << endl;
        cout << CYAN << " All votes are secure and unmodified." << RESET << endl;
    }
    else
    {
        cout << RED << "\n Blockchain integrity compromised!" << RESET << endl;
        cout << RED << "  Votes may have been tampered with!" << RESET << endl;
    }
    pause();
}

void VotingSystem::run()
{
    while (true)
    {
        clearscreen();
        displayMainMenu();

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            adminPanel();
            break;

        case 2:
            voterPanel();
            break;

        case 3:
            viewResults();
            break;

        case 4:
        {

            bool exitBlockchainMenu = false;

            while (!exitBlockchainMenu) // ✅ Loop until user chooses to exit
            {
                clearscreen();
                cout << CYAN << "\n|===============================================|" << RESET << endl;
                cout << CYAN << "|       BLOCKCHAIN OPERATIONS                   |" << RESET << endl;
                cout << CYAN << "|===============================================|" << RESET << endl;

                cout << YELLOW << "1. View Blockchain" << RESET << endl;
                cout << YELLOW << "2. Export Blockchain" << RESET << endl;
                cout << YELLOW << "3. Verify Blockchain Integrity" << RESET << endl;
                cout << YELLOW << "4. Back to Main Menu" << RESET << endl;
                cout << GREEN << "\nEnter your choice: " << RESET;

                int bcChoice;
                cin >> bcChoice;

                switch (bcChoice)
                {
                case 1:
                    viewBlockchain();
                    break;

                case 2:
                    exportBlockchain();
                    break;

                case 3:
                    verifyBlockchainIntegrity();
                    break;

                case 4:
                    exitBlockchainMenu = true;
                    break;

                default:
                    cout << RED << "Invalid choice!" << RESET << endl;
                    pause();
                    break;
                }
            }
            break;
        }

        case 5:
            cout << CYAN << "\n Thank you for using the Blockchain Voting System!" << RESET << endl;
            return;

        default:
            cout << RED << "Invalid choice!" << RESET << endl;
            pause();
            break;
        }
    }
}

void VotingSystem::viewStatistics()
{
    clearscreen();
    cout << CYAN << "\n|==============================================|" << RESET << endl;
    cout << CYAN << "|        ELECTION STATISTICS                    |" << RESET << endl;
    cout << CYAN << "|==============================================|" << RESET << endl;

    sqlite3 *dbconn = db.getConnection();

   
    int tvotes = 0;
    int votecount = 0;
    sqlite3_stmt *voterStmt;
    const char *voterSql = "SELECT COUNT(*), SUM(hasvoted) FROM voters;";

    if (sqlite3_prepare_v2(dbconn, voterSql, -1, &voterStmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(voterStmt) == SQLITE_ROW)
        {
            tvotes = sqlite3_column_int(voterStmt, 0);
            votecount = sqlite3_column_int(voterStmt, 1);
        }
    }
    sqlite3_finalize(voterStmt);

    int notvotes = tvotes - votecount;
    double turnout = (tvotes == 0) ? 0.0 : (static_cast<double>(votecount) / tvotes) * 100.0;

    
    int totalCandidates = 0;
    int totalVotes = 0;

    sqlite3_stmt *candStmt;
    const char *candSql = "SELECT COUNT(*), SUM(votecount) FROM candidates;";

    if (sqlite3_prepare_v2(dbconn, candSql, -1, &candStmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(candStmt) == SQLITE_ROW)
        {
            totalCandidates = sqlite3_column_int(candStmt, 0);
            totalVotes = sqlite3_column_int(candStmt, 1);
        }
        sqlite3_finalize(candStmt);
    }

    
    char lname[50] = "N/A";
    char lsymbol[20] = "N/A";
    int lvotes = 0;

    sqlite3_stmt *leadStmt;
    const char *leadSql = "SELECT name, symbol, votecount FROM candidates ORDER BY votecount DESC LIMIT 1;";
    if (sqlite3_prepare_v2(dbconn, leadSql, -1, &leadStmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(leadStmt) == SQLITE_ROW)
        {
            strcpy(lname, reinterpret_cast<const char *>(sqlite3_column_text(leadStmt, 0)));
            strcpy(lsymbol, reinterpret_cast<const char *>(sqlite3_column_text(leadStmt, 1)));
            lvotes = sqlite3_column_int(leadStmt, 2);
        }
    }
    sqlite3_finalize(leadStmt);

    cout << "\n"
         << YELLOW << " Voter Information:" << RESET << endl;
    cout << "   Total Registered Voters:     " << tvotes << endl;
    cout << "   Total Votes Cast:            " << votecount << endl;
    cout << "   Voters Not Yet Voted:        " << notvotes << endl;
    cout << GREEN << "   Voter Turnout:               " << fixed << setprecision(2) << turnout << "%" << RESET << endl;

    cout << "\n"
         << YELLOW << "  Candidate Information:" << RESET << endl;
    cout << "   Total Candidates:            " << totalCandidates << endl;
    cout << "   Total Votes Counted:         " << totalVotes << endl;

    if (totalCandidates > 0 && lvotes > 0)
    {
        cout << GREEN << "   Leading Candidate:           " << lsymbol << " - "
             << lname << " (" << lvotes << " votes)" << RESET << endl;
    }
    else
    {
        cout << "   Leading Candidate:           N/A" << endl;
    }

    cout << "\n"
         << YELLOW << "  Blockchain Information:" << RESET << endl;
    int totalBlocks = blockchain.getBlockCount();
    cout << "   Total Blocks:                " << totalBlocks << endl;
    cout << "   Genesis Block:               " << (totalBlocks > 0 ? "1" : "0") << endl;
    cout << "   Vote Blocks:                 " << (totalBlocks > 0 ? totalBlocks - 1 : 0) << endl;

    cout << "   Blockchain Status:           ";

    bool isValid = blockchain.isChainValid_Silent();

    if (isValid)
    {
        cout << GREEN << " Valid" << RESET << endl;
    }
    else
    {
        cout << RED << " Invalid" << RESET << endl;
    }

    cout << "\n"
         << CYAN << "=======================================" << RESET << endl;

    pause();
}
