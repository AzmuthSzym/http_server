#ifndef HTTP_UTILS_H
#define HTTP_UTILS_H

#include <string>
#include <winsock2.h>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


struct HttpRequest {
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> queryParams;
};

struct ResponseInfo {
    std::string statusCode;
    std::string statusText;
    std::string content;
    std::string contentType;
};

// Function declarations
std::string readRequest(SOCKET clientSocket);
std::string createResponse(ResponseInfo content);
HttpRequest parseRequest(std::string rawRequest);
ResponseInfo handleRequest(HttpRequest request);
std::map<std::string, std::string> parseQueryString(const std::string& queryString);
std::string readFileContents(const std::string& filepath);
std::string getMimeType(const std::string& filepath);
ResponseInfo serveFile(const std::string& filepath);


#endif