#include "server.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>

hydra::server::server()
{
    std::stringstream ss;
    ss << PIPE_VOLUME << "/command.fifo";
    _commandPipe = ss.str();
}

hydra::server::~server() {}

void hydra::server::watcher()
{
    pid_t pipe_id;
    while (true)
    {
        pipe_id = open(_commandPipe.c_str(), O_RDONLY | O_NONBLOCK);
        std::string depth;
        read(pipe_id, &depth, sizeof(depth));
        close(pipe_id);
        std::cout << depth << std::endl;
    }
    
}

pid_t hydra::server::startup()
{
    _commandFifo = mkfifo(_commandPipe.c_str(), 666);
    commandWatcher = std::thread(&hydra::server::watcher, this);
    return _commandFifo;
}

void hydra::server::shutdown()
{
    commandWatcher.join();
    close(_commandFifo);
    unlink(_commandPipe.c_str());
}