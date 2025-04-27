// main.cpp
#include "Server.hpp"
#include <stdexcept> // For std::runtime_error
#include <iostream>  // For std::cerr, std::cout

int main() {
    try {
        Server server(8080);    // Listen on port 8080 (or choose your port)
        server.start();         // Begin accepting clients
    }
    catch (const std::exception &e) {
        std::cerr << "Fatal: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
