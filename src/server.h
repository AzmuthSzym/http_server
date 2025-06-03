#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <chrono>
#include <stdio.h>
#include "http_utils.h"

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

#endif