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

    return 0;
}

