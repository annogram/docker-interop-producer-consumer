#include "server.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>

hydra::server::server(std::string path)
{
    int len;
    std::list<int> clients;
    unsigned t;
    struct sockaddr_un local;

    if ((_watcherThreadId = socket(AF_UNIX, SOCK_STREAM, 0) == -1))
    {
        throw hydra::OpenSocketException();
    }
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, path.c_str());
    unlink(local.sun_path); // Unlink in case there is some open connection
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(_watcherThreadId, (struct sockaddr *)&local, len) == -1)
    {
        throw hydra::OpenSocketException("Could not bind to socket");
    }
    if (listen(_watcherThreadId, 10) == -1)
    {
        throw hydra::OpenSocketException("Was unable to read from the socket");
    }
}

hydra::server::~server() {}

void hydra::server::WatcherFunc()
{
    int clientId;
    unsigned t;
    struct sockaddr_un remote;
    _listening = true;
    while (_listening)
    {
        std::cout << "Awaiting connection" << std::endl;
        t = sizeof(remote);
        if ((clientId = accept(_watcherThreadId, (struct sockaddr *)&remote, &t)) == -1)
        {
            throw hydra::OpenSocketException("Could not open connection to client socket");
        }
        std::cout << "Connected" << std::endl;
    }
}

pid_t hydra::server::startup()
{
    _watcher = std::thread(&hydra::server::WatcherFunc, this);
}

void hydra::server::shutdown()
{
    _watcher.join();
}