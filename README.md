<div align="center">

# 🗳️ Blockchain Voting System

### *Secure, Transparent, and Tamper-Proof Electronic Voting*

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![SQLite](https://img.shields.io/badge/SQLite-3-green.svg)
![OpenSSL](https://img.shields.io/badge/OpenSSL-Crypto-red.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

*A decentralized voting platform using blockchain technology to ensure vote integrity and transparency*

[Features](#-features) • [Installation](#-installation) • [Usage](#-usage) • [Demo](#-demo) • [Documentation](#-documentation)

</div>

---

## 📖 Overview

The **Blockchain Voting System** is a secure electronic voting application that leverages blockchain technology to provide an immutable, transparent, and auditable voting process. Built with C++, SQLite, and OpenSSL, this system ensures that every vote is encrypted, verified, and permanently recorded in an tamper-proof blockchain [attached_file:1][attached_file:2].

### 🎯 Why Blockchain for Voting?

- **Immutability**: Once a vote is cast, it cannot be altered or deleted
- **Transparency**: Complete audit trail visible to all stakeholders
- **Security**: Cryptographic hashing prevents tampering
- **Verification**: Real-time blockchain integrity checks
- **Decentralization**: No single point of failure

---

## ✨ Features

### 🔐 Admin Panel
- ✅ **Voter Management**: Register voters with unique IDs
- ✅ **Candidate Management**: Add candidates with symbols
- ✅ **Real-time Monitoring**: View voter status and candidate standings
- ✅ **Election Statistics**: Comprehensive dashboard with turnout and results
- ✅ **Security Controls**: Password protection and authentication
- ✅ **Database Reset**: Clean slate for new elections
- ✅ **Blockchain Audit**: Verify and export complete chain

### 🗳️ Voter Features
- ✅ **Secure Voting**: Encrypted vote casting
- ✅ **Status Check**: Verify voting completion
- ✅ **Duplicate Prevention**: One vote per voter enforced
- ✅ **Blockchain Recording**: Votes stored in immutable blocks

### 📊 Public Access
- ✅ **Live Results**: Real-time vote counting with percentages
- ✅ **Blockchain Explorer**: View complete chain data
- ✅ **Integrity Verification**: Validate blockchain authenticity
- ✅ **Export Functionality**: Download audit trails

### ⛓️ Blockchain Technology
- ✅ **SHA-256 Hashing**: Cryptographic block linking
- ✅ **Vote Encryption**: XOR-based vote protection
- ✅ **Chain Validation**: Automatic tampering detection
- ✅ **Persistent Storage**: Binary file blockchain storage
- ✅ **Genesis Block**: Automatic initialization

---

## 🛠️ Technology Stack

| Component | Technology | Purpose |
|-----------|-----------|---------|
| **Language** | C++17 | Core system implementation |
| **Database** | SQLite3 | Voter and candidate data storage |
| **Cryptography** | OpenSSL | SHA-256 hashing and encryption |
| **Compiler** | GCC/MinGW | Cross-platform compilation |
| **UI** | ANSI Colors | Terminal interface enhancement |

---

## 📦 Installation

### Prerequisites

<details>
<summary><b>Windows (MinGW/MSYS2)</b></summary>

```bash
# Install MSYS2 from https://www.msys2.org/
# Then install required packages:
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-sqlite3
pacman -S mingw-w64-x86_64-openssl



# Clone repository
git clone https://github.com/daw159/blockchain-voting-system.git
cd blockchain-voting-system

# Compile (Windows)
g++ main.cpp User.cpp Voter.cpp Candidate.cpp Block.cpp Database.cpp Blockchain.cpp admin.cpp VotingSystem.cpp -o voting.exe -lsqlite3 -lcrypto

# Compile (Linux/macOS)
g++ main.cpp User.cpp Voter.cpp Candidate.cpp Block.cpp Database.cpp Blockchain.cpp admin.cpp VotingSystem.cpp -o voting -lsqlite3 -lcrypto

# Run
./voting
## **🔧 Fixed README.md - Error Corrected**

The error is in the markdown links. GitHub markdown doesn't support inline links within badge URLs. Here's the **corrected version**:

```markdown
<div align="center">

# 🗳️ Blockchain Voting System

### *Secure, Transparent, and Tamper-Proof Electronic Voting*

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![SQLite](https://img.shields.io/badge/SQLite-3-green.svg)
![OpenSSL](https://img.shields.io/badge/OpenSSL-Crypto-red.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

*A decentralized voting platform using blockchain technology to ensure vote integrity and transparency*

[Features](#-features) • [Installation](#-installation) • [Usage](#-usage) • [Demo](#-demo) • [Documentation](#-documentation)

</div>

---

## 📖 Overview

The **Blockchain Voting System** is a secure electronic voting application that leverages blockchain technology to provide an immutable, transparent, and auditable voting process. Built with C++, SQLite, and OpenSSL, this system ensures that every vote is encrypted, verified, and permanently recorded in an tamper-proof blockchain [attached_file:1][attached_file:2].

### 🎯 Why Blockchain for Voting?

- **Immutability**: Once a vote is cast, it cannot be altered or deleted
- **Transparency**: Complete audit trail visible to all stakeholders
- **Security**: Cryptographic hashing prevents tampering
- **Verification**: Real-time blockchain integrity checks
- **Decentralization**: No single point of failure

---

## ✨ Features

### 🔐 Admin Panel
- ✅ **Voter Management**: Register voters with unique IDs
- ✅ **Candidate Management**: Add candidates with symbols
- ✅ **Real-time Monitoring**: View voter status and candidate standings
- ✅ **Election Statistics**: Comprehensive dashboard with turnout and results
- ✅ **Security Controls**: Password protection and authentication
- ✅ **Database Reset**: Clean slate for new elections
- ✅ **Blockchain Audit**: Verify and export complete chain

### 🗳️ Voter Features
- ✅ **Secure Voting**: Encrypted vote casting
- ✅ **Status Check**: Verify voting completion
- ✅ **Duplicate Prevention**: One vote per voter enforced
- ✅ **Blockchain Recording**: Votes stored in immutable blocks

### 📊 Public Access
- ✅ **Live Results**: Real-time vote counting with percentages
- ✅ **Blockchain Explorer**: View complete chain data
- ✅ **Integrity Verification**: Validate blockchain authenticity
- ✅ **Export Functionality**: Download audit trails

### ⛓️ Blockchain Technology
- ✅ **SHA-256 Hashing**: Cryptographic block linking
- ✅ **Vote Encryption**: XOR-based vote protection
- ✅ **Chain Validation**: Automatic tampering detection
- ✅ **Persistent Storage**: Binary file blockchain storage
- ✅ **Genesis Block**: Automatic initialization

---

## 🛠️ Technology Stack

| Component | Technology | Purpose |
|-----------|-----------|---------|
| **Language** | C++17 | Core system implementation |
| **Database** | SQLite3 | Voter and candidate data storage |
| **Cryptography** | OpenSSL | SHA-256 hashing and encryption |
| **Compiler** | GCC/MinGW | Cross-platform compilation |
| **UI** | ANSI Colors | Terminal interface enhancement |

---

## 📦 Installation

### Prerequisites

<details>
<summary><b>Windows (MinGW/MSYS2)</b></summary>

```bash
# Install MSYS2 from https://www.msys2.org/
# Then install required packages:
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-sqlite3
pacman -S mingw-w64-x86_64-openssl
```
</details>

<details>
<summary><b>Linux (Ubuntu/Debian)</b></summary>

```bash
sudo apt update
sudo apt install g++ libsqlite3-dev libssl-dev
```
</details>

<details>
<summary><b>macOS</b></summary>

```bash
brew install sqlite3 openssl gcc
```
</details>

### Clone & Build

```bash
# Clone repository
git clone https://github.com/daw159/blockchain-voting-system.git
cd blockchain-voting-system

# Compile (Windows)
g++ main.cpp User.cpp Voter.cpp Candidate.cpp Block.cpp Database.cpp Blockchain.cpp admin.cpp VotingSystem.cpp -o voting.exe -lsqlite3 -lcrypto

# Compile (Linux/macOS)
g++ main.cpp User.cpp Voter.cpp Candidate.cpp Block.cpp Database.cpp Blockchain.cpp admin.cpp VotingSystem.cpp -o voting -lsqlite3 -lcrypto

# Run
./voting
```

---

## 🚀 Usage

### Quick Start

1. **Launch the application**
   ```bash
   ./voting
   ```

2. **Admin Login** (Default password: `admin123`)
   - Register voters
   - Add candidates
   - Monitor election statistics

3. **Cast Votes**
   - Select "Voter Panel" from main menu
   - Enter voter ID
   - Choose candidate

4. **View Results**
   - Access from main menu
   - Real-time vote counting
   - Percentage breakdowns

5. **Verify Blockchain**
   - Navigate to "Blockchain Operations"
   - Run integrity check
   - Export audit trail

---

## 🎬 Demo

### Main Menu
```
|===============================================+
|         BLOCKCHAIN VOTING SYSTEM              |
|===============================================|

1. Admin Panel
2. Voter Panel
3. View Results
4. Blockchain Operations
5. Exit
```

### Voting Process
```
========== CAST YOUR VOTE ==========
Enter your Voter ID: 101

========== CANDIDATES LIST ==========
ID   Name                Symbol         Votes   
1    Imran Khan          Cricket Bat    0       
2    Nawaz Sharif        Tiger          0       

Enter Candidate ID: 1

✓ Vote cast successfully!
  Your vote has been recorded securely in the blockchain.
```

### Election Results
```
========== ELECTION RESULTS ==========
Total Votes Cast: 100

1. Cricket Bat - Imran Khan
   Votes: 52 (52.0%)
   
2. Tiger - Nawaz Sharif
   Votes: 48 (48.0%)
```

### Blockchain Verification
```
   Checking Block 0: ✓ Valid
   Checking Block 1: ✓ Valid
   Checking Block 2: ✓ Valid
   
   ✓ All blocks verified successfully!
   Blockchain is valid and intact!
```

---

## 📊 System Architecture

### Component Diagram

```
┌─────────────────────────────────────┐
│       VotingSystem (Controller)     │
├─────────────────────────────────────┤
│  -  adminPanel()                     │
│  -  voterPanel()                     │
│  -  viewResults()                    │
└──────────┬──────────┬───────────────┘
           │          │          
      ┌────┴───┐  ┌───┴────┐  ┌────────┐
      │ Admin  │  │Database│  │Blockchain│
      │        │  │(SQLite)│  │  Chain   │
      └────────┘  └────────┘  └────────┘
```

### Class Hierarchy

```
User (Abstract)
 ├── Voter
 └── Candidate

Block ──(composition)──> Blockchain

VotingSystem ──(uses)──> Admin, Database, Blockchain
```

---

## 📁 Project Structure

```
blockchain-voting-system/
├── main.cpp              # Entry point
├── VotingSystem.cpp/h    # System controller
├── User.cpp/h            # Base user class
├── Voter.cpp/h           # Voter implementation
├── Candidate.cpp/h       # Candidate implementation
├── Block.cpp/h           # Blockchain block
├── Blockchain.cpp/h      # Chain management
├── Database.cpp/h        # SQLite operations
├── admin.cpp/h           # Admin authentication
├── colors.h              # ANSI color codes
├── windows_colors.h      # Windows console colors
├── voting_system.db      # SQLite database (auto-generated)
├── blockchain.dat        # Blockchain storage (auto-generated)
├── admin.dat             # Admin credentials (auto-generated)
└── README.md
```

---

## 🔒 Security Features

### 1. Cryptographic Hashing
Each block uses SHA-256 to create a unique hash based on:
- Previous block hash
- Voter ID
- Encrypted vote
- Timestamp

```cpp
hash = SHA256(previousHash + voterID + encryptedVote + timestamp)
```

### 2. Vote Encryption
Votes are encrypted before blockchain storage:
```cpp
encryptedVote = (candidateID + ENCRYPTION_KEY) % 100
```

### 3. Chain Integrity
- Every block references the previous block's hash
- Tampering with any block invalidates the entire chain
- Real-time verification detects modifications

### 4. Access Control
- Admin functions password-protected
- Failed login attempt limits
- Secure password change mechanism

### 5. Duplicate Prevention
- Database tracks voting status
- Blockchain immutability prevents vote modification
- Double-voting attempts rejected

---

## 🧪 Testing

### Test Scenario

```bash
# 1. Clean start
rm voting_system.db blockchain.dat

# 2. Run application
./voting

# 3. Admin Panel
# - Register 5 voters
# - Add 3 candidates
# - View statistics (should show 0 blocks)

# 4. Cast 4 votes
# - Verify blockchain grows to 4 blocks
# - Check voter turnout: 80%

# 5. Verify blockchain integrity
# - All blocks should be valid
# - Export blockchain audit trail

# 6. View results
# - Verify vote counts
# - Check percentage calculations
```

---

## 📚 Documentation

### Admin Operations

| Function | Description | Access |
|----------|-------------|--------|
| Register Voter | Add new voter with unique ID | Admin |
| Add Candidate | Register candidate with symbol | Admin |
| View Statistics | Election dashboard | Admin |
| Reset Database | Clear all data | Admin |
| Change Password | Update admin password | Admin |

### Voter Operations

| Function | Description | Access |
|----------|-------------|--------|
| Cast Vote | Submit encrypted vote | Voter |
| Check Status | Verify voting completion | Voter |

### Public Operations

| Function | Description | Access |
|----------|-------------|--------|
| View Results | See live vote counts | Public |
| View Blockchain | Browse chain data | Public |
| Verify Integrity | Validate blockchain | Public |

---

## 👤 Author

**Muhammad Dawood**
- GitHub: [@daw159](https://github.com/daw159)
- Email: mdawood78612@gmail.com

---

<div align="center">

**⭐ Star this repository if you found it helpful!**

Made with ❤️ for secure and transparent elections

</div>
```

***
