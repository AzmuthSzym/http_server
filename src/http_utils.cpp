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

std::string createResponse(ResponseInfo responseInfo) 
{
    std::string response = "HTTP/1.1 " + responseInfo.statusCode + " OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Content-Length: " + std::to_string(responseInfo.content.length()) + "\r\n"
                          "Connection: close\r\n"
                          "Cache-Control: no-cache\r\n"
                          "\r\n" + responseInfo.content;
    return response;
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

ResponseInfo handleRequest(HttpRequest request)
{
    if(request.path == "/")
    {
        return ResponseInfo{"200 OK", "Home Page"};
    }
    else if(request.path == "/about")
    {
        return ResponseInfo{"200 OK", "About"};
    }
    else if(request.path == "/search") 
    {
        std::string response = "<html><body>";
        response += "<h1>Search Results</h1>";
        
        if (!request.queryParams.empty()) {
            response += "<h2>Search Parameters:</h2><ul>";
            for (const auto& param : request.queryParams) {
                response += "<li><strong>" + param.first + ":</strong> " + param.second + "</li>";
            }
            response += "</ul>";
        } else {
            response += "<p>No search parameters provided.</p>";
        }
        
        response += "</body></html>";
        return ResponseInfo{"200 OK", response};
    }
    else
    {
        return ResponseInfo{"404 Not Found", "404 Not Found"};
    }
}

std::map<std::string, std::string> parseQueryString(const std::string& queryString) 
{
    std::map<std::string, std::string> params;
    if (queryString.empty())
    {
        return params;
    }

    size_t start = 0;
    size_t end = queryString.find('&');
    
    while (start < queryString.length())
    {
        std::string pair = queryString.substr(start, end - start);

        size_t equalPos = pair.find('=');
        if(equalPos != std::string::npos)
        {
            std::string key = pair.substr(0, equalPos);
            std::string value = pair.substr(equalPos + 1);
            params[key] = value;
        }

        if(end == std::string::npos) break;
        start = end + 1;
        end = queryString.find('&', start);
    }

    return params;
}