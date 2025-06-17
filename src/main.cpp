#include <vector>
#include "server.h"
#include "http_utils.h"

using namespace std;

int main() {
    Server server(27015);
    std::thread serverThread(&Server::start, &server);

    std::this_thread::sleep_for(std::chrono::seconds(20));

    server.stop();

    serverThread.join();
    /*std::string content = "Hello World!";
    std::string response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "Content-Length: " + std::to_string(content.length()) + "\r\n"
                        "Connection: close\r\n"
                        "Cache-Control: no-cache\r\n"
                        "\r\n" + content;
    HttpRequest test = parseRequest(response);
    std::cout << test.method << std::endl;
    std::cout << test.path << std::endl;
    std::cout << test.version << std::endl;*/

    return 0;
}

