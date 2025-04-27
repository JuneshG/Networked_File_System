// RequestHandler.hpp
// Prevents duplicate inclusion (like a "one-time use" seal)
#pragma once

// Include headers for dependencies
#include "FileSystem.hpp"    // Lets us use the FileSystem class (the "filing cabinet")
#include "UserManager.hpp"   // Lets us use the UserManager class (the "security ledger")
#include <string>           // For std::string (handling text)

class RequestHandler {
private:
    // Private member references (like specialized tools)
    FileSystem& fs;  // Reference to a FileSystem object (the "filing cabinet" we'll use)
    UserManager& um; // Reference to a UserManager object (the "security ledger" we'll check)

public:
    // Constructor: Initializes the handler with existing FileSystem and UserManager objects
    RequestHandler(FileSystem& fs, UserManager& um); 
    //              ^^^^^^^^^^^^^  ^^^^^^^^^^^^^^
    //              "Borrow" the filing cabinet and security ledger (no copies!)

    // Method: Processes a client's request (like a waiter handling an order)
    std::string processRequest(const std::string& request); 
    //                         ^^^^^^^^^^^^^^^^^^
     //                         The client's command (e.g., "CREATE_DIR documents")
};