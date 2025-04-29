// Client.cpp (Simple TCP Client)
#include <iostream>
#include <string>
#include <thread>
#include <cstring>
#include <vector>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#define closesocket close
typedef int SOCKET;
#endif

int main() {
    #if defined(_WIN32)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return 1;
    }
    #endif

    SOCKET clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSock < 0) {
        std::cerr << "Error creating socket.\n";
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;

    // ⚠️ Replace "18.119.253.55" with your AWS EC2 public IP address
    // serverAddr.sin_addr.s_addr = inet_addr("18.119.253.55"); 
    serverAddr.sin_addr.s_addr = inet_addr("localhost"); // For local testing, use localhost
    serverAddr.sin_port = htons(8080); // Port 8080 as configured on server

    if (connect(clientSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection to server failed.\n";
        closesocket(clientSock);
        return 1;
    }

    std::cout << "Connected to server!\n";
    std::cout << "Enter commands (e.g., CREATE_DIR folder): \n";

    std::string command;
    char buffer[4096];

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        
        if (command.empty()) continue; // skip empty lines

        if (command == "quit" || command == "exit") {
            std::cout << "Closing connection...\n";
            break;
        }

        // Send command to server
        if (send(clientSock, command.c_str(), command.size(), 0) < 0) {
            std::cerr << "Send failed.\n";
            break;
        }

        // receive response from server
        int bytesReceived = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            std::cerr << "Connection closed by server.\n";
            break;
        }

        buffer[bytesReceived] = '\0'; // null-terminate
        std::cout << "Server: " << buffer << std::endl;
    }

    closesocket(clientSock);

    #if defined(_WIN32)
    WSACleanup();
    #endif

    return 0;
}
