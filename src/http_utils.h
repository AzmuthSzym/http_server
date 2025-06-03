#ifndef HTTP_UTILS_H
#define HTTP_UTILS_H

#include <string>
#include <winsock2.h>


struct HttpRequest {
    std::string method;
    std::string path; 
    std::string version;
};

// Function declarations
std::string readRequest(SOCKET clientSocket);
std::string createResponse(std::string content);
HttpRequest parseRequest(std::string rawRequest);
std::string handleRequest(HttpRequest request);

#endif