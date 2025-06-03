#include <vector>
#include "server.h"

using namespace std;

int main() {
    Server server(27015);
    std::thread serverThread(&Server::start, &server);

    std::this_thread::sleep_for(std::chrono::seconds(10));

    server.stop();

    serverThread.join();
    return 0;
}

