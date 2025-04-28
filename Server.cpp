// Server.cpp
#include "Server.hpp"
#include "RequestHandler.hpp"
#include <iostream>
#include <stdexcept>

Server::Server(int port) {
#if defined(_WIN32) || defined(_WIN64)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
        throw std::runtime_error("WSAStartup failed");
#endif

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
#if defined(_WIN32) || defined(_WIN64)
        WSACleanup();
#endif
        throw std::runtime_error("socket() failed");
    }

    sockaddr_in addr{};
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(static_cast<u_short>(port));
    if (bind(serverSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(serverSocket);
#if defined(_WIN32) || defined(_WIN64)
        WSACleanup();
#endif
        throw std::runtime_error("bind() failed");
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(serverSocket);
#if defined(_WIN32) || defined(_WIN64)
        WSACleanup();
#endif
        throw std::runtime_error("listen() failed");
    }
}

Server::~Server() {
    // stop accepting new clients
    closesocket(serverSocket);

#if defined(_WIN32) || defined(_WIN64)
    WSACleanup();
#endif

    // join threads…
    for (auto &t : clientThreads)
      if (t.joinable()) t.join();
}

void Server::handleClient(SOCKET clientSocket) {
    FileSystem    fs("server_files/");
    UserManager   um;
    RequestHandler rh(fs, um);      // ← must be right here

    std::string buffer;    // accumulates raw bytes
    char        temp[512];

    while (true) {
        int bytes = recv(clientSocket, temp, sizeof(temp), 0);
        if (bytes <= 0) break;            // client hung up or error
        buffer.append(temp, bytes);

        // Inner loop: slice off each complete line (first CR or LF)
        size_t pos;
        while ((pos = buffer.find_first_of("\r\n")) != std::string::npos) {
            // 1) pull out the raw line
            std::string line = buffer.substr(0, pos);

            // 2) erase that line + any adjacent CR/LF
            size_t next = buffer.find_first_not_of("\r\n", pos);
            buffer.erase(0, (next == std::string::npos ? buffer.size() : next));

            // 3) trim any stray \r or \n at end (just in case)
            while (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
                line.pop_back();

            // ─── New: ignore blank or all‐whitespace lines ───
            if (line.find_first_not_of(" \t") == std::string::npos) {
                continue;   // skip sending ERR_UNKNOWN_CMD on empty <Enter>
            }

            // 4) only now process a non‐blank command
            std::string response = rh.processRequest(line);
            send(clientSocket,
                 response.c_str(),
                 static_cast<int>(response.size()),
                 0);
        }
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
