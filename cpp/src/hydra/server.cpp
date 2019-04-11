#include "server.h"
#include <iostream>
#include <fstream>
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
    std::fstream fstream(_commandPipe);
    std::string datum;
    std::cout << "Reading from pipe" << std::endl;
    
    while(fstream >> datum){
        std::cout <<"In read looop" << std::endl;
        std::cout << datum << std::endl;
    }
    std::cout << "Finished reading from pipe" << std::endl;
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