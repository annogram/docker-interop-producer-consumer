#include "server.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include "./messages.h"

hydra::Server::Server()
{
    std::stringstream ss;
    ss << PIPE_VOLUME << "/command.fifo";
    _commandPipe = ss.str();
}

hydra::Server::~Server() {}

void hydra::Server::watcher()
{
    _stream = std::ifstream(_commandPipe);
    std::string datum;
    while (std::getline(_stream, datum))
    {
        auto message = Message::ParseMessage(datum);
        std::cout << datum << std::endl;    
    }
    

    // auto type = message->type;
}

pid_t hydra::Server::startup()
{
    _commandFifo = mkfifo(_commandPipe.c_str(), 0666);
    _go = true;
    commandWatcher = std::thread(&hydra::Server::watcher, this);
    return _commandFifo;
}

void hydra::Server::shutdown()
{
    _go = false;
    commandWatcher.detach();
    unlink(_commandPipe.c_str());
}