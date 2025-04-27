// UserManager.hpp

// Prevents duplicate inclusion (like a "one-time use" stamp)
#pragma once

// Include libraries for data structures and strings
#include <unordered_map>  // For std::unordered_map (fast key-value storage)
#include <string>         // For std::string (handling usernames/passwords)

class UserManager {
private:
    // Private member (hidden from outside the class)
    std::unordered_map<std::string, std::string> users; 
    //           ^           ^           ^
    //           |           |           |
    //    Username (key)   Password (value)
    // Acts like a "security ledger" storing username-password pairs.
public:
    // Constructor: Initializes the UserManager (like setting up an empty ledger)
    UserManager();

    // Method: Validates a user's login attempt (like a bouncer checking ID)
    bool login(const std::string& username, const std::string& password);
    //        ^^^^^^^^^^^^^^^^^^  ^^^^^^^^^^^^^^^^^^
    //        Username (reference) Password (reference) - Efficient, no copies!
    // Method: Registers a new user (like adding a new entry to the ledger)
    bool registerUser(const std::string& username, const std::string& password);
};