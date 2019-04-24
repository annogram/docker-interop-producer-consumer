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
    _stream = std::fstream(_commandPipe);
    std::string datum;
    std::stringstream out;
    do {
        _stream >> datum;
        if(datum == "s")
            _go = false;
        else
            out << datum;

    } while (_go);
    auto message = Message::ParseMessage(out.str());
    // auto type = message->type;
    std::cout << out.str() << std::endl;
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
    _stream.close();
    commandWatcher.detach();
    unlink(_commandPipe.c_str());
}