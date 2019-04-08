#include "server.h"
#include <iostream>
#include <thread>

hydra::server::server()
{
    std::stringstream ss;
    ss << PIPE_VOLUME << "/command.fifo";
    command_pipe = ss.str();
}

hydra::server::~server() {}

pid_t hydra::server::startup()
{
    command_fifo = mkfifo(command_pipe.c_str(), 666);
    return command_fifo;
}

void hydra::server::shutdown()
{
    close(command_fifo);
    unlink(command_pipe.c_str());
}