#if !defined(HYDRA_SERVER_H)
#define HYDRA_SERVER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <thread>
#include <string>
#include <list>

constexpr auto PIPE_VOLUME = "/var/interop-volume";

namespace hydra
{
class server
{
private:
  pid_t _commandFifo;
  std::string _commandPipe;
  std::thread commandWatcher;
  void watcher();
public:
  server(/* args */);
  ~server();
  pid_t startup();
  void shutdown();
};

} // namespace hydra

#endif // HYDRA_SERVER_H
