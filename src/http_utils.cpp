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
    std::string response = "HTTP/1.1 " + responseInfo.statusCode + responseInfo.statusText + "\r\n"
                          "Content-Type:" +responseInfo.contentType+"\r\n"
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
    std::string fullPath = firstLine.substr(firstSpace + 1, secondSpace - firstSpace - 1);
    printf("DEBUG: fullPath = '%s'\n", fullPath.c_str());
    if(fullPath.find('?') != std::string::npos)
    {
        request.path = fullPath.substr(0, fullPath.find('?'));
        request.queryParams = parseQueryString(fullPath.substr(fullPath.find('?') + 1, fullPath.length() - 1));
        printf("DEBUG: final request.path = '%s'\n", request.path.c_str());
        printf("DEBUG: queryParams size = %zd\n", request.queryParams.size());
    }
    else
    {
        request.path = fullPath;
    }
    request.version = firstLine.substr(secondSpace + 1);

    return request;
}

ResponseInfo handleRequest(HttpRequest request)
{
    if(request.path == "/")
    {
        return serveFile("../public/index.html");
    }
    else if(request.path == "/about")
    {
        return serveFile("../public/about.html");
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
        return ResponseInfo{"200", "OK", response, "text/html"};
    }
    else
    {
        return ResponseInfo{"404", "Not Found", "404 Not Found", "text/plain"};
    }
}

std::map<std::string, std::string> parseQueryString(const std::string& queryString) 
{
    printf("DEBUG: parseQueryString input = '%s'\n", queryString.c_str());
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
            printf("DEBUG: Adding param: '%s' = '%s'\n", key.c_str(), value.c_str());
        }

        if(end == std::string::npos) break;
        start = end + 1;
        end = queryString.find('&', start);
    }

    return params;
}

std::string readFileContents(const std::string& filepath)
{
    std::ifstream file(filepath);
    if(file.good())
    {
        auto size = std::filesystem::file_size(filepath);
        std::string fileContents(size, '\0');
        file.read(&fileContents[0], size);
        return fileContents;
    }
    else
    {
        return "Error";
    }
}

std::string getMimeType(const std::string& filepath)
{
    size_t pos = filepath.rfind('.');
    if(pos != std::string::npos)
    {
        std::string extension = filepath.substr(pos, filepath.length() - 1);
        if(extension == ".html") return "text/html";
        else if(extension == ".css") return "text/css";
        else if(extension == ".js") return "application/javascript";
        else if(extension == ".png") return "image/png";
        else if(extension == ".jpg") return "image/jpeg";
        else return "text/plain";
    }
    else
    {
        return "Error";
    }
}

ResponseInfo serveFile(const std::string& filepath)
{
    std::string fileContents = readFileContents(filepath);
    if(fileContents != "Error")
    {
        std::string mimeType = getMimeType(filepath);
        return ResponseInfo{"200", "OK", fileContents, mimeType};
    }
    return ResponseInfo{"404", "Not Found", "WRONG SERVER FILE", "text/plain"};
    
}