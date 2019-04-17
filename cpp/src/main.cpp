#include <chrono>
#include <thread>
#include "hydra/server.h"

int main()
{
    hydra::server server;
    server.startup();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    server.shutdown();
    return 0;
}