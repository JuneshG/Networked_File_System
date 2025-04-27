//Server.hpp
#pragma once // Prevent this header from being included multiple times (like a "do not duplicate" stamp)

// Include necessary libraries
#define _WIN32_WINNT 0x0601
#include <winsock2.h> // Windows socket library (for network communication: TCP/IP)
#include <vector> // Standard C++ library for dynamic arrays (like lists) and For std::vector (dynamic array to store client threads)
#include <thread> // Standard C++ library for multi-threading (to handle multiple clients at once) for std::thread (to create threads for each client)
#include <mutex> // Standard C++ library for thread synchronization
#include <windows.h>

class Server { // Class definition for the server and its functionalities and data members and methods

private: // Private members of the class
    SOCKET serverSocket; // Socket for the server to accept incoming connections. The "phone line" the server uses to listen for connections
    std::vector<std::thread> clientThreads; // Vector to store threads for each connected client. List of "workers" handling clients (like waiters at a restaurant)

    //private methods
    void handleClient(SOCKET clientSocket); // Method to handle communication with a connected client. The "waiter" who takes orders and serves food to the client. Function to manage ONE client (like a waiter serving one table)


public: // Public members of the class
    //Constructor called when creating a Server Object. (e.g., Server myServer(8080);)
    Server(int port); // Sets up the "phone line" (socket) on the given port. The "phone number" the server listens on for incoming calls (connections). The port number is like an extension number for the server to receive calls on.

    //Destructor called when destroying a Server Object. (e.g., Server myServer(8080);)
    ~Server(); // Cleans up resources when the server is no longer needed. The "goodbye" message to the server when it's shutting down.

    //public method: Starts the server to accept incoming connections. Like opening the restaurant doors to welcome customers.
    void start(); // Starts the server and begins accepting client connections. The "open for business" sign on the restaurant door.
};
