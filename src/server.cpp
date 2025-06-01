#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT 27015

int main() {
    // 1. Initialize Winsock first
    WSADATA wsaData;
    int iResult;

    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
    else 
    {
        printf("WSAStartup successful\n");
    }
    
    // 2. Create a socket
    SOCKET ListenSocket = INVALID_SOCKET;
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(ListenSocket == INVALID_SOCKET) 
    {
        printf("Error at socket() initalization: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    else
    {
        printf("Socket creation successful\n");
    }

    // 3. Set up server address (port 8080)
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT); // DEFAULT_PORT = 27015
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    // 4. Bind socket to address
    iResult = bind(ListenSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));

    if(iResult != 0)
    {
        printf("Socked binding error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    else
    {
        printf("Socket binding successful\n");
    }

    // 5. Listen for connections
    iResult = listen(ListenSocket, SOMAXCONN);
        if(iResult != 0)
    {
        printf("Listening for connections error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // 6. Accept loop
    SOCKET ClientSocket = INVALID_SOCKET;
    sockaddr_in clientAddress;
    int clientAddrSize = sizeof(clientAddress);

    printf("Starting accept loop...\n");
    while (true) 
    {
        printf("Waiting for connection...\n");  // Add this too

        ClientSocket = accept(ListenSocket, (sockaddr*)&clientAddress, &clientAddrSize);
        if (ClientSocket == INVALID_SOCKET) {
            printf("Accept failed: %d\n", WSAGetLastError());
            continue; // Try to accept the next connection, for learning
        }

        char buffer[1024];
        int bytesReceived = recv(ClientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            printf("Received from browser:\n%s\n", buffer);
        
        }
        //char* message = "Hello from the server!\n";
        //char* message = "HTTP/1.1 200 OK\r\nConnection: close\r\n\r\nHello World!";
        char* message = "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: 12\r\n"
                "Connection: close\r\n"
                "Cache-Control: no-cache\r\n"
                "\r\n"
                "Hello World!";
        send(ClientSocket, message, strlen(message), 0);

        closesocket(ClientSocket);
    }
    
    // 7. Cleanup
    return 0;
}