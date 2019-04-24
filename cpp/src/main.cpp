#include <chrono>
#include <thread>
#include "hydra/server.h"

int main()
{
    hydra::Server server;
    server.startup();
    std::this_thread::sleep_for(std::chrono::seconds(5000));
    server.shutdown();
    return 0;
}