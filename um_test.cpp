// um_test.cpp
#include <iostream>
#include "UserManager.hpp"

int main() {
    UserManager um;

    // Test preload login
    std::cout << std::boolalpha;
    std::cout << "alice/password123: "
              << um.login("alice", "password123") << "\n";

    // Test failure
    std::cout << "alice/badpass: "
              << um.login("alice", "wrong") << "\n";

    // Test registerUser
    std::cout << "Register new 'dave': "
              << um.registerUser("dave", "xyz") << "\n";
    std::cout << "Login dave/xyz: "
              << um.login("dave", "xyz") << "\n";

    // Test duplicate register
    std::cout << "Register alice again: "
              << um.registerUser("alice", "123") << "\n";

    return 0;
}
