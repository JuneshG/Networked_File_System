// Server.cpp
#include "Server.hpp"
#include "RequestHandler.hpp"
#include <iostream>     // std::cerr, std::cout
#include <stdexcept>    // std::runtime_error

Server::Server(int port) {
    // 1) Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }

    // 2) Create a listening socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("socket() failed");
    }

    // 3) Bind to all interfaces on the given port
    sockaddr_in addr{};
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;               // 0.0.0.0
    addr.sin_port        = htons(static_cast<u_short>(port));
    if (bind(serverSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(serverSocket);
        WSACleanup();
        throw std::runtime_error("bind() failed");
    }

    // 4) Start listening
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(serverSocket);
        WSACleanup();
        throw std::runtime_error("listen() failed");
    }
}

Server::~Server() {
    // Stop accepting new clients
    closesocket(serverSocket);

    // Clean up WinSock
    WSACleanup();

    // Wait for all client threads to finish
    for (auto &t : clientThreads) {
        if (t.joinable()) t.join();
    }
}
void Server::handleClient(SOCKET clientSocket) {
    FileSystem fs("server_files/");
    UserManager um;
    RequestHandler rh(fs, um);

    char buffer[1024];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;
        buffer[bytesReceived] = '\0';
        std::string request(buffer);

        std::string response = rh.processRequest(request);
        send(clientSocket, response.c_str(), (int)response.size(), 0);
    }
    closesocket(clientSocket);
}

void Server::start() {
    std::cout << "Server listening for connections...\n";
    while (true) {
        // Block until a client connects
        SOCKET clientSock = accept(serverSocket, nullptr, nullptr);
        if (clientSock == INVALID_SOCKET) {
            std::cerr << "accept() failed or server shutting down\n";
            break;
        }

        // Spawn a new thread to handle that client
        clientThreads.emplace_back(
            &Server::handleClient,
            this,
            clientSock
        );
        // If you’d rather detach them immediately:
        // clientThreads.back().detach();
    }
}
