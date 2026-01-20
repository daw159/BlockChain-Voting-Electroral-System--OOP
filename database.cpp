#include "Database.h"
#include "colors.h"
#include <iostream>
#include <cstring>
#include<iomanip>

using namespace std;

Database::Database() : db(nullptr), errorMessage(nullptr) {}

Database::~Database()
{
    closeConnection();
}

bool Database::executeSQL(const char *sql)
{
    int rc = sqlite3_exec(db, sql, 0, 0, &errorMessage);
    if (rc != SQLITE_OK)
    {
        cerr << RED << "SQL error: " << errorMessage << RESET << endl;
        sqlite3_free(errorMessage);
        return false;
    }
    else
        return true;
}

void Database::closeConnection()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
        cout << YELLOW << "Database connection closed." << RESET << endl;
    }
}

bool Database::openConnection(const char *dbName)
{
    int rc = sqlite3_open(dbName, &db);
    if (rc)
    {
        cerr << RED << "Can't open database: " << sqlite3_errmsg(db) << RESET << endl;
        return false;
    }
    cout << GREEN << "Database connected successfully!" << RESET << endl;

    const char *createvotetable =
        "CREATE TABLE IF NOT EXISTS voters ("
        "voterid INTEGER PRIMARY KEY, "
        "name TEXT NOT NULL, "
        "hasvoted INTEGER DEFAULT 0);";

    const char *createcandidatetable =
        "CREATE TABLE IF NOT EXISTS candidates ("
        "candidateid INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "symbol TEXT NOT NULL UNIQUE, "
        "votecount INTEGER DEFAULT 0);";

    if (!executeSQL(createvotetable))
    {
        return false;
    }

    if (!executeSQL(createcandidatetable))
    {
        return false;
    }
    return true;
}

bool Database::voterExists(int id)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM voters WHERE voterid = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {

        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    bool exists = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        exists = sqlite3_column_int(stmt, 0) > 0;
    }
    sqlite3_finalize(stmt);
    return exists;
}

bool Database::hasVoted(int id)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT hasvoted FROM voters WHERE voterid = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << RED << "Failed to prepare statement: " << sqlite3_errmsg(db) << RESET << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);
    bool voted = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        voted = sqlite3_column_int(stmt, 0) == 1;
    }
    sqlite3_finalize(stmt);
    return voted;
}

bool Database::markAsVoted(int id)
{
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE voters SET hasvoted = 1 WHERE voterid = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {

        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    bool success = false;
    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        success = true;
    }
    sqlite3_finalize(stmt);
    return success;
}

void Database::displayAllVoters()
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT voterid, name, hasvoted FROM voters ORDER BY voterid;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << RED << "Failed to retrieve voters!" << RESET << endl;
        return;
    }

    cout << CYAN << "\n========== REGISTERED VOTERS ==========" << RESET << endl;
        cout << YELLOW << left 
         << setw(8) << "ID" 
         << setw(25) << "Name" 
         << setw(15) << "Status" 
         << RESET << endl;
    cout << "------------------------------------------------" << endl;


    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const char *name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        bool hasVoted = (sqlite3_column_int(stmt, 2) == 1);

        cout << left << setw(8) << id << setw(25) << name;
        if (hasVoted)
        {
            cout << GREEN << " Voted" << RESET << endl;
        }
        else
        {
            cout << RED << " Not Voted" << RESET << endl;
        }
    }

    cout << "======================================\n"
         << endl;
    sqlite3_finalize(stmt);
}

bool Database::addVoter(int id, const char *name)
{
    
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO voters (voterid, name) VALUES (?,?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << RED << "Failed to prepare statement: " << sqlite3_errmsg(db) << RESET << endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_STATIC);
   bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    
    if (!success)
    {
        cerr << RED << "Failed to add voter: " << sqlite3_errmsg(db) << RESET << endl;
    }
    
    sqlite3_finalize(stmt);
    return success;

}


bool Database::addCandidate(const char *name, const char *symbol)
{
    
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO candidates (name, symbol) VALUES (?,?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << RED << "Failed to prepare statement: " << sqlite3_errmsg(db) << RESET << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, symbol, -1, SQLITE_STATIC);
    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    
    sqlite3_finalize(stmt);
    return success;
}

