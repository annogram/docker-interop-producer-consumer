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
    while (!_done)
    {
        // std::cout << "reading" << std::endl;
        while (std::getline(_stream, datum))
        {
            // std::cout << datum << std::endl;
            auto message = Message::ParseMessage(datum);
            std::cout << message._sender << std::endl
                      << message._path << std::endl
                      << std::endl;
        }
    }
}

pid_t hydra::Server::startup()
{
    _done = false;
    _commandFifo = mkfifo(_commandPipe.c_str(), 0666);
    commandWatcher = std::thread(&hydra::Server::watcher, this);
    return _commandFifo;
}

void hydra::Server::shutdown()
{
    _done = true;
    if (_stream.is_open())
        _stream.close();
    commandWatcher.detach();
    unlink(_commandPipe.c_str());
}