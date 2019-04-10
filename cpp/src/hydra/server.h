#if !defined(HYDRA_SERVER_H)
#define HYDRA_SERVER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <thread>
#include <string>
#include <list>

constexpr const char *PIPE_VOLUME = "/var/interop-volume/cpp_server";

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

class server
{
private:
  int _watcherThreadId;
  bool _listening = false;
  std::thread _watcher;
  void WatcherFunc();
public:
  server(std::string path = PIPE_VOLUME);
  ~server();
  pid_t startup();
  void shutdown();
};

} // namespace hydra

#endif // HYDRA_SERVER_H
