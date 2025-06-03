#include "http_utils.h"

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

HttpRequest parseRequest(std::string rawRequest)
{
    HttpRequest request;
    //From RFC 7230 Paragraph3 - First line of the message always contains method, path and version each separated by a space (SP)
    std::string firstLine = rawRequest.substr(0, rawRequest.find('\r\n'));

    // Find positions of the two spaces
    size_t firstSpace = firstLine.find(' ');
    size_t secondSpace = firstLine.find(' ', firstSpace + 1);

    request.method = firstLine.substr(0, firstSpace);
    request.path = firstLine.substr(firstSpace + 1, secondSpace - firstSpace - 1);
    request.version = firstLine.substr(secondSpace + 1);

    return request;
}

std::string handleRequest(HttpRequest request)
{
    if(request.path == "/")
    {
        return "Home Page";
    }
    else if(request.path == "/about")
    {
        return "About";
    }
    else
    {
        return "404 Not Found";
    }
}