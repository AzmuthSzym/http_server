#ifndef HTTP_UTILS_H
#define HTTP_UTILS_H

#include <string>
#include <winsock2.h>
#include <map>


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
};

// Function declarations
std::string readRequest(SOCKET clientSocket);
std::string createResponse(ResponseInfo content);
HttpRequest parseRequest(std::string rawRequest);
ResponseInfo handleRequest(HttpRequest request);
std::map<std::string, std::string> parseQueryString(const std::string& queryString);

#endif