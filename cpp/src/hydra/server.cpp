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
    int num;
    char value[300];
    std::cout << "Awaiting a client" << std::endl;
    pipe_id = open(_commandPipe.c_str(), O_RDONLY);
    std::cout << "Found a client" << std::endl;
    do {
        if((num = read(pipe_id, value, sizeof(value))) == -1){
            throw hydra::OpenSocketException("Could not read from pipe");
        }else{
            std::cout << value << std::endl;
        }
    } while(num > 0);
}

pid_t hydra::server::startup()
{
    std::cout << "Opening command pipe" << std::endl;
    _commandFifo = mkfifo(_commandPipe.c_str(), 0666);
    commandWatcher = std::thread(&hydra::server::watcher, this);
    return _commandFifo;
}

void hydra::server::shutdown()
{
    commandWatcher.join();
    close(_commandFifo);
    unlink(_commandPipe.c_str());
}