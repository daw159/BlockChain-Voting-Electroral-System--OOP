#define _HAS_STD_BYTE 0  // ✅ Must be FIRST line

#include <iostream>
#include "colors.h"          // ✅ Include colors.h first
#include "windows_colors.h"  // ✅ Then windows_colors.h
#include "VotingSystem.h"

using namespace std;

int main() {
    enableANSI();  // ✅ Enable ANSI colors on Windows
    
    VotingSystem system;
    
    if (!system.initialize()) {
        cerr << RED << "Failed to initialize system. Exiting..." << RESET << endl;
        return 1;
    }
    
    system.run();
    
    return 0;
}
