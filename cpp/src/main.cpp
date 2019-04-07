#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <chrono>
#include <thread>

constexpr auto PIPE_VOLUME = "/var/interop-volume";

int main() {
    std::stringstream ss;
    ss << PIPE_VOLUME << "/command.fifo";
    pid_t fifo = mkfifo(ss.str().c_str(), 666);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    close(fifo);
    unlink(ss.str().c_str());
    return 1;
}