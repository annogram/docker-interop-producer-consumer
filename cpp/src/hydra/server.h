#if !defined(HYDRA_SERVER_H)
#define HYDRA_SERVER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <thread>
#include <string>
#include <list>
#include <fstream>


constexpr auto PIPE_VOLUME = "/var/interop-volume";

namespace hydra
{
class OpenSocketException : public std::exception
{
private:
  std::string _msg;

public:
  OpenSocketException(std::string msg = "Could not create initial socket") : _msg(msg)
  {
  }
  virtual char const *what() const noexcept { return _msg.c_str(); }
};

class Server
{
private:
  pid_t _commandFifo;
  std::string _commandPipe;
  std::ifstream _stream;
  std::thread commandWatcher;
  bool _done;
  void watcher();
public:
  Server(/* args */);
  ~Server();
  pid_t startup();
  void shutdown();
};

} // namespace hydra

#endif // HYDRA_SERVER_H
