#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

constexpr auto COMMAND_PIPE = "/var/interop-volume/pipe.fifo";

int main() {
    pid_t fifo = mkfifo(COMMAND_PIPE, 666);
    close(fifo);
    unlink(COMMAND_PIPE);
    return 1;
}