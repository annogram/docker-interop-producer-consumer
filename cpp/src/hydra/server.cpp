#include "server.h"
#include <iostream>

hydra::server::server(/* args */)
{
    std::stringstream ss;
    ss << PIPE_VOLUME << "/command.fifo";
    std::cout << ss.str() << std::endl;
    command_pipe = ss.str();
}

hydra::server::~server()
{
}

pid_t hydra::server::startup(){
    std::cout << command_pipe << std::endl;
    command_fifo = mkfifo(command_pipe.c_str(), 666);
    return command_fifo;
}

void hydra::server::shutdown()
{
    close(command_fifo);
    unlink(command_pipe.c_str());
}