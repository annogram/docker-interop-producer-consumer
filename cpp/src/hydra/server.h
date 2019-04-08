#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

constexpr auto PIPE_VOLUME = "/var/interop-volume";

namespace hydra
{
class server
{
private:
  pid_t command_fifo;
  std::string command_pipe;

public:
  server(/* args */);
  ~server();
  pid_t startup();
  void shutdown();
};

} // namespace hydra
