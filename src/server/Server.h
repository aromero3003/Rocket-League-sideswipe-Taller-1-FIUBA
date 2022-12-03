#ifndef __SERVER_H__
#define __SERVER_H__

#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <atomic>
#include "socket.h"
#include "AcceptThread.h"
#include <atomic>
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
