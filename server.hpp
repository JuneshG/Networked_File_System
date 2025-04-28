// Server.hpp (after)
#pragma once

#if defined(_WIN32) || defined(_WIN64)
// ———————— Windows ————————
#  define _WIN32_WINNT 0x0601
#  include <winsock2.h>
#  include <windows.h>
   typedef SOCKET socket_t;
#else
// —————— POSIX / Linux ——————
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <unistd.h>     // for close()
   typedef int socket_t;
#  define INVALID_SOCKET  -1
#  define SOCKET_ERROR    -1
#  define closesocket(s)  ::close(s)
#endif

#include <vector>
#include <thread>
#include <mutex>

class Server {
private:
    socket_t        serverSocket;
    std::vector<std::thread> clientThreads;
    void handleClient(socket_t clientSocket);

public:
    Server(int port);
    ~Server();
    void start();
};
