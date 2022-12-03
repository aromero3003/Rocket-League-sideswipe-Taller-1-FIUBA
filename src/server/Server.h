#ifndef __SERVER_H__
#define __SERVER_H__

#include <algorithm>
#include <atomic>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>

#include "AcceptThread.h"
#include "socket.h"
class Server {
 private:
  std::atomic<bool> serverStatus;
  AcceptThread acceptThread;

  void shutdown();

 public:
  explicit Server(Socket& skt);
  void run();
  void waitToClose();
};
#endif