// bool Database::symbolExists(const char *symbol)
// {
//     sqlite3_stmt *stmt;
//     const char *sql = "SELECT COUNT(*) FROM candidates WHERE symbol = ?;";
//     if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
//     {
//         return false;
//     }
//     sqlite3_bind_text(stmt, 1, symbol, -1, SQLITE_STATIC);
//     bool exists = false;
//     if (sqlite3_step(stmt) == SQLITE_ROW)
//     {
//         exists = sqlite3_column_int(stmt, 0) > 0;
//     }
//     sqlite3_finalize(stmt);
//     return exists;
// }

void Database::displayAllCandidates()
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT candidateid, name, symbol, votecount FROM candidates ORDER BY candidateid;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << RED << "Failed to retrieve candidates!" << RESET << endl;
        return;
    }

    cout << CYAN << "\n========== CANDIDATES LIST ==========" << RESET << endl;
cout << YELLOW << left 
         << setw(5) << "ID" 
         << setw(25) << "Name" 
         << setw(15) << "Symbol" 
         << setw(8) << "Votes" 
         << RESET << endl;
    cout << "--------------------------------------------------------------" << endl;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const char *name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        const char *symbol = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        int votes = sqlite3_column_int(stmt, 3);

        cout << left 
             << setw(5) << id 
             << setw(25) << name 
             << setw(15) << symbol 
             << setw(8) << votes 
             << endl;
    
    }

    cout << "=====================================\n"
         << endl;
    sqlite3_finalize(stmt);
}

bool Database::candidateExists(int id) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT COUNT(*) FROM candidates WHERE candidateid = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    
    sqlite3_bind_int(stmt, 1, id);
    
    bool exists = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = (sqlite3_column_int(stmt, 0) > 0);
    }
    
    sqlite3_finalize(stmt);
    return exists;
}

bool Database::incrementCandidateVotes(int id)
{
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE candidates SET votecount = votecount + 1 WHERE candidateid = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {

        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    bool success = false;
    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        success = true;
    }
    sqlite3_finalize(stmt);
    return success;
}


void Database::displayResults() {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT candidateid, name, symbol, votecount FROM candidates ORDER BY votecount DESC;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << RED << "Failed to retrieve results!" << RESET << endl;
        return;
    }
    
    
    int totalVotes = 0;
    const char* totalSql = "SELECT SUM(votecount) FROM candidates;";
    sqlite3_stmt* totalStmt;
    if (sqlite3_prepare_v2(db, totalSql, -1, &totalStmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(totalStmt) == SQLITE_ROW) {
            totalVotes = sqlite3_column_int(totalStmt, 0);
        }
        sqlite3_finalize(totalStmt);
    }
    
    cout << CYAN << "\n========== ELECTION RESULTS ==========" << RESET << endl;
    cout << YELLOW << "Total Votes Cast: " << totalVotes << RESET << endl;
    cout << "======================================" << endl;
    
    int rank = 1;
    int position = 1;  
    int previousVotes = -1;  
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* symbol = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int votecount = sqlite3_column_int(stmt, 3);
        
        float percentage = (totalVotes > 0) ? (votecount * 100.0f / totalVotes) : 0;
        
        
        if (votecount != previousVotes) {
            rank = position;  
        }
        
        cout << GREEN << rank << ". " << symbol << " - " << name << RESET;
        
        
        if (position > 1 && votecount == previousVotes) {
            cout << YELLOW << " (TIE)" << RESET;
        }
        
        cout << endl;
        cout << "   Votes: " << votecount << " (" << percentage << "%)" << endl;
        cout << "--------------------------------------" << endl;
        
        previousVotes = votecount;  
        position++; 
    }
    
    cout << "======================================\n" << endl;
    sqlite3_finalize(stmt);
}

void Database::resetElectionData() {
    
    executeSQL("DELETE FROM voters;");
    
    
    executeSQL("DELETE FROM candidates;");
    
    
    executeSQL("DELETE FROM sqlite_sequence WHERE name='candidates';");
    
    cout << GREEN << " Database tables cleared successfully!" << RESET << endl;
}
