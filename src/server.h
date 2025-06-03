#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <chrono>
#include <stdio.h>

#define DEFAULT_PORT 27015
#pragma comment(lib, "ws2_32.lib")

class Server {
private:
    int port;
    SOCKET listenSocket;
    bool wsaInitialized;
    bool running;

public:
    Server(int port);
    bool start();
    void stop();
    void reset();
    ~Server();
};

// Function declarations (if you keep them as standalone functions)
std::string readRequest(SOCKET clientSocket);
std::string createResponse(std::string content);

#endif