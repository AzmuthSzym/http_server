#include "server.h"

std::string createResponse(std::string content) 
{
    std::string response = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Content-Length: " + std::to_string(content.length()) + "\r\n"
                          "Connection: close\r\n"
                          "Cache-Control: no-cache\r\n"
                          "\r\n" + content;
    return response;
}

std::string readRequest(SOCKET clientSocket) 
{
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) 
    {
        buffer[bytesReceived] = '\0';
        printf("Received from browser:\n%s\n", buffer);
        return std::string(buffer);
    }
    return "";
}

Server::Server(int port)
{
    this->port = port;
    listenSocket = INVALID_SOCKET;
    running = false;
    // 1. Initialize Winsock first
    WSADATA wsaData;
    
    int iResult;

    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        wsaInitialized = false;
    }
    else 
    {
        printf("WSAStartup successful\n");
        wsaInitialized = true;
    }
}

bool Server::start()
{
    int iResult;
    // 2. Create a socket
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(listenSocket == INVALID_SOCKET) 
    {
        printf("Error at socket() initalization: %ld\n", WSAGetLastError());
        reset();
        return false;
    }
    else
    {
        printf("Socket creation successful\n");
    }

    // 3. Set up server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(this->port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // 4. Bind socket to address
    iResult = bind(listenSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));

    if(iResult != 0)
    {
        printf("Socked binding error: %d\n", WSAGetLastError());
        reset();
        return false;
    }
    else
    {
        printf("Socket binding successful\n");
    }

    // 5. Listen for connections
    iResult = listen(listenSocket, SOMAXCONN);
        if(iResult != 0)
    {
        printf("Listening for connections error: %d\n", WSAGetLastError());
        reset();
        return false;
    }

    // 6. Accept loop
    SOCKET ClientSocket = INVALID_SOCKET;
    sockaddr_in clientAddress;
    int clientAddrSize = sizeof(clientAddress);

    printf("Starting accept loop...\n");
    running = true;
    while (running) 
    {
        printf("Waiting for connection...\n");

        ClientSocket = accept(listenSocket, (sockaddr*)&clientAddress, &clientAddrSize);
        if (ClientSocket == INVALID_SOCKET) {
            printf("Accept failed: %d\n", WSAGetLastError());
            continue; // Try to accept the next connection, for learning
        }

        std::string request = readRequest(ClientSocket);
        std::string response = createResponse("Hello World!");
        send(ClientSocket, response.c_str(), response.length(), 0);

        closesocket(ClientSocket);
    }
    return true;
}

void Server::reset()
{
    closesocket(listenSocket);
    listenSocket = INVALID_SOCKET;
}

void Server::stop()
{
    running = false;
}

Server::~Server()
{
    if (listenSocket != INVALID_SOCKET) 
    {
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
    }
    if(wsaInitialized)
    {
        WSACleanup();
        wsaInitialized = false;
    }
}