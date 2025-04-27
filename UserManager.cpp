#include "UserManager.hpp" // Include the header file for UserManager class

UserManager::UserManager() { // Constructor to initialize the UserManager
    // Initialize the user database (like setting up an empty ledger)       
    // Preload test users (replace with database later)
    users["alice"] = "password123"; // Example user 1
    users["bob"] = "qwerty"; // Example user 2
    users["charlie"] = "letmein"; // Example user 3
}

bool UserManager::login(const std::string& username, const std::string& password) {     // Method to validate a user's login attempt
    // Check if the username exists and if the password matches (like a bouncer checking ID)    
    return (users.find(username) != users.end() && users[username] == password);    // Check if the username exists and if the password matches
    // If the username is found in the map and the password matches, return true (login successful)
    // Otherwise, return false (login failed)
}   // End of login method

bool UserManager::registerUser(const std::string& username, // Method to register a new user
    const std::string& password) // (like adding a new entry to the ledger)
{
// try to insert; if username already exists, insertion fails
auto [it, inserted] = users.emplace(username, password);    //
return inserted;
}

// If the insertion was successful (username didn't exist), return true (registration successful)
// If the username already exists, return false (registration failed)
   // End of registerUser method